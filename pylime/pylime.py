# -*- coding: utf-8 -*-
"""
PyLime Python module for lightweight Monte Carlo estimation

:author: Alexander Wietek
"""
from __future__ import absolute_import, division, print_function
import os
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
from functools import wraps
import re
from collections import OrderedDict, defaultdict
import h5py
import copy


def read_data(directory, regex, quantities, verbose=True):
    """ Read data for various seeds and quantities using regular expression
    
    Args:
        directory (str)  : directory containing all data files
        regex (str)      : regular expression to match files in the directory
        quantities (list): list of strings of quantities in the data files
        verbose (bool)   : print the matching files
    Returns:
        OrderedDict:    dictionary of quantities and seeds
    """
    # get files matching the regular expression
    files = os.listdir(directory)
    files.sort()
    file_of_seed = OrderedDict()
    for fl in files:
        match = re.search(regex, fl)
        if match:
            seed = match.group(1)
            file_of_seed[seed] = fl
            if verbose:
                print("Matched", fl)

    # Read all hdf5 files
    values_of_quantity_seed = defaultdict(dict)
    for seed, fl in file_of_seed.items():
        try:
            hf = h5py.File(os.path.join(directory, fl), 'r')
        except:
            print("Error reading h5file: Ignoring seed {}".format(seed))
            continue

        for quantity in quantities:
            if quantity in hf.keys():
                values_of_quantity_seed[quantity][seed] = hf[quantity][:] 
            else:
                print("Couldn't find \"{}\" in seed {}".format(quantity, seed))
   
    return values_of_quantity_seed

def mean_err_of_data(data, quantities=None, nmins=None, nmaxs=None):
    """ simple mean and error of data
    
    Args:
        data:       dictionary of dictionary, quantities and seeds
        quantities: list of quantities for which to compute mean and error
                    (default: all means and errors are computed)
        nmins:      dictionary containing minimum index for each seed
        nmaxs:      dictionary containing minimum index for each seed
    Returns:
        2x dict:    dictionary of means and errors  of quantities
    """
    means = dict()
    errs = dict()

    if quantities == None:
        quantities = data.keys()
    
    for quantity in quantities:
        # mean_of_seeds = []
        # err_of_seeds = []

        # Compute mean, error for every seed
        all_data = []
        for seed, values in data[quantity].items():

            # truncate the timeseries
            if nmins == None:
                nmin = 0
            else:
                nmin = nmins[seed]
            if nmaxs == None:
                nmax = None
            else:
                nmax = nmaxs[seed]
            
            shape = values[nmin:nmax].shape
            if shape[0] > 0:
                all_data.append(values[nmin:nmax])

        all_data = np.concatenate(all_data, axis=0)
        means[quantity] = mean(all_data)
        errs[quantity] = sem(all_data)

    return means, errs

def mean_err_tau_of_data(data, quantities=None, nmins=None, nmaxs=None):
    """ mean, error, aund autocorrelation time of data
    
    Args:
        data:       dictionary of dictionary, quantities and seeds
        quantities: list of quantities for which to compute mean and error
                    (default: all means and errors are computed)
        nmins:      dictionary containing minimum index for each seed
        nmaxs:      dictionary containing minimum index for each seed
    Returns:
        3x dict:    dictionary of means, errors, and autocorrelation times  
                    of quantities
    """
    means = dict()
    errs = dict()
    taus = dict()

    if quantities == None:
        quantities = data.keys()
    
    for quantity in quantities:

        means[quantity] = 0
        errs[quantity] = 0

        # Compute mean, error for every seed
        avg = dict()
        err = dict()

        taus[quantity] = max(1., autocorr_time(data[quantity]))

        for seed, values in data[quantity].items():

            # truncate the timeseries
            if nmins == None:
                nmin = 0
            else:
                nmin = nmins[seed]
            if nmaxs == None:
                nmax = None
            else:
                nmax = nmaxs[seed]
            
            series = values[nmin:nmax]
            avg[seed] = mean(series)
            err[seed] = sem(series)

        
        for seed in data[quantity].keys(): 
            means[quantity] += avg[seed]
            errs[quantity] += err[seed]**2

        n_seeds = len(data[quantity].items())
        means[quantity] /= n_seeds
        errs[quantity] = np.sqrt(taus[quantity] * errs[quantity]) / n_seeds
        
    return means, errs, taus



def transform_quantity(data, source, target, function):
    """ transform a quantity in data according to a function
    
    Args:
        data:       dictionary of dictionary, quantities and seeds
        source:     name of the source quantity
        target:     name of the target quantity
        function:   function to apply to every seed
    Returns:
        dict of dict:  dictionary of seeds including the transformed 
    """
    if target not in data.keys():
        data[target] = dict()

    for (seed, values) in data[source].items():
        data[target][seed] = function(values)
    return data


def add_quantities(data, sources, target, prefactors=None):
    """ transform a quantity in data according to a function
    
    Args:
        data:       dictionary of dictionary, quantities and seeds
        sources:    list of names of the source quantities
        target:     name of the target quantity
        prefactors: dictionary of prefactors multiplied to sources
    Returns:
        dict of dict:  dictionary of seeds including the transformed 
    """
    if target not in data.keys():
        data[target] = dict()
    
    
    first_source = True
    for source in sources:

        if source not in data.keys():
            raise ValueError("Quantity {} not found in data!".format(source))
            
        if prefactors is None:
            pre = 1.0
        else:
            if source not in prefactors.keys():
                raise ValueError("Quantity {} not found in prefactors!".format(source))
            pre = prefactors[source]

        for (seed, values) in data[source].items():
            if first_source:
                data[target][seed] = pre * copy.deepcopy(values)
            else:
                data[target][seed] += pre * values

        first_source = False
    return data

def resample_bin_data(data, quantities=None, binsize=1, axis=0):
    """ simple mean and error of data
    
    Args:
        data:       dictionary of dictionary, quantities and seeds
    Returns:
        2x dict:    dictionary of means and errors  of quantities
    """
    data_resampled = dict()
    for quantity, values_of_seed in data.items():
        if quantities is None or quantity in quantities:
            data_resampled[quantity] = dict()
            for idx, (seed, values) in enumerate(values_of_seed.items()):
                data_resampled[quantity][seed] = \
                    resample_bin(data[quantity][seed], binsize, axis)
    return data_resampled

def resample_bin(array, binsize=1, axis=0):
    """ Resample a given array into bins 
    
    Args:
        array (np.array): The array being resampled
        binsize (int)   : the size of the resulting bins (default: 1)
        axis (int)      : axis along which to resample (default: 0)
    Returns:
        np.array: binned data
    """
    if not isinstance(array, np.ndarray):
        raise ValueError("array not of type numpy.array")

    shape = array.shape
    if not axis < len(shape):
        raise ValueError("Cannot bin resample axis {}".format(axis))

    if binsize > shape[axis]:
        raise ValueError("binsize larger than length of array")

    commensurate_size = (shape[axis] // binsize) * binsize
    resize_shape = []
    inter_shape = []
    for idx, d in enumerate(shape):
        if idx == axis:
            inter_shape.append(commensurate_size // binsize)
            inter_shape.append(binsize)
            resize_shape.append(commensurate_size)
        else:
            inter_shape.append(d)
            resize_shape.append(d)

    array.resize(resize_shape)
    array_reshaped = array.reshape(inter_shape)
    
    return array_reshaped.mean(axis=axis+1)

def resample_jackknife(array, axis=0):
    """ Resample a given array to jackknife samples 

    Args:
        array (np.array): The array being resampled
        binsize (int)   : the size of the resulting bins (default: 1)
        axis (int)      : axis along which to resample (default: 0)
    Returns:
        np.array: jackknife resampled data
    """
    if not isinstance(array, np.ndarray):
        raise ValueError("array not of type numpy.array")
    A_resampled = np.zeros_like(array)
    n_seeds = array.shape[axis]
    for seed in range(n_seeds):
        A_resampled[seed] = np.mean(np.delete(array, seed, axis=axis), axis=axis)
    return A_resampled



def resample_jackknife_data(data, quantities=None, axis=0):
    """ simple mean and error of data
    
    Args:
        data:       dictionary of dictionary, quantities and seeds
    Returns:
        2x dict:    dictionary of means and errors  of quantities
    """
    data_resampled = dict()
    for quantity, values_of_seed in data.items():
        if quantities is None or quantity in quantities:
            data_resampled[quantity] = dict()
            for idx, (seed, values) in enumerate(values_of_seed.items()):
                data_resampled[quantity][seed] = \
                    resample_jackknife(data[quantity][seed], axis)
    return data_resampled


def mean(array, axis=0):
    """ Compute the mean of an array
    
    Args:
        array (np.array): The array being resampled
        axis (int)      : axis along which to compute mean (default: 0)
    Returns:
        float: mean 
    """
    return np.mean(array, axis=axis)

def std(array, axis=0, ddof=0):
    """ Compute the std. deviation of an array
    
    Args:
        array (np.array): The array being resampled
        axis (int)      : axis along which to compute std. deviation (default: 0)
    Returns:
        float: std. deviation
    """
    return np.std(array, axis=axis, ddof=ddof)

def sem(array, axis=0, ddof=0):
    """ Compute statistical error of mean (sem)
    
    Args:
        array (np.array): The array being resampled
        axis (int)      : axis along which to compute sem (default: 0)
    Returns:
        float: sem
    """
    return stats.sem(array, axis=axis, ddof=ddof)

def add_sem(e1, e2):
    return np.sqrt(e1**2 + e2**2)

def add_sem(arr, axis=0):
    return np.sqrt(np.sum(arr**2, axis=axis))

def mult_sem(m1, e1, m2, e2):
    m = m1 * m2
    return np.sqrt(m**2 * ( (e1/m1)**2 + (e2/m2)**2))

def div_sem(m1, e1, m2, e2):
    m = m1 / m2
    return np.sqrt(m**2 * ( (e1/m1)**2 + (e2/m2)**2))

def sem_jackknife(array, axis=0, ddof=0):
    """ Compute statistical error of mean (sem) from jackknife resampled data
    
    Args:
        array (np.array): The array being resampled
        axis (int)      : axis along which to compute sem jackknife(default: 0)
    Returns:
        float: sem jackknife
    """
    n = array.shape[axis]
    return np.sqrt((n-1)*(n-ddof)) * stats.sem(array, axis=axis, ddof=ddof)

def err(array, axis=0, ddof=0, binidx=-1):
    """ Compute standard error of a given sample """
    if binidx < 0:
        binidx = binning_depth(array)
    binsize = 2**binidx
    array_bins = resample_bin(array, binsize)
    return stats.sem(array_bins, axis=axis, ddof=ddof)

def tau(array):
    """ Compute autocorrelation """
    binidx = binning_depth(array)
    if binidx >= 2:
        er = err(array)
        er0 = err(array, binidx=0)
        return (er**2)/(er0**2)
    else:
        return 0

def binning_depth(array, maxk_offset=4):
    if not isinstance(array, np.ndarray):
        raise ValueError("array not of type numpy.array")
    return max(0, int(np.floor(np.log2(len(array)))) - maxk_offset)


def plot_binning(array, maxk_offset=3, **kwargs):
    """ Produce a plot showing how the error evolves as function of binsize """
    
    maxk = int(np.floor(np.log2(len(array)))) - maxk_offset
    if maxk <= 0:
        raise ValueError("Array to small for binning analysis" +
                         " (try choosing smaller maxk_offset)")
    binsizes = []
    errors = []
    for k in range(maxk):
        binsize=2**k
        array_bins = resample_bin(array, binsize)
        binsizes.append(binsize)
        errors.append(err(array_bins))
    plt.semilogx(binsizes, errors)
    plt.show()

def autocorr(data, nmin=0, nmax=None, normalize=True):
    """ Compute autocorrelation function for a given timeseries
    
    Args:
        data (np.array):  the data for which to compute the autocorrelation
        normalize (bool): flag, whether to normalize autocorrelation function
    Returns:
        float: full autocorrelation function with positive lag
    """
    if not isinstance(data, np.ndarray):
        raise ValueError("data not of type numpy.array")

    mean = np.mean(data[nmin:nmax])
    data_normalized = data[nmin:nmax] - mean
    corr = np.correlate(data_normalized, data_normalized,  mode='full')
    autocorr = corr[corr.size // 2:]
    if normalize:
        autocorr /= autocorr[0]

    return autocorr



def _axes_decorator(plot_func):
    import matplotlib.pyplot as plt
    
    @wraps(plot_func)
    def _wrapped_plot_func(*args, **kwargs):
        #read axes label 'ax' from kwargs
        axes = None

        for key in kwargs:
            if key=='ax':
                axes = kwargs[key]

        if not axes:
            fig = plt.figure()
            axes = fig.gca()
            kwargs.update({'ax': axes})
        
        return plot_func(*args, **kwargs)

    return _wrapped_plot_func 



@_axes_decorator
def plot_autocorr(timeseries, nmins=None, nmaxs=None,
                  max_time=20, plot_mean=False, ax=None, **kwargs):
    """ Plot autocorrelation functions for a list of timeseries
    
    Args:
        list of arrays (np.array): The timeseries whose autocorrelation function
                                   to plot
        max_time (int):            maximum time for which to plot the 
                                   autocorrelation function 
        plot_mean (bool):          flag, whether to plot mean and error of the 
                                   autocorrelation functions
        ax:                        Axes for plotting, **optional**. 
                                   Default: Create new figure and axes
    Returns:
        Handle to plot
    """
    if isinstance(timeseries, np.ndarray):
        timeseries = [timeseries]


        
    # Compute autocorrelation for time window
    n_timeseries = len(timeseries)
    autocorrs_arr = np.zeros((n_timeseries, max_time))
    for idx, (seed, data) in enumerate(timeseries.items()):
        max_time_seed = min(max_time, len(data))
        if max_time > 0:
            if nmins == None:
                auto = autocorr(data, 0)[:max_time_seed]
            else:
                auto = autocorr(data, nmins[seed])[:max_time_seed]
            autocorrs_arr[idx, :len(auto)] = auto

    # Plot autocorrelations for timeseries
    autocorrs_arr = np.abs(autocorrs_arr)
    for idx in range(n_timeseries):
        ax.plot(range(max_time), autocorrs_arr[idx, :], label="{}".format(idx))

    # Plot averaged autocorrelation function
    if plot_mean:
        autocorr_avg = mean(autocorrs_arr, axis=0)
        autocorr_err = sem(autocorrs_arr, axis=0)
        ax.errorbar(range(max_time), autocorr_avg, autocorr_err, color="black",
                    label="mean", linewidth=2)

    ax.set_xlabel("time")
    ax.set_ylabel("autocorrelation")
    ax.set_yscale('log')
    return ax


@_axes_decorator
def plot_timeseries(timeseries, nmins=None, ax=None, **kwargs):
    """ Plot autocorrelation functions for a list of timeseries
    
    Args:
        list of arrays (np.array): The timeseries to plot
        ax:                        Axes for plotting, **optional**. 
                                   Default: Create new figure and axes
    Returns:
        Handle to plot
    """
    if isinstance(timeseries, np.ndarray):
        timeseries = [timeseries]
    
    for seed, data in timeseries.items(): 
        if nmins != None:
            p = ax.plot(range(len(data)), data, label="{} (from {})".format(
                                                       seed, nmins[seed]))
            color = p[-1].get_color()
            ax.axvline(x=nmins[seed], color=color)
        else:
            ax.plot(range(len(data)), data, label="{}".format(seed))

    ax.set_xlabel("time")
    ax.set_ylabel("data")
    return ax


def auto_window(taus, c):
    m = np.arange(len(taus)) < c * taus
    if np.any(m):
        return np.argmin(m)
    return len(taus) - 1

def autocorr_time(timeseries, nmins=None, nmaxs=None, max_time=20, c=5.0):
    """ Compute estimate for the autocorrelation time    
    Args:
        list of arrays (np.array): The timeseries whose autocorrelation function
                                   to plot
    Returns:
        autocorrelation time according to dfm.io/posts/autocorr
    """
    
    if isinstance(timeseries, np.ndarray):
        timeseries = [timeseries]

    f = np.zeros(max_time)
    n=0
    for seed, data in timeseries.items():
        if nmins == None:
            nmin = 0
        else:
            nmin = nmins[seed]
        if nmaxs == None:
            nmax = None
        else:
            nmax = nmaxs[seed]
        
        if max_time > 0:
            corr = autocorr(data, nmin=nmin, nmax=nmax)[:max_time]
            corr_pad_zeros = np.zeros_like(f)
            corr_pad_zeros[:len(corr)] = corr
            f += corr_pad_zeros
            n += 1
    f /= n

    if max_time > 0:
        taus = 2.0*np.cumsum(f) - 1.0
        window = auto_window(taus, c)
        return taus[window]
    else:
        return 0


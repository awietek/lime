# -*- coding: utf-8 -*-
"""
PyLime Python module for lightweight Monte Carlo estimation

:author: Alexander Wietek
"""
from __future__ import absolute_import, division, print_function
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt

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
    return array[:(array.size // binsize) * binsize].reshape(-1, binsize).mean(axis=1)

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
    A_resampled = np.zeros_like(A)
    n_seeds = A.shape[0]
    for seed in range(n_seeds):
        A_resampled[seed,:] = np.mean(np.delete(A, seed, axis=0), axis=0)
    return A_resampled

def err(array, axis=0):
    """ Compute standard error of a given sample """
    return stats.sem(array, axis)

def plot_binning(array, maxk_offset=5, **kwargs):
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

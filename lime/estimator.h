// Copyright 2018 Alexander Wietek - All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LIME_ESTIMATOR_H
#define LIME_ESTIMATOR_H

#include <string>
#include <sstream>
#include <limits>

#include <lime/complex.h>

#define LIME_REAL_ERROR -1

namespace lime
{
  using uint64 = unsigned long;
  using complex::real_t;

  enum convergence_t { converged, notconverged, maybeconverged };
  
    /*!
      Estimator is a class template for performing measurements of 
      correlated data. It estimates the mean, autocorrelation time
      and error of a given timeseries by storing only O(log(N)) elements,
      where N is the length of the timeseries. The algorithm is adapted
      form the ALPS library, and descirbed in arXiv:0906.0943.

      Usage:
      @code
      #include <lime/all.h>

      lime::Estimator<double> est;
      
      for(int step = 0; step <= 10; ++step)
        est << (double) step;
      
      // Get mean, error, aud autocorrelation time
      printf("mean: %f, error: %f, tau: %f\n", est.mean(), est.error(), est.tau());
      
      // Detailed output with binning
      std::cout << est.output(true) << std::endl;

      @endcode
      @tparam coeff_t type of data for measurements

    */
  template <class coeff_t = double>
  class Estimator
  {
    using real_t = complex::real_t<coeff_t>;

  public:
    Estimator();    

    /// returns length of time series.
    uint64 size() const;
    
    // return mean value of time series
    coeff_t mean() const;

    // return variance of time series
    real_t variance() const;

    /// error estimated from bin i, or from default bin if < 0
    real_t error(int i = LIME_REAL_ERROR) const;
    
    /// returns autocorrelation time
    real_t tau() const;

    /// returns whether correlated errors have converged
    convergence_t convergence() const;

    /// output string of binning
    std::string output(bool print_bins=false) const;
    int binning_depth() const;
    
    /// add measurement to time series
    void operator<<(const coeff_t& x);

  private:
    std::vector<coeff_t> sum_;           // sum of measurements in the bin
    std::vector<real_t> sum2_;           // sum of the squares
    std::vector<uint64> bin_entries_;    // number of measurements
    std::vector<coeff_t> last_bin_;      // the last value measured
    uint64 size_;            // total number of measurements (=bin_entries_[0])

    inline coeff_t binmean(int i) const;
    inline real_t binvariance(int i) const;
    
  };

  template <class coeff_t>
  Estimator<coeff_t>::Estimator() : size_(0) {}

  template <class coeff_t>
  uint64 Estimator<coeff_t>::size() const
  { return size_; }

  template <class coeff_t>
  coeff_t Estimator<coeff_t>::mean() const
  {
    assert(size() > 0); // need at least one element for mean
    return sum_[0] / (real_t)size();
  }
  
  template <class coeff_t>
  real_t<coeff_t> Estimator<coeff_t>::variance() const
  {
    assert(size() > 0); // need at least one element for variance
    if (size() == 1) return std::numeric_limits<real_t>::infinity();
    else
      {
	real_t variance = 
	  (sum2_[0] - complex::norm(sum_[0]) / (real_t)size()) /
	  ((real_t)(size() - 1));
	return variance;
      }
  }

  // error estimated from bin i, or from default bin if <0
  template <class coeff_t>
  real_t<coeff_t> Estimator<coeff_t>::error(int i) const
  {
    assert(i < (int)binning_depth()); // invalid binning depth
    assert(size() > 0); // need at least one element for error

    if (i < 0) i = binning_depth()-1;
    uint64 binsize_ = bin_entries_[i];
    real_t correction = 
      binvariance(0) < 1e-12 ? 1. : binvariance(i) / binvariance(0);

    correction *= (variance() / (real_t)(binsize_ - 1));
    return std::sqrt(correction);
  }

  template <class coeff_t>
  real_t<coeff_t> Estimator<coeff_t>::tau() const
  {
    assert(size() > 0); // need at least one element for autocorrelation
    if( binning_depth() >= 2 )
      {
	real_t er = error();
	return er*er*size()/variance();
      }
    else return std::numeric_limits<real_t>::infinity();      
  }

  template <class coeff_t>
  convergence_t Estimator<coeff_t>::convergence() const
  {
    real_t err = std::abs(error());
    int range = 4;
    if (binning_depth() < range) return maybeconverged;
    else
      {
	convergence_t conv = converged;
	for (int i = binning_depth() - range; i < binning_depth()-1; ++i)
	  {
	    real_t this_err(error(i));
	    if (std::abs(this_err) >= err)
	      conv = converged;
	    else if (std::abs(this_err) < 0.824 * err)
	      conv = notconverged;
	    else if (std::abs(this_err) < 0.9 * err && conv != notconverged)
	      conv = maybeconverged;
	  }
	return conv;
      }
  }
  
  template <class coeff_t>
  std::string Estimator<coeff_t>::output(bool print_bins) const
  {
    std::stringstream ss;
    ss << mean() << " +- " << error(-1) << ", tau: " << tau(); 
    if (convergence() == notconverged)
      ss << " NOT converged";
    else if (convergence() == maybeconverged)
      ss << " maybe converged";
    else if (convergence() == converged)
      ss << " converged";
    if(print_bins)
      {
	ss << std::endl;
	for (int i = 0; i < binning_depth(); ++i)
	  ss << " bin[" << i <<"] size:" << bin_entries_[i] << ", value: " 
	     << mean() << " +- " << error(i) << std::endl;
      }
    return ss.str();
  }
 
  template <class coeff_t>
  int Estimator<coeff_t>::binning_depth() const 
  { return  ( int(sum_.size()) - 7 < 1 ) ? 1 : int(sum_.size())-7; }
 
  template <class coeff_t>
  void Estimator<coeff_t>::operator<<(const coeff_t& x)
  {
    // set sizes if starting additions
    if(size_ == 0)
      {
	last_bin_.resize(1);
	sum_.resize(1);
	sum2_.resize(1);
	bin_entries_.resize(1);
      }

    // store x, x^2
    last_bin_[0] = x;
    sum_[0] += x;
    sum2_[0] += complex::norm(x);

    uint64 i = size_;
    size_++;
    bin_entries_[0]++;
    uint64 binlen = 1;
    std::size_t bin = 0;

    // binning
    do
      {
	if(i&1)
	  {
	    // a bin is filled
	    binlen *= 2;
	    bin++;
	    if(bin >= last_bin_.size())
	      {
		last_bin_.resize(std::max(bin+1, last_bin_.size()));
		sum_.resize(std::max(bin+1, sum_.size()));
		sum2_.resize(std::max(bin+1, sum2_.size()));
		bin_entries_.resize(std::max(bin+1, bin_entries_.size()));
	      }

	    coeff_t x1=(sum_[0] - sum_[bin]);
	    x1 /= (real_t)binlen;

	    real_t y1 = std::norm(x1);

	    last_bin_[bin] = x1;
	    sum2_[bin] += y1;
	    sum_[bin] = sum_[0];
	    bin_entries_[bin]++;
	  }
	else
	  break;
      } while ( i >>= 1);
  }

  template <class coeff_t>
  inline coeff_t Estimator<coeff_t>::binmean(int i) const
  {
    return sum_[i] / ((real_t)(bin_entries_[i]) * ((uint64)1<<i));
  }

  template <class coeff_t>
  inline real_t<coeff_t> Estimator<coeff_t>::binvariance(int i) const
  {
    real_t retval = sum2_[i];
    retval /= (real_t)bin_entries_[i];
    retval -= complex::norm(binmean(i));
    return retval;
  }
 
}

#endif

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

#include <vector>
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
    using scalar_t = complex::scalar_t<coeff_t>;
    using real_scalar_t = complex::real_scalar_t<coeff_t>;
    using complex_scalar_t = complex::complex_scalar_t<coeff_t>;
    using real_t = complex::real_t<coeff_t>;
    using complex_t = complex::complex_t<coeff_t>;

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

    // /// returns whether correlated errors have converged
    // convergence_t convergence() const;

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

    coeff_t binmean(int i) const;
    real_t binvariance(int i) const;
    
  };

}

#endif

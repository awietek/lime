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

#ifndef LIME_TIMESERIES_H
#define LIME_TIMESERIES_H

#include <algorithm>
#include <numeric>

#include <lime/complex.h>
#include <lime/acor.h>

namespace lime
{
  using uint64 = unsigned long;
  using complex::real_t;

  template <class coeff_t = double>
  class Timeseries
  {
    using real_t = complex::real_t<coeff_t>;
    using vector_t = std::vector<coeff_t>;
    using iterator_t = typename vector_t::iterator;
    using const_iterator_t = typename vector_t::const_iterator;


  public:
    Timeseries() = default;
    Timeseries(const vector_t& series);
    uint64 size() const;
    coeff_t mean() const;
    vector_t autocovariance(uint64 maxtime = 20) const;
    std::pair<real_t, real_t> error_tau() const;
    real_t error() const;
    std::string output() const;

    void operator<<(const coeff_t& x);
    coeff_t& operator[](const int& idx);

    iterator_t begin() { return series_.begin(); }
    iterator_t end() { return series_.end(); }
    const_iterator_t begin() const { return series_.begin(); }
    const_iterator_t end() const { return series_.end(); }
    const_iterator_t cbegin() const { return series_.cbegin(); }
    const_iterator_t cend() const { return series_.cend(); }

  private:
    vector_t series_;    
  };

  template <class coeff_t>
  Timeseries<coeff_t>::Timeseries(const vector_t& series)
    : series_(series) {}
 
  template <class coeff_t>
  uint64 Timeseries<coeff_t>::size() const
  { return series_.size(); }
  
  template <class coeff_t>
  coeff_t Timeseries<coeff_t>::mean() const
  { 
    return std::accumulate(series_.begin(), series_.end(), 0.0) / 
      (coeff_t)size(); 
  }

  template <class coeff_t>
  std::vector<coeff_t> Timeseries<coeff_t>::autocovariance(uint64 maxtime) const
  {
    uint64 L = size();
    assert(maxtime < L); // Max time for autocorr < length of Timeseries

    // Compute series with mean subtracted
    coeff_t mn = mean();
    vector_t series_normalized_ = series_;
    std::for_each(series_normalized_.begin(), series_normalized_.end(), 
		  [](coeff_t& x) { x -= mean;});
    
    // Compute the autocovariance
    vector_t autocov(maxtime, 0.0);
    for (uint64 t = 0; t < maxtime; t++)
      {
	for (uint64 n = 0; n < L - t; n++)
	  autocov[t] += series_normalized_[n] * series_normalized_[n + t];
	autocov[t] /= (coeff_t)(L - t);
      }
    return autocov;
  }

  template <class coeff_t>
  std::pair<real_t<coeff_t>, real_t<coeff_t>> Timeseries<coeff_t>::error_tau() const
  {
    double mean, sigma, tau;
    std::vector<double> work(series_.begin(), series_.end());
    acor::acor(&mean, &sigma, &tau, work.data(), size());
    return {(real_t) sigma, (real_t) tau};
  }

  template <class coeff_t>
  real_t<coeff_t> Timeseries<coeff_t>::error() const
  {
    auto err_tau = error_tau();
    return err_tau.first;
  }

  template <class coeff_t>
  std::string Timeseries<coeff_t>::output() const
  {
    auto err_tau = error_tau();
    std::stringstream ss;
    ss << mean() << " +- " << err_tau.first << ", tau: " << err_tau.second; 
    return ss.str();
  }
  template <class coeff_t>
  void Timeseries<coeff_t>::operator<<(const coeff_t& x)
  { series_.push_back(x); }

  template <class coeff_t>
  coeff_t& Timeseries<coeff_t>::operator[](const int& idx)
  { return series_[idx]; }
}

#endif

#include <numeric>

#include <lila/all.h>
#include <lime/complex.h>
#include <lime/print.h>
#include <lime/arithmetics.h>

#include "timeseries.h"

namespace lime
{

  template <class coeff_t>
  Timeseries<coeff_t>::Timeseries(const vector_t& series)
    : series_(series) {}
 
  template <class coeff_t>
  uint64 Timeseries<coeff_t>::size() const
  { return series_.size(); }
  
  template <class coeff_t>
  coeff_t Timeseries<coeff_t>::mean() const
  { 
    return arithmetics::accumulate(series_) / (scalar_t)size(); 
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
		  [&mn](coeff_t& x) { x -= mn;});
    
    // Compute the autocovariance
    vector_t autocovs;
    for (uint64 t = 0; t < maxtime; t++)
      {
	auto autocov = arithmetics::mult(series_normalized_[0], series_normalized_[0 + t]);
	for (uint64 n = 1; n < L - t; n++)
	  autocov += arithmetics::mult(series_normalized_[n], series_normalized_[n + t]);
	autocov /= (scalar_t)(L - t);
	autocovs.push_back(autocov);
      }
    return autocovs;
  }

  template <class coeff_t>
  real_t<coeff_t> Timeseries<coeff_t>::variance() const
  {
    assert(size() > 0);
    if (size() == 1) return arithmetics::infinity(series_[0]);
    else
      {
	complex::real_t<coeff_t> sum2 = arithmetics::norm(series_[0]);
	for (int i=1; i<size(); ++i)
	  sum2 += arithmetics::norm(series_[i]);
	sum2 /= (real_scalar_t)size(); 
	auto mn = mean();
	return sum2 - arithmetics::norm(mn);
      }
  }

  template <class coeff_t>
  real_t<coeff_t> Timeseries<coeff_t>::error() const
  {
    return arithmetics::sqrt(variance());
  }

  template <class coeff_t>
  std::string Timeseries<coeff_t>::output() const
  {
    return print_mean_err(mean(), error());
  }
  template <class coeff_t>
  void Timeseries<coeff_t>::operator<<(const coeff_t& x)
  { series_.push_back(x); }

  template <class coeff_t>
  coeff_t& Timeseries<coeff_t>::operator[](const int& idx)
  { return series_[idx]; }

  template <class coeff_t>
  const coeff_t& Timeseries<coeff_t>::operator[](const int& idx) const
  { return series_[idx]; }


  template class Timeseries<float>;
  template class Timeseries<double>;
  template class Timeseries<std::complex<float>>;
  template class Timeseries<std::complex<double>>;

  template class Timeseries<lila::Vector<float>>;
  template class Timeseries<lila::Vector<double>>;
  template class Timeseries<lila::Vector<std::complex<float>>>;
  template class Timeseries<lila::Vector<std::complex<double>>>;

  template class Timeseries<lila::Matrix<float>>;
  template class Timeseries<lila::Matrix<double>>;
  template class Timeseries<lila::Matrix<std::complex<float>>>;
  template class Timeseries<lila::Matrix<std::complex<double>>>;

}

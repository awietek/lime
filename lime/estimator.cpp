#include <cassert>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>

#include <lila/all.h>

#include "estimator.h"

#include <lime/arithmetics.h>

namespace lime
{
  template <class coeff_t>
  Estimator<coeff_t>::Estimator() : size_(0) {}

  template <class coeff_t>
  uint64 Estimator<coeff_t>::size() const
  { return size_; }

  template <class coeff_t>
  coeff_t Estimator<coeff_t>::mean() const
  {
    assert(size() > 0); // need at least one element for mean
    return sum_[0] / (scalar_t)size();
  }
  
  template <class coeff_t>
  real_t<coeff_t> Estimator<coeff_t>::variance() const
  {
    assert(size() > 0); // need at least one element for variance
    if (size() == 1) return std::numeric_limits<real_t>::infinity();
    else
      {
	real_t variance = 
	  (sum2_[0] - arithmetics::norm(sum_[0]) / (real_scalar_t)size()) /
	  ((real_scalar_t)(size() - 1));
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

    // real_t correction = 
    //   binvariance(0) < 1e-12 ? 1. : binvariance(i) / binvariance(0);
    real_t correction = 
      arithmetics::div_zero_to_one(binvariance(i), binvariance(0));

    // correction *= (variance() / (real_scalar_t)(binsize_ - 1));
    correction = arithmetics::mult(correction, 
				   variance() / (real_scalar_t)(binsize_ - 1));
    return arithmetics::sqrt(correction);
  }

  template <class coeff_t>
  real_t<coeff_t> Estimator<coeff_t>::tau() const
  {
    assert(size() > 0); // need at least one element for autocorrelation
    // if( binning_depth() >= 2 )
    //   {
    real_t er = error();
    real_t tau = arithmetics::mult(er, er) * (real_scalar_t)size();
    return arithmetics::div(tau, variance());
    //   }
    // else return std::numeric_limits<real_t>::infinity();      
  }

  // template <class coeff_t>
  // convergence_t Estimator<coeff_t>::convergence() const
  // {
  //   real_t err = arithmetics::abs(error());
  //   int range = 4;
  //   if (binning_depth() < range) return maybeconverged;
  //   else
  //     {
  // 	convergence_t conv = converged;
  // 	for (int i = binning_depth() - range; i < binning_depth()-1; ++i)
  // 	  {
  // 	    real_t this_err(error(i));
  // 	    if (arithmetics::abs(this_err) >= err)
  // 	      conv = converged;
  // 	    else if (arithmetics::abs(this_err) < 0.824 * err)
  // 	      conv = notconverged;
  // 	    else if (arithmetics::abs(this_err) < 0.9 * err && conv != notconverged)
  // 	      conv = maybeconverged;
  // 	  }
  // 	return conv;
  //     }
  // }
  
  template <class coeff_t>
  std::string Estimator<coeff_t>::output(bool print_bins) const
  {
    std::stringstream ss;
    // ss << mean() << " +- " << error(-1) << ", tau: " << tau(); 
    // // if (convergence() == notconverged)
    // //   ss << " NOT converged";
    // // else if (convergence() == maybeconverged)
    // //   ss << " maybe converged";
    // // else if (convergence() == converged)
    // //   ss << " converged";
    // if(print_bins)
    //   {
    // 	ss << std::endl;
    // 	for (int i = 0; i < binning_depth(); ++i)
    // 	  ss << " bin[" << i <<"] size:" << bin_entries_[i] << ", value: " 
    // 	     << mean() << " +- " << error(i) << std::endl;
    //   }
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
    sum2_[0] += arithmetics::norm(x);

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
	    x1 /= (scalar_t)binlen;

	    real_t y1 = arithmetics::norm(x1);

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
  coeff_t Estimator<coeff_t>::binmean(int i) const
  {
    // return sum_[i] / ((real_t)(bin_entries_[i]) * ((uint64)1<<i));
    return sum_[i] / ((scalar_t)(bin_entries_[i]) * (scalar_t)((uint64)1<<i));
  }

  template <class coeff_t>
  real_t<coeff_t> Estimator<coeff_t>::binvariance(int i) const
  {
    real_t retval = sum2_[i];
    retval /= (real_scalar_t)bin_entries_[i];
    retval -= arithmetics::norm(binmean(i));
    return retval;
  }
 
  template class Estimator<float>;
  template class Estimator<double>;
  template class Estimator<std::complex<float>>;
  template class Estimator<std::complex<double>>;

  template class Estimator<lila::Vector<float>>;
  template class Estimator<lila::Vector<double>>;
  template class Estimator<lila::Vector<std::complex<float>>>;
  template class Estimator<lila::Vector<std::complex<double>>>;

  template class Estimator<lila::Matrix<float>>;
  template class Estimator<lila::Matrix<double>>;
  template class Estimator<lila::Matrix<std::complex<float>>>;
  template class Estimator<lila::Matrix<std::complex<double>>>;

}

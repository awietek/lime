#include "collection.h"

#include <lime/estimator.h>
#include <lime/timeseries.h>

namespace lime {

  // template <class key_t, class estimator_t>
  // estimator_t Collection<key_t, estimator_t>::operator[](key_t const& key) const
  // {
  //   // Try to insert (returns iterator to element if already present)
  //   auto r = keys_estimators_.insert({key, estimator_t()});

  //   // if key does not already exists, add key
  //   if (r.second) keys_.push_back(key);

  //   // return new or old estimator
  //   return r.first->second;
  // }

  template <class key_t, class estimator_t>
  estimator_t& Collection<key_t, estimator_t>::operator[](key_t const& key)
  {
    auto r = keys_estimators_.insert({key, estimator_t()});
    if (r.second) keys_.push_back(key);
    return r.first->second;
  }

  template class Collection<int, Estimator<float>>;
  template class Collection<int, Estimator<double>>;
  template class Collection<int, Estimator<std::complex<float>>>;
  template class Collection<int, Estimator<std::complex<double>>>;

  template class Collection<std::string, Estimator<float>>;
  template class Collection<std::string, Estimator<double>>;
  template class Collection<std::string, Estimator<std::complex<float>>>;
  template class Collection<std::string, Estimator<std::complex<double>>>;

  template class Collection<int, Timeseries<float>>;
  template class Collection<int, Timeseries<double>>;
  template class Collection<int, Timeseries<std::complex<float>>>;
  template class Collection<int, Timeseries<std::complex<double>>>;

  template class Collection<std::string, Timeseries<float>>;
  template class Collection<std::string, Timeseries<double>>;
  template class Collection<std::string, Timeseries<std::complex<float>>>;
  template class Collection<std::string, Timeseries<std::complex<double>>>;

}

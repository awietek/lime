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

#include <vector>
#include <lime/complex.h>

namespace lime
{
  using uint64 = unsigned long;
  using complex::real_t;

  template <class coeff_t = double>
  class Timeseries
  {
    using scalar_t = complex::scalar_t<coeff_t>;
    using real_scalar_t = complex::real_scalar_t<coeff_t>;
    using complex_scalar_t = complex::complex_scalar_t<coeff_t>;
    using real_t = complex::real_t<coeff_t>;
    using complex_t = complex::complex_t<coeff_t>;

    using vector_t = std::vector<coeff_t>;
    using iterator_t = typename vector_t::iterator;
    using const_iterator_t = typename vector_t::const_iterator;

  public:
    using data_t = coeff_t;

    Timeseries() = default;
    Timeseries(const vector_t& series);
    uint64 size() const;
    coeff_t mean() const;
    vector_t autocovariance(uint64 maxtime = 20) const;
    real_t variance() const;
    real_t error() const;
    std::string output() const;

    void operator<<(coeff_t const& x);
    coeff_t& operator[](int const& idx);
    const coeff_t& operator[](int const& idx) const;

    iterator_t begin() { return series_.begin(); }
    iterator_t end() { return series_.end(); }
    const_iterator_t begin() const { return series_.begin(); }
    const_iterator_t end() const { return series_.end(); }
    const_iterator_t cbegin() const { return series_.cbegin(); }
    const_iterator_t cend() const { return series_.cend(); }

    coeff_t* data() { return series_.data();}
    const coeff_t* data() const { return series_.data();}

  private:
    vector_t series_;    
  };

}

#endif

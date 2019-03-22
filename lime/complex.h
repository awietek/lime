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

#ifndef LIME_COMPLEX_H
#define LIME_COMPLEX_H

#include <complex>

namespace lime {
  namespace complex {
    namespace detail {
    
      template <class coeff_t>
      struct real_type_struct {
	typedef coeff_t type;
      };

      template <class coeff_t>
      struct real_type_struct<std::complex<coeff_t> > {
	typedef coeff_t type;
      };

      template <class coeff_t>
      struct complex_type_struct {
	typedef std::complex<coeff_t> type;
      };

      template <class coeff_t>
      struct complex_type_struct<std::complex<coeff_t> > {
	typedef std::complex<coeff_t> type;
      };

    }

    template <class coeff_t>
    using real_t = typename detail::real_type_struct<coeff_t>::type;
    
    template <class coeff_t>
    using complex_t = typename detail::complex_type_struct<coeff_t>::type;

    inline float real (float x) { return x; }
    inline double real (double x) { return x; }
    inline float real (std::complex<float> x) { return x.real(); }
    inline double real (std::complex<double> x) { return x.real(); }
    
    inline float imag (float) { return 0.; }
    inline double imag (double) { return 0.; }
    inline float imag (std::complex<float> x) { return x.imag(); }
    inline double imag (std::complex<double> x) { return x.imag(); }
    
    inline float conj (float x) { return x; }
    inline double conj (double x) { return x; }
    inline std::complex<float> conj (std::complex<float> x) { return std::conj(x); }
    inline std::complex<double> conj (std::complex<double> x) { return std::conj(x); }

    inline float norm (float x) { return x*x; }
    inline double norm (double x) { return x*x; }
    inline std::complex<float> norm (std::complex<float> x) { return std::norm(x); }
    inline std::complex<double> norm (std::complex<double> x) { return std::norm(x); }

  }
}

#endif

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

#ifndef LIME_ARITHMETICS_H
#define LIME_ARITHMETICS_H

#include <lime/complex.h>
#include <lila/all.h>

namespace lime {
  namespace arithmetics {

    // Division of observables
    template <class coeff_t>
    coeff_t div(coeff_t const& a, coeff_t const& b);

    template <class coeff_t>
    lila::Vector<coeff_t> 
    div(lila::Vector<coeff_t> const& a, lila::Vector<coeff_t> const& b);

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    div(lila::Matrix<coeff_t> const& a, lila::Matrix<coeff_t> const& b);


    // Division of observables (divide by zero defaults to 1.)
    template <class coeff_t>
    coeff_t div_zero_to_one(coeff_t const& a, coeff_t const& b);

    template <class coeff_t>
    lila::Vector<coeff_t> 
    div_zero_to_one(lila::Vector<coeff_t> const& a, lila::Vector<coeff_t> const& b);

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    div_zero_to_one(lila::Matrix<coeff_t> const& a, lila::Matrix<coeff_t> const& b);


    // Multiplication of observables
    template <class coeff_t>
    coeff_t mult(coeff_t const& a, coeff_t const& b);

    template <class coeff_t>
    lila::Vector<coeff_t> 
    mult(lila::Vector<coeff_t> const& a, lila::Vector<coeff_t> const& b);

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    mult(lila::Matrix<coeff_t> const& a, lila::Matrix<coeff_t> const& b);


    // square root of observables
    template <class coeff_t>
    coeff_t sqrt(coeff_t const& a);

    template <class coeff_t>
    lila::Vector<coeff_t> 
    sqrt(lila::Vector<coeff_t> const& a);

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    sqrt(lila::Matrix<coeff_t> const& a);


    // absolute value of observables
    template <class coeff_t>
    coeff_t abs(coeff_t const& a);

    template <class coeff_t>
    lila::Vector<coeff_t> 
    abs(lila::Vector<coeff_t> const& a);

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    abs(lila::Matrix<coeff_t> const& a);

    // norm (entry squared (cplx::conj)) of observables
    template <class coeff_t>
    complex::real_t<coeff_t> norm(coeff_t const& a);

    template <class coeff_t>
    lila::Vector<complex::real_t<coeff_t>> 
    norm(lila::Vector<coeff_t> const& a);

    template <class coeff_t>
    lila::Matrix<complex::real_t<coeff_t>> 
    norm(lila::Matrix<coeff_t> const& a);
    
    // sum of observables
    template <class coeff_t>
    coeff_t accumulate(std::vector<coeff_t> const& vec);

    template <class coeff_t>
    lila::Vector<coeff_t>
    accumulate(std::vector<lila::Vector<coeff_t>> const& vec);

    template <class coeff_t>
    lila::Matrix<coeff_t>
    accumulate(std::vector<lila::Matrix<coeff_t>> const& vec);

    // infinity for returning infinite variance for one measurement
    template <class coeff_t>
    complex::real_t<coeff_t>
    infinity(coeff_t const& vec);

    template <class coeff_t>
    lila::Vector<complex::real_t<coeff_t>>
    infinity(lila::Vector<coeff_t> const& vec);

    template <class coeff_t>
    lila::Matrix<complex::real_t<coeff_t>>
    infinity(lila::Matrix<coeff_t> const& mat);


  }
}

#endif

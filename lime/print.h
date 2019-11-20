// Copyright 2019 Alexander Wietek - All Rights Reserved.
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

#ifndef LIME_PRINT_H
#define LIME_PRINT_H

#include <lime/complex.h>
#include <lila/all.h>

namespace lime {
  template <class coeff_t>
  std::string print_mean_err(coeff_t const& mean, 
			     complex::real_t<coeff_t> const& err, 
			     int precision=10);

  template <class coeff_t>
  std::string print_mean_err(lila::Vector<coeff_t> const& mean, 
			     lila::Vector<complex::real_t<coeff_t>> const& err, 
			     std::string sep="\n", 
			     int precision=10);

  template <class coeff_t>
  std::string print_mean_err(lila::Matrix<coeff_t> const& mean, 
			     lila::Matrix<complex::real_t<coeff_t>> const& err, 
			     std::string seprow="\n", std::string sepcol=", ",
			     int precision=10);


  template <class coeff_t>
  std::string print_mean_err_tau(coeff_t const& mean, 
				 complex::real_t<coeff_t> const& err, 
				 complex::real_t<coeff_t> const& tau, 
				 int precision=10);


  template <class coeff_t>
  std::string print_mean_err_tau(lila::Vector<coeff_t> const& mean, 
				 lila::Vector<complex::real_t<coeff_t>> const& err, 
				 lila::Vector<complex::real_t<coeff_t>> const& tau, 
				 std::string sep="\n", 
				 int precision=10);

  template <class coeff_t>
  std::string print_mean_err_tau(lila::Matrix<coeff_t> const& mean, 
				 lila::Matrix<complex::real_t<coeff_t>> const& err, 
				 lila::Matrix<complex::real_t<coeff_t>> const& tau, 
				 std::string seprow="\n", std::string sepcol=", ",
				 int precision=10);

}

#endif

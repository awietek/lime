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
#ifndef LIME_TESTUTILS_H
#define LIME_TESTUTILS_H

namespace testutils
{
  template <class coeff_t>
  inline coeff_t rdm(std::mt19937& gen);

  template <>
  inline float rdm<float>(std::mt19937& gen)
  {
    std::normal_distribution<float> d{0,1}; 
    return d(gen);
  }
  template <>
  inline double rdm<double>(std::mt19937& gen)
  {
    std::normal_distribution<float> d{0,1}; 
    return d(gen);
  }
  template <>
  inline std::complex<float> rdm<std::complex<float>>(std::mt19937& gen)
  {
    std::normal_distribution<float> d{0,1}; 
    return {d(gen), d(gen)};
  }
  template <>
  inline std::complex<double> rdm<std::complex<double>>(std::mt19937& gen)
  {
    std::normal_distribution<double> d{0,1}; 
    return {d(gen), d(gen)};
  }
}
#endif

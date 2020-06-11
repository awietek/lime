// Copyright 2020 Alexander Wietek - All Rights Reserved.
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

#ifndef LIME_TYPES_H
#define LIME_TYPES_H

#include <complex>
#include <lila/all.h>

namespace lime
{
  using sscalar = float;
  using dscalar = double;
  using cscalar = std::complex<float>;
  using zscalar = std::complex<double>;

  using svector = lila::Vector<float>;
  using dvector = lila::Vector<double>;
  using cvector = lila::Vector<std::complex<float>>;
  using zvector = lila::Vector<std::complex<double>>;
  
  using smatrix = lila::Matrix<float>;
  using dmatrix = lila::Matrix<double>;
  using cmatrix = lila::Matrix<std::complex<float>>;
  using zmatrix = lila::Matrix<std::complex<double>>;

}

#endif

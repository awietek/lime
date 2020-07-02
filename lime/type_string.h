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

#ifndef LIME_HDF5_TYPE_STRING_H
#define LIME_HDF5_TYPE_STRING_H

#include <array>
#include <complex>
#include <hdf5.h>
#include <string>

#include <lime/types.h>

namespace lime {

const std::vector<std::string> all_lime_field_types{
    "IntScalar",          "UintScalar",          "LongScalar",  "UlongScalar",
    "LlongScalar",        "UllongScalar",        "FloatScalar", "DoubleScalar",
    "ComplexFloatScalar", "ComplexDoubleScalar", "FloatVector", "DoubleVector",
    "ComplexFloatVector", "ComplexDoubleVector", "FloatMatrix", "DoubleMatrix",
    "ComplexFloatMatrix", "ComplexDoubleMatrix"};

inline std::string type_string(int const &) { return "IntScalar"; }
inline std::string type_string(unsigned const &) { return "UintScalar"; }
inline std::string type_string(long const &) { return "LongScalar"; }
inline std::string type_string(unsigned long const &) { return "UlongScalar"; }
inline std::string type_string(long long const &) { return "LlongScalar"; }
inline std::string type_string(unsigned long long const &) {
  return "UllongScalar";
}

inline std::string type_string(sscalar const &) { return "FloatScalar"; }
inline std::string type_string(dscalar const &) { return "DoubleScalar"; }
inline std::string type_string(cscalar const &) { return "ComplexFloatScalar"; }
inline std::string type_string(zscalar const &) {
  return "ComplexDoubleScalar";
}

inline std::string type_string(svector const &) { return "FloatVector"; }
inline std::string type_string(dvector const &) { return "DoubleVector"; }
inline std::string type_string(cvector const &) { return "ComplexFloatVector"; }
inline std::string type_string(zvector const &) {
  return "ComplexDoubleVector";
}

inline std::string type_string(smatrix const &) { return "FloatMatrix"; }
inline std::string type_string(dmatrix const &) { return "DoubleMatrix"; }
inline std::string type_string(cmatrix const &) { return "ComplexFloatMatrix"; }
inline std::string type_string(zmatrix const &) {
  return "ComplexDoubleMatrix";
}

inline std::string type_string(std::vector<int> const &) { return "IntScalar"; }
inline std::string type_string(std::vector<unsigned int> const &) {
  return "UintScalar";
}
inline std::string type_string(std::vector<long> const &) {
  return "LongScalar";
}
inline std::string type_string(std::vector<unsigned long> const &) {
  return "UlongScalar";
}
inline std::string type_string(std::vector<long long> const &) {
  return "LlongScalar";
}
inline std::string type_string(std::vector<unsigned long long> const &) {
  return "UllongScalar";
}

inline std::string type_string(std::vector<sscalar> const &) {
  return "FloatScalar";
}
inline std::string type_string(std::vector<dscalar> const &) {
  return "DoubleScalar";
}
inline std::string type_string(std::vector<cscalar> const &) {
  return "ComplexFloatScalar";
}
inline std::string type_string(std::vector<zscalar> const &) {
  return "ComplexDoubleScalar";
}

inline std::string type_string(std::vector<svector> const &) {
  return "FloatVector";
}
inline std::string type_string(std::vector<dvector> const &) {
  return "DoubleVector";
}
inline std::string type_string(std::vector<cvector> const &) {
  return "ComplexFloatVector";
}
inline std::string type_string(std::vector<zvector> const &) {
  return "ComplexDoubleVector";
}

inline std::string type_string(std::vector<smatrix> const &) {
  return "FloatMatrix";
}
inline std::string type_string(std::vector<dmatrix> const &) {
  return "DoubleMatrix";
}
inline std::string type_string(std::vector<cmatrix> const &) {
  return "ComplexFloatMatrix";
}
inline std::string type_string(std::vector<zmatrix> const &) {
  return "ComplexDoubleMatrix";
}

} // namespace lime

#endif

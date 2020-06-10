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

#include <string>
#include <array>
#include <complex>
#include <hdf5.h>

#include <lila/all.h>

namespace lime { 
using complex = std::complex<double>;
using scomplex = std::complex<float>;

const std::vector<std::string> all_lime_field_types
  {"IntScalar", "UintScalar", "FloatScalar", "DoubleScalar",
   "ComplexFloatScalar","ComplexDoubleScalar",
   "FloatVector", "DoubleVector","ComplexFloatVector", "ComplexDoubleVector",
   "FloatMatrix", "DoubleMatrix","ComplexFloatMatrix", "ComplexDoubleMatrix"
  };

inline std::string type_string(int data)
{ return "IntScalar"; }
inline std::string type_string(unsigned int data)
{ return "UintScalar"; }
inline std::string type_string(float data)
{ return "FloatScalar"; }
inline std::string type_string(double data)
{ return "DoubleScalar"; }
inline std::string type_string(scomplex data)
{ return "ComplexFloatScalar"; }
inline std::string type_string(complex data)
{ return "ComplexDoubleScalar"; }

inline std::string type_string(lila::Vector<float> data)
{ return "FloatVector"; }
inline std::string type_string(lila::Vector<double> data)
{ return "DoubleVector"; }
inline std::string type_string(lila::Vector<scomplex> data)
{ return "ComplexFloatVector"; }
inline std::string type_string(lila::Vector<complex> data)
{ return "ComplexDoubleVector"; }

inline std::string type_string(lila::Matrix<float> data)
{ return "FloatMatrix"; }
inline std::string type_string(lila::Matrix<double> data)
{ return "DoubleMatrix"; }
inline std::string type_string(lila::Matrix<scomplex> data)
{ return "ComplexFloatMatrix"; }
inline std::string type_string(lila::Matrix<complex> data)
{ return "ComplexDoubleMatrix"; }

inline std::string type_string(std::vector<int> data)
{ return "IntScalar"; }
inline std::string type_string(std::vector<unsigned int> data)
{ return "UintScalar"; }
inline std::string type_string(std::vector<float> data)
{ return "FloatScalar"; }
inline std::string type_string(std::vector<double> data)
{ return "DoubleScalar"; }
inline std::string type_string(std::vector<scomplex> data)
{ return "ComplexFloatScalar"; }
inline std::string type_string(std::vector<complex> data)
{ return "ComplexDoubleScalar"; }

inline std::string type_string(std::vector<lila::Vector<float>> data)
{ return "FloatVector"; }
inline std::string type_string(std::vector<lila::Vector<double>> data)
{ return "DoubleVector"; }
inline std::string type_string(std::vector<lila::Vector<scomplex>> data)
{ return "ComplexFloatVector"; }
inline std::string type_string(std::vector<lila::Vector<complex>> data)
{ return "ComplexDoubleVector"; }

inline std::string type_string(std::vector<lila::Matrix<float>> data)
{ return "FloatMatrix"; }
inline std::string type_string(std::vector<lila::Matrix<double>> data)
{ return "DoubleMatrix"; }
inline std::string type_string(std::vector<lila::Matrix<scomplex>> data)
{ return "ComplexFloatMatrix"; }
inline std::string type_string(std::vector<lila::Matrix<complex>> data)
{ return "ComplexDoubleMatrix"; }

    
}

#endif

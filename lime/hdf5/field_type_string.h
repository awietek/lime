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

#ifndef LIME_HDF5_FIELD_TYPE_STRING_H
#define LIME_HDF5_FIELD_TYPE_STRING_H

#include <string>
#include <complex>
#include <hdf5.h>

#include <lila/all.h>

namespace lime { namespace hdf5 {

using complex = std::complex<double>;
using scomplex = std::complex<float>;

inline std::string field_type_string(int data)
{ return "IntSingle"; }
inline std::string field_type_string(unsigned int data)
{ return "UintSingle"; }
inline std::string field_type_string(float data)
{ return "FloatSingle"; }
inline std::string field_type_string(double data)
{ return "DoubleSingle"; }
inline std::string field_type_string(scomplex data)
{ return "ScomplexSingle"; }
inline std::string field_type_string(complex data)
{ return "ComplexSingle"; }

inline std::string field_type_string(lila::Vector<float> data)
{ return "FloatVector"; }
inline std::string field_type_string(lila::Vector<double> data)
{ return "DoubleVector"; }
inline std::string field_type_string(lila::Vector<scomplex> data)
{ return "ScomplexVector"; }
inline std::string field_type_string(lila::Vector<complex> data)
{ return "ComplexVector"; }

inline std::string field_type_string(lila::Matrix<float> data)
{ return "FloatMatrix"; }
inline std::string field_type_string(lila::Matrix<double> data)
{ return "DoubleMatrix"; }
inline std::string field_type_string(lila::Matrix<scomplex> data)
{ return "ScomplexMatrix"; }
inline std::string field_type_string(lila::Matrix<complex> data)
{ return "ComplexMatrix"; }

std::string field_type_string_from_dataset(hid_t dataset_id);

    
}}

#endif

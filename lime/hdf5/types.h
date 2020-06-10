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

#ifndef LIME_HDF5_TYPES_H
#define LIME_HDF5_TYPES_H

#include <complex>
#include <string>
#include <cassert>

#include <hdf5.h>

#define LIME_FIELD_TYPE_STRING "LimeFieldType"
#define LIME_FIELD_STATIC_EXTENSIBLE_STRING "LimeFieldStaticExtensible"

namespace lime { namespace hdf5 {
    
using complex = std::complex<double>;
using scomplex = std::complex<float>;

template <class TCoeffs> inline hid_t hdf5_datatype();

template <> inline hid_t hdf5_datatype<int>()
{ return H5T_NATIVE_INT; }
template <> inline hid_t hdf5_datatype<unsigned int>()
{ return H5T_NATIVE_UINT; }
template <> inline hid_t hdf5_datatype<float>()
{ return H5T_NATIVE_FLOAT; }
template <> inline hid_t hdf5_datatype<double>()
{ return H5T_NATIVE_DOUBLE; }
template <> inline hid_t hdf5_datatype<scomplex>()
{
  hid_t memtype = H5Tcreate(H5T_COMPOUND, 2*sizeof(float));
  H5Tinsert(memtype, "r", 0*sizeof(float), H5T_NATIVE_FLOAT);
  H5Tinsert(memtype, "i", 1*sizeof(float), H5T_NATIVE_FLOAT);
  return memtype;
}
template <> inline hid_t hdf5_datatype<complex>()
{
  hid_t memtype = H5Tcreate(H5T_COMPOUND, 2*sizeof(double));
  H5Tinsert(memtype, "r", 0*sizeof(double), H5T_NATIVE_DOUBLE);
  H5Tinsert(memtype, "i", 1*sizeof(double), H5T_NATIVE_DOUBLE);
  return memtype;
}


}}

#endif

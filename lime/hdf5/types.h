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

using lime_int = int;
using lime_uint = unsigned int;
using lime_long = long;
using lime_ulong = unsigned long;
using lime_llong = long long;
using lime_ullong = unsigned long long;

using lime_float = float;
using lime_double = double;
using lime_scomplex = std::complex<float>;
using lime_complex = std::complex<double>;

template <class TCoeffs> inline hid_t hdf5_datatype();

template <> inline hid_t hdf5_datatype<lime_int>()
{ return H5T_NATIVE_INT; }
template <> inline hid_t hdf5_datatype<lime_uint>()
{ return H5T_NATIVE_UINT; }
template <> inline hid_t hdf5_datatype<lime_long>()
{ return H5T_NATIVE_LONG; }
template <> inline hid_t hdf5_datatype<lime_ulong>()
{ return H5T_NATIVE_ULONG; }
template <> inline hid_t hdf5_datatype<lime_llong>()
{ return H5T_NATIVE_LLONG; }
template <> inline hid_t hdf5_datatype<lime_ullong>()
{ return H5T_NATIVE_ULLONG; }
template <> inline hid_t hdf5_datatype<lime_float>()
{ return H5T_NATIVE_FLOAT; }
template <> inline hid_t hdf5_datatype<lime_double>()
{ return H5T_NATIVE_DOUBLE; }
template <> inline hid_t hdf5_datatype<lime_scomplex>()
{
  hid_t memtype = H5Tcreate(H5T_COMPOUND, 2*sizeof(float));
  H5Tinsert(memtype, "r", 0*sizeof(float), H5T_NATIVE_FLOAT);
  H5Tinsert(memtype, "i", 1*sizeof(float), H5T_NATIVE_FLOAT);
  return memtype;
}
template <> inline hid_t hdf5_datatype<lime_complex>()
{
  hid_t memtype = H5Tcreate(H5T_COMPOUND, 2*sizeof(double));
  H5Tinsert(memtype, "r", 0*sizeof(double), H5T_NATIVE_DOUBLE);
  H5Tinsert(memtype, "i", 1*sizeof(double), H5T_NATIVE_DOUBLE);
  return memtype;
}


}}

#endif

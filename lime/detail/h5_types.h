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

#ifndef LIME_H5_TYPES_H
#define LIME_H5_TYPES_H

#include <complex>
#include <cassert>

#include <hdf5.h>

namespace lime
{
  namespace detail
  {
    using complex = std::complex<double>;
    using scomplex = std::complex<float>;

    template <class TCoeffs> inline hid_t hdf5_datatype();
    template <> inline hid_t hdf5_datatype<int>() { return H5T_NATIVE_INT; }
    template <> inline hid_t hdf5_datatype<unsigned int>() { return H5T_NATIVE_UINT; }
    template <> inline hid_t hdf5_datatype<float>() { return H5T_NATIVE_FLOAT; }
    template <> inline hid_t hdf5_datatype<double>() { return H5T_NATIVE_DOUBLE; }
    template <> inline hid_t hdf5_datatype<complex>()
    {
      hid_t memtype = H5Tcreate (H5T_COMPOUND, sizeof (complex));
      herr_t status = H5Tinsert (memtype, "r", 0, H5T_NATIVE_DOUBLE);
      status = H5Tinsert(memtype, "i", sizeof(double), H5T_NATIVE_DOUBLE);
      assert(status != -1);
      return memtype;
    }
    template <> inline hid_t hdf5_datatype<scomplex>()
    {
      hid_t memtype = H5Tcreate (H5T_COMPOUND, sizeof (scomplex));
      herr_t status = H5Tinsert (memtype, "r", 0, H5T_NATIVE_FLOAT);
      status = H5Tinsert(memtype, "i", sizeof(float), H5T_NATIVE_FLOAT);
      assert(status != -1);
      return memtype;
    }
  }  // namespace detail

}

#endif
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

#ifndef LIME_IO_H5_DETAIL_H
#define LIME_IO_H5_DETAIL_H

#include <hdf5.h>

#include <lime/detail/h5_types.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    inline void writeh5_array_1d(hsize_t size, const coeff_t* array, std::string filename, std::string tag)
    {
      hsize_t dims[1] = {size};

      hid_t file = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
      assert(file > -1);
      hid_t space = H5Screate_simple (1, dims, NULL);
      assert(space > -1);
      hid_t dset = H5Dcreate(file, tag.c_str(), hdf5_datatype<coeff_t>(), space, H5P_DEFAULT,
			     H5P_DEFAULT, H5P_DEFAULT);
      assert(dset > -1);
      herr_t status = H5Dwrite(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL, H5P_DEFAULT,
			       array);
      assert(status > -1);

      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);
    }

    template <class coeff_t>
    inline std::vector<coeff_t> readh5_array_1d(std::string filename, std::string tag)
    {
      hid_t file = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file > -1);
      hid_t dset = H5Dopen(file, tag.c_str(), H5P_DEFAULT);
      assert(dset > -1);
      hid_t space = H5Dget_space (dset);
      assert(space > -1);
      hsize_t dims[1];
      hid_t ndims = H5Sget_simple_extent_dims (space, dims, NULL);
      assert(ndims == 1);
      
      std::vector<coeff_t> array(dims[0], 0);
      herr_t status = H5Dread(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL, H5P_DEFAULT,
			      array.data());
      assert(status > -1);

      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);
      return array;
    }

  }  // namespace detail

}

#endif

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

#ifndef LIME_H5_UTILS_H
#define LIME_H5_UTILS_H

#include <string>
#include <hdf5.h>

namespace lime
{
  namespace detail
  {

    inline bool h5_entry_exists(hid_t file_id, std::string entry)
    { return H5Lexists(file_id, entry.c_str(), H5P_DEFAULT); }

    inline std::vector<hsize_t> h5_get_shape(hid_t dataspace_id)  
    {
      int ndims = H5Sget_simple_extent_ndims(dataspace_id);
      assert(ndims > -1);
      std::vector<hsize_t> dims(ndims, 0);
      int ndims2 = H5Sget_simple_extent_dims(dataspace_id, dims.data(), NULL);
      assert(ndims2 > -1);
      assert(ndims == ndims2);
      return dims;
    }

  }  // namespace detail

}

#endif

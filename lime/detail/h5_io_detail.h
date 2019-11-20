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

#include <string>
#include <vector>
#include <hdf5.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    void writeh5_array_1d
    (hsize_t size, coeff_t const* array, std::string filename, std::string tag);

    template <class coeff_t>
    std::vector<coeff_t> readh5_array_1d(std::string filename, std::string tag);

  }  // namespace detail
}

#endif

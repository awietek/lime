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

#ifndef LIME_HDF5_PARSE_FILE_H
#define LIME_HDF5_PARSE_FILE_H

#include <hdf5.h>

namespace lime { namespace hdf5 {
herr_t parse_file(hid_t loc_id, const char *name, const H5O_info_t *info,
		  void *fileh5);
}}

#endif

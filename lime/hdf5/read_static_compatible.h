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

#ifndef LIME_HDF5_READ_STATIC_COMPATIBLE_H
#define LIME_HDF5_READ_STATIC_COMPATIBLE_H

#include <complex>
#include <hdf5.h>
#include <string>

#include <lila/all.h>
#include <lime/hdf5/types.h>

namespace lime {
namespace hdf5 {

// Functions to check field with a scalar entry
bool read_static_compatible(hid_t file_id, std::string field, lime_int data);
bool read_static_compatible(hid_t file_id, std::string field, lime_uint data);
bool read_static_compatible(hid_t file_id, std::string field, lime_long data);
bool read_static_compatible(hid_t file_id, std::string field, lime_ulong data);
bool read_static_compatible(hid_t file_id, std::string field, lime_llong data);
bool read_static_compatible(hid_t file_id, std::string field, lime_ullong data);

bool read_static_compatible(hid_t file_id, std::string field, lime_float data);
bool read_static_compatible(hid_t file_id, std::string field, lime_double data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lime_scomplex data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lime_complex data);

// Functions to check a field with a lila::Vector entry
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Vector<lime_float> data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Vector<lime_double> data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Vector<lime_scomplex> data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Vector<lime_complex> data);

// Functions to check a field with a lila::Matrix entry
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Matrix<lime_float> data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Matrix<lime_double> data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Matrix<lime_scomplex> data);
bool read_static_compatible(hid_t file_id, std::string field,
                            lila::Matrix<lime_complex> data);
} // namespace hdf5
} // namespace lime

#endif

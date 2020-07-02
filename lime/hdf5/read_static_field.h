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

#ifndef LIME_HDF5_READ_STATIC_FIELD_H
#define LIME_HDF5_READ_STATIC_FIELD_H

#include <complex>
#include <hdf5.h>
#include <string>

#include <lila/all.h>
#include <lime/hdf5/types.h>

namespace lime {
namespace hdf5 {

// Functions to read a field with a scalar entry
void read_static_field(hid_t file_id, std::string field, lime_int &data);
void read_static_field(hid_t file_id, std::string field, lime_uint &data);
void read_static_field(hid_t file_id, std::string field, lime_long &data);
void read_static_field(hid_t file_id, std::string field, lime_ulong &data);
void read_static_field(hid_t file_id, std::string field, lime_llong &data);
void read_static_field(hid_t file_id, std::string field, lime_ullong &data);

void read_static_field(hid_t file_id, std::string field, lime_float &data);
void read_static_field(hid_t file_id, std::string field, lime_double &data);
void read_static_field(hid_t file_id, std::string field, lime_scomplex &data);
void read_static_field(hid_t file_id, std::string field, lime_complex &data);

// Functions to read a field with a lila::Vector entry
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_float> &data);
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_double> &data);
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_scomplex> &data);
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_complex> &data);

// Functions to read a field with a lila::Matrix entry
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_float> &data);
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_double> &data);
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_scomplex> &data);
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_complex> &data);

} // namespace hdf5
} // namespace lime

#endif

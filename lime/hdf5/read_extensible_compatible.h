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

#ifndef LIME_HDF5_READ_EXTENSIBLE_COMPATIBLE_H
#define LIME_HDF5_READ_EXTENSIBLE_COMPATIBLE_H

#include <complex>
#include <hdf5.h>
#include <string>

#include <lila/all.h>
#include <lime/hdf5/types.h>

namespace lime {
namespace hdf5 {

// Functions to check field with a scalar entry
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_int> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_uint> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_long> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_ulong> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_llong> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_ullong> const &data);

bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_float> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_double> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_scomplex> const &data);
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_complex> const &data);

// Functions to check a field with a lila::Vector entry
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_float>> const &data);
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_double>> const &data);
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_scomplex>> const &data);
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_complex>> const &data);

// Functions to check a field with a lila::Matrix entry
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_float>> const &data);
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_double>> const &data);
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_scomplex>> const &data);
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_complex>> const &data);
  
} // namespace hdf5
} // namespace lime

#endif

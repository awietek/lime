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

#include <string>
#include <complex>
#include <hdf5.h>

#include <lila/all.h>

namespace lime { namespace hdf5 {

using complex = std::complex<double>;
using scomplex = std::complex<float>;

// Functions to check field with a scalar entry
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<int> const& data);
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<unsigned> const&  data);
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<float> const& data);
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<double> const& data);
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<scomplex> const& data);
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<complex> const& data);

// Functions to check a field with a lila::Vector entry
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<float>> const& data);
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<double>> const& data);
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<scomplex>> const& data);
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<complex>> const& data);

// Functions to check a field with a lila::Matrix entry
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<float>> const& data);
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<double>> const& data);
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<scomplex>> const& data);
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<complex>> const& data);
}}

#endif

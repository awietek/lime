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

#ifndef LIME_HDF5_READ_EXTENSIBLE_FIELD_H
#define LIME_HDF5_READ_EXTENSIBLE_FIELD_H

#include <string>
#include <vector>
#include <complex>
#include <hdf5.h>

#include <lila/all.h>

namespace lime { namespace hdf5 {

using complex = std::complex<double>;
using scomplex = std::complex<float>;

// Functions to read a field with a scalar entry
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<int>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<unsigned>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<float>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<double>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<scomplex>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<complex>& data);

// Functions to read a field with a lila::Vector entry
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<float>>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<double>>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<scomplex>>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<complex>>& data);

// Functions to read a field with a lila::Matrix entry
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<float>>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<double>>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<scomplex>>& data);
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<complex>>& data);

}}

#endif

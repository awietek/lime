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

#ifndef LIME_HDF5_APPEND_EXTENSIBLE_FIELD_H
#define LIME_HDF5_APPEND_EXTENSIBLE_FIELD_H

#include <string>
#include <complex>
#include <hdf5.h>

#include <lila/all.h>

namespace lime { namespace hdf5 {

using complex = std::complex<double>;
using scomplex = std::complex<float>;

    // Functions to write a field with a scalar entry
void append_extensible_field(hid_t file_id, std::string field, int data);
void append_extensible_field(hid_t file_id, std::string field, unsigned data);
void append_extensible_field(hid_t file_id, std::string field, float data);
void append_extensible_field(hid_t file_id, std::string field, double data);
void append_extensible_field(hid_t file_id, std::string field, scomplex data);
void append_extensible_field(hid_t file_id, std::string field, complex data);

// Functions to write a field with a lila::Vector entry
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<float> const& data);
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<double> const& data);
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<scomplex> const& data);
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<complex> const& data);

// Functions to write a field with a lila::Matrix entry
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<float> const& data);
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<double> const& data);
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<scomplex> const& data);
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<complex> const& data);

  }}

#endif

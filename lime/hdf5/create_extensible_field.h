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

#ifndef LIME_HDF5_CREATE_EXTENSIBLE_FIELD_H
#define LIME_HDF5_CREATE_EXTENSIBLE_FIELD_H

#include <string>
#include <complex>
#include <hdf5.h>

#include <lila/all.h>

#ifndef LIME_STRING_CHUNK_SIZE
#define LIME_STRING_CHUNK_SIZE 10
#endif
#ifndef LIME_SCALAR_CHUNK_SIZE
#define LIME_SCALAR_CHUNK_SIZE 100
#endif
#ifndef LIME_VECTOR_CHUNK_SIZE
#define LIME_VECTOR_CHUNK_SIZE 10
#endif
#ifndef LIME_MATRIX_CHUNK_SIZE
#define LIME_MATRIX_CHUNK_SIZE 1
#endif

namespace lime { namespace hdf5 {

using complex = std::complex<double>;
using scomplex = std::complex<float>;
    
// Functions to create a field with a scalar entry
void create_extensible_field(hid_t file_id, std::string field, int data,
			     hsize_t chunk_size=LIME_SCALAR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field, unsigned data,
			     hsize_t chunk_size=LIME_SCALAR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field, float data,
			     hsize_t chunk_size=LIME_SCALAR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field, double data,
			     hsize_t chunk_size=LIME_SCALAR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field, scomplex data,
			     hsize_t chunk_size=LIME_SCALAR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field, complex data,
			     hsize_t chunk_size=LIME_SCALAR_CHUNK_SIZE);

// Functions to create a field with a lila::Vector entry
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<float> const& data,
			     hsize_t chunk_size=LIME_VECTOR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<double> const& data,
			     hsize_t chunk_size=LIME_VECTOR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<scomplex> const& data,
			     hsize_t chunk_size=LIME_VECTOR_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Vector<complex> const& data,
			     hsize_t chunk_size=LIME_VECTOR_CHUNK_SIZE);

// Functions to create a field with a lila::Matrix entry
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<float> const& data,
			     hsize_t chunk_size=LIME_MATRIX_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<double> const& data,
			     hsize_t chunk_size=LIME_MATRIX_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<scomplex> const& data,
			     hsize_t chunk_size=LIME_MATRIX_CHUNK_SIZE);
void create_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<complex> const& data,
			     hsize_t chunk_size=LIME_MATRIX_CHUNK_SIZE);

}}

#endif

#include "read_static_field.h"

#include <lime/hdf5/utils.h>

namespace lime {
namespace hdf5 {

// Functions to write a field with a scalar entry
template <class data_t>
void read_static_field_scalar(hid_t file_id, std::string field, data_t &data) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data);
  H5Dclose(dataset_id);
}

void read_static_field(hid_t file_id, std::string field, lime_int &data) {
  read_static_field_scalar<lime_int>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_uint &data) {
  read_static_field_scalar<lime_uint>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_long &data) {
  read_static_field_scalar<lime_long>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_ulong &data) {
  read_static_field_scalar<lime_ulong>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_llong &data) {
  read_static_field_scalar<lime_llong>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_ullong &data) {
  read_static_field_scalar<lime_ullong>(file_id, field, data);
}

void read_static_field(hid_t file_id, std::string field, lime_float &data) {
  read_static_field_scalar<lime_float>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_double &data) {
  read_static_field_scalar<lime_double>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_scomplex &data) {
  read_static_field_scalar<lime_scomplex>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field, lime_complex &data) {
  read_static_field_scalar<lime_complex>(file_id, field, data);
}

// Functions to write a field with a vector entry
template <class data_t>
void read_static_field_vector(hid_t file_id, std::string field,
                              lila::Vector<data_t> &vector) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  vector.clear();
  vector.resize(dims[0]);
  H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT,
          vector.data());
  H5Dclose(dataset_id);
}

void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_float> &data) {
  read_static_field_vector<float>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_double> &data) {
  read_static_field_vector<lime_double>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_scomplex> &data) {
  read_static_field_vector<lime_scomplex>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field,
                       lila::Vector<lime_complex> &data) {
  read_static_field_vector<lime_complex>(file_id, field, data);
}

// Functions to write a field with a matrix entry
template <class data_t>
void read_static_field_matrix(hid_t file_id, std::string field,
                              lila::Matrix<data_t> &matrix) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  auto matrix_T = lila::Zeros<data_t>(dims[1], dims[0]);
  H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT,
          matrix_T.data());
  matrix = lila::Transpose(matrix_T);
  H5Dclose(dataset_id);
}

void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_float> &data) {
  read_static_field_matrix<lime_float>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_double> &data) {
  read_static_field_matrix<lime_double>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_scomplex> &data) {
  read_static_field_matrix<lime_scomplex>(file_id, field, data);
}
void read_static_field(hid_t file_id, std::string field,
                       lila::Matrix<lime_complex> &data) {
  read_static_field_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

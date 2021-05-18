#include "write_static_field.h"

namespace lime {
namespace hdf5 {

// Functions to write a field with a scalar entry
template <class data_t>
void write_static_field_scalar(hid_t file_id, std::string field, data_t data) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, &data);
  H5Dclose(dataset_id);
}

void write_static_field(hid_t file_id, std::string field, lime_int data) {
  write_static_field_scalar<lime_int>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_uint data) {
  write_static_field_scalar<lime_uint>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_long data) {
  write_static_field_scalar<lime_long>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_ulong data) {
  write_static_field_scalar<lime_ulong>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_llong data) {
  write_static_field_scalar<lime_llong>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_ullong data) {
  write_static_field_scalar<lime_ullong>(file_id, field, data);
}

void write_static_field(hid_t file_id, std::string field, lime_float data) {
  write_static_field_scalar<lime_float>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_double data) {
  write_static_field_scalar<lime_double>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_scomplex data) {
  write_static_field_scalar<lime_scomplex>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field, lime_complex data) {
  write_static_field_scalar<lime_complex>(file_id, field, data);
}

// Functions to write a field with a vector entry
template <class data_t>
void write_static_field_vector(hid_t file_id, std::string field,
                               lila::Vector<data_t> const &vector) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT,
           vector.data());
  H5Dclose(dataset_id);
}

void write_static_field(hid_t file_id, std::string field,
                        lila::Vector<lime_float> const &data) {
  write_static_field_vector<lime_float>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field,
                        lila::Vector<lime_double> const &data) {
  write_static_field_vector<lime_double>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field,
                        lila::Vector<lime_scomplex> const &data) {
  write_static_field_vector<lime_scomplex>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field,
                        lila::Vector<lime_complex> const &data) {
  write_static_field_vector<lime_complex>(file_id, field, data);
}

// Functions to write a field with a matrix entry
template <class data_t>
void write_static_field_matrix(hid_t file_id, std::string field,
                               lila::Matrix<data_t> const &matrix) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  auto matrix_T = lila::Transpose(matrix);
  H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT,
           matrix_T.data());
  H5Dclose(dataset_id);
}

void write_static_field(hid_t file_id, std::string field,
                        lila::Matrix<lime_float> const &data) {
  write_static_field_matrix<lime_float>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field,
                        lila::Matrix<lime_double> const &data) {
  write_static_field_matrix<lime_double>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field,
                        lila::Matrix<lime_scomplex> const &data) {
  write_static_field_matrix<lime_scomplex>(file_id, field, data);
}
void write_static_field(hid_t file_id, std::string field,
                        lila::Matrix<lime_complex> const &data) {
  write_static_field_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

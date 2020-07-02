#include "create_static_field.h"

#include <lime/hdf5/types.h>

namespace lime {
namespace hdf5 {

// Functions to create a field with a scalar entry
template <class data_t>
void create_static_field_scalar(hid_t file_id, std::string field, data_t data) {
  hsize_t dims[1];
  dims[0] = 1;
  hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id =
      H5Dcreate2(file_id, field.c_str(), datatype_id, dataspace_id, H5P_DEFAULT,
                 H5P_DEFAULT, H5P_DEFAULT);
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
}

void create_static_field(hid_t file_id, std::string field, lime_int data) {
  create_static_field_scalar<lime_int>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_uint data) {
  create_static_field_scalar<lime_uint>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_long data) {
  create_static_field_scalar<lime_long>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_ulong data) {
  create_static_field_scalar<lime_ulong>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_llong data) {
  create_static_field_scalar<lime_llong>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_ullong data) {
  create_static_field_scalar<lime_ullong>(file_id, field, data);
}

void create_static_field(hid_t file_id, std::string field, lime_float data) {
  create_static_field_scalar<lime_float>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_double data) {
  create_static_field_scalar<lime_double>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_scomplex data) {
  create_static_field_scalar<lime_scomplex>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field, lime_complex data) {
  create_static_field_scalar<lime_complex>(file_id, field, data);
}

// Functions to create a field with a vector entry
template <class data_t>
void create_static_field_vector(hid_t file_id, std::string field,
                                lila::Vector<data_t> vector) {
  hsize_t dims[1];
  dims[0] = (hsize_t)vector.size();
  hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id =
      H5Dcreate2(file_id, field.c_str(), datatype_id, dataspace_id, H5P_DEFAULT,
                 H5P_DEFAULT, H5P_DEFAULT);
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
}

void create_static_field(hid_t file_id, std::string field,
                         lila::Vector<lime_float> data) {
  create_static_field_vector<lime_float>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field,
                         lila::Vector<lime_double> data) {
  create_static_field_vector<lime_double>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field,
                         lila::Vector<lime_scomplex> data) {
  create_static_field_vector<lime_scomplex>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field,
                         lila::Vector<lime_complex> data) {
  create_static_field_vector<lime_complex>(file_id, field, data);
}

// Functions to create a field with a matrix entry
template <class data_t>
void create_static_field_matrix(hid_t file_id, std::string field,
                                lila::Matrix<data_t> matrix) {
  hsize_t dims[2];
  dims[0] = matrix.nrows();
  dims[1] = matrix.ncols();
  hid_t dataspace_id = H5Screate_simple(2, dims, NULL);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id =
      H5Dcreate2(file_id, field.c_str(), datatype_id, dataspace_id, H5P_DEFAULT,
                 H5P_DEFAULT, H5P_DEFAULT);
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
}

void create_static_field(hid_t file_id, std::string field,
                         lila::Matrix<lime_float> data) {
  create_static_field_matrix<lime_float>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field,
                         lila::Matrix<lime_double> data) {
  create_static_field_matrix<lime_double>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field,
                         lila::Matrix<lime_scomplex> data) {
  create_static_field_matrix<lime_scomplex>(file_id, field, data);
}
void create_static_field(hid_t file_id, std::string field,
                         lila::Matrix<lime_complex> data) {
  create_static_field_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

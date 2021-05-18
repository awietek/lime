#include "read_extensible_field.h"

#include <lime/hdf5/utils.h>

namespace lime {
namespace hdf5 {

// Functions to read an extensible field with a scalar entry
template <class data_t>
void read_extensible_field_scalar(hid_t file_id, std::string field,
                                  std::vector<data_t> &data) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  data.clear();
  data.resize(dims[0]);
  H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, data.data());
  H5Dclose(dataset_id);
}

void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_int> &data) {
  read_extensible_field_scalar<lime_int>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_uint> &data) {
  read_extensible_field_scalar<lime_uint>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_long> &data) {
  read_extensible_field_scalar<lime_long>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_ulong> &data) {
  read_extensible_field_scalar<lime_ulong>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_llong> &data) {
  read_extensible_field_scalar<lime_llong>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_ullong> &data) {
  read_extensible_field_scalar<lime_ullong>(file_id, field, data);
}

void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_float> &data) {
  read_extensible_field_scalar<lime_float>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_double> &data) {
  read_extensible_field_scalar<lime_double>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_scomplex> &data) {
  read_extensible_field_scalar<lime_scomplex>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lime_complex> &data) {
  read_extensible_field_scalar<lime_complex>(file_id, field, data);
}

// Functions to read an extensible field with a vector entry
template <class data_t>
void read_extensible_field_vector(hid_t file_id, std::string field,
                                  std::vector<lila::Vector<data_t>> &vectors) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  vectors.clear();
  vectors.resize(dims[0]);
  for (hsize_t idx = 0; idx < dims[0]; ++idx) {
    vectors[idx].clear();
    vectors[idx].resize(dims[1]);

    hid_t filespace_id = H5Dget_space(dataset_id);
    std::vector<hsize_t> offset = {idx, 0};
    std::vector<hsize_t> ext_dims = {1, dims[1]};
    H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
                        ext_dims.data(), NULL);
    hid_t memspace_id = H5Screate_simple(2, ext_dims.data(), NULL);

    H5Dread(dataset_id, datatype_id, memspace_id, filespace_id, H5P_DEFAULT,
            vectors[idx].data());
    H5Sclose(filespace_id);
    H5Sclose(memspace_id);
  }
  H5Dclose(dataset_id);
}

void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Vector<lime_float>> &data) {
  read_extensible_field_vector<lime_float>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Vector<lime_double>> &data) {
  read_extensible_field_vector<lime_double>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Vector<lime_scomplex>> &data) {
  read_extensible_field_vector<lime_scomplex>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Vector<lime_complex>> &data) {
  read_extensible_field_vector<lime_complex>(file_id, field, data);
}

// Functions to read an extensible field with a matrix entry
template <class data_t>
void read_extensible_field_matrix(hid_t file_id, std::string field,
                                  std::vector<lila::Matrix<data_t>> &matrices) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  matrices.clear();
  matrices.resize(dims[0]);
  for (hsize_t idx = 0; idx < dims[0]; ++idx) {
    // matrices[idx].clear();
    // matrices[idx].resize(dims[1], dims[2]);

    hid_t filespace_id = H5Dget_space(dataset_id);
    std::vector<hsize_t> offset = {idx, 0, 0};
    std::vector<hsize_t> ext_dims = {1, dims[1], dims[2]};
    H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
                        ext_dims.data(), NULL);
    hid_t memspace_id = H5Screate_simple(3, ext_dims.data(), NULL);

    auto matrix_T = lila::Zeros<data_t>(dims[2], dims[1]);
    H5Dread(dataset_id, datatype_id, memspace_id, filespace_id, H5P_DEFAULT,
            matrix_T.data());
    matrices[idx] = lila::Transpose(matrix_T);
    H5Sclose(filespace_id);
    H5Sclose(memspace_id);
  }
  H5Dclose(dataset_id);
}

void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Matrix<lime_float>> &data) {
  read_extensible_field_matrix<lime_float>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Matrix<lime_double>> &data) {
  read_extensible_field_matrix<lime_double>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Matrix<lime_scomplex>> &data) {
  read_extensible_field_matrix<lime_scomplex>(file_id, field, data);
}
void read_extensible_field(hid_t file_id, std::string field,
                           std::vector<lila::Matrix<lime_complex>> &data) {
  read_extensible_field_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

#include "append_extensible_field.h"

#include <lime/hdf5/types.h>
#include <lime/hdf5/utils.h>


extern "C" {
void h5dwrite_f_c(hid_t *dset_id, hid_t mem_type_id, const void *buf,
		  hsize_t[], int hdferr, hid_t *mem_space_id,
		  hid_t *file_space_id, hid_t *xfer_prp);
}

namespace lime {
namespace hdf5 {

// Functions to write a field with a scalar entry
template <class data_t>
void append_extensible_field_scalar(hid_t file_id, std::string field,
                                    data_t data) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();

  // Make dataspace larger by one
  auto dims = get_dataspace_dims(dataset_id);
  assert(dims.size() == 2);
  auto new_dims = dims;
  ++new_dims[0];
  H5Dset_extent(dataset_id, new_dims.data());

  // Write to a subselection
  hid_t filespace_id = H5Dget_space(dataset_id);
  std::vector<hsize_t> offset = {dims[0], 0};
  std::vector<hsize_t> ext_dims = {1, dims[1]};
  H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
                      ext_dims.data(), NULL);
  hid_t memspace_id = H5Screate_simple(2, ext_dims.data(), NULL);
  H5Dwrite(dataset_id, datatype_id, memspace_id, filespace_id, H5P_DEFAULT,
           &data);

  H5Sclose(memspace_id);
  H5Sclose(filespace_id);
  H5Dclose(dataset_id);
}

void append_extensible_field(hid_t file_id, std::string field, lime_int data) {
  append_extensible_field_scalar<lime_int>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field, lime_uint data) {
  append_extensible_field_scalar<lime_uint>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field, lime_long data) {
  append_extensible_field_scalar<lime_long>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lime_ulong data) {
  append_extensible_field_scalar<lime_ulong>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lime_llong data) {
  append_extensible_field_scalar<lime_llong>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lime_ullong data) {
  append_extensible_field_scalar<lime_ullong>(file_id, field, data);
}

void append_extensible_field(hid_t file_id, std::string field,
                             lime_float data) {
  append_extensible_field_scalar<lime_float>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lime_double data) {
  append_extensible_field_scalar<lime_double>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lime_scomplex data) {
  append_extensible_field_scalar<lime_scomplex>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lime_complex data) {
  append_extensible_field_scalar<lime_complex>(file_id, field, data);
}

// Functions to write a field with a vector entry
template <class data_t>
void append_extensible_field_vector(hid_t file_id, std::string field,
                                    lila::Vector<data_t> const &vector) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();

  // Make dataspace larger by one
  auto dims = get_dataspace_dims(dataset_id);
  assert(dims.size() == 2);
  auto new_dims = dims;
  ++new_dims[0];
  H5Dset_extent(dataset_id, new_dims.data());

  // Write to a subselection
  hid_t filespace_id = H5Dget_space(dataset_id);
  std::vector<hsize_t> offset = {dims[0], 0};
  std::vector<hsize_t> ext_dims = {1, dims[1]};
  H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
                      ext_dims.data(), NULL);
  hid_t memspace_id = H5Screate_simple(2, ext_dims.data(), NULL);
  H5Dwrite(dataset_id, datatype_id, memspace_id, filespace_id, H5P_DEFAULT,
           vector.data());

  H5Sclose(memspace_id);
  H5Sclose(filespace_id);
  H5Dclose(dataset_id);
}

void append_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_float> const &data) {
  append_extensible_field_vector<lime_float>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_double> const &data) {
  append_extensible_field_vector<lime_double>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_scomplex> const &data) {
  append_extensible_field_vector<lime_scomplex>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_complex> const &data) {
  append_extensible_field_vector<lime_complex>(file_id, field, data);
}

// Functions to write a field with a matrix entry
template <class data_t>
void append_extensible_field_matrix(hid_t file_id, std::string field,
                                    lila::Matrix<data_t> const &matrix) {
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();

  // Make dataspace larger by one
  auto dims = get_dataspace_dims(dataset_id);
  assert(dims.size() == 3);
  auto new_dims = dims;
  ++new_dims[0];
  H5Dset_extent(dataset_id, new_dims.data());

  // Write to a subselection
  hid_t filespace_id = H5Dget_space(dataset_id);
  std::vector<hsize_t> offset = {dims[0], 0, 0};
  std::vector<hsize_t> ext_dims = {1, dims[1], dims[2]};
  H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
                      ext_dims.data(), NULL);
  hid_t memspace_id = H5Screate_simple(3, ext_dims.data(), NULL);

  auto matrix_T = lila::Transpose(matrix);
  H5Dwrite(dataset_id, datatype_id, memspace_id, filespace_id, H5P_DEFAULT,
           matrix_T.data());
  
  H5Sclose(memspace_id);
  H5Sclose(filespace_id);
  H5Dclose(dataset_id);
}

void append_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_float> const &data) {
  append_extensible_field_matrix<lime_float>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_double> const &data) {
  append_extensible_field_matrix<lime_double>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_scomplex> const &data) {
  append_extensible_field_matrix<lime_scomplex>(file_id, field, data);
}
void append_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_complex> const &data) {
  append_extensible_field_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

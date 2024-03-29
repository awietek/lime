#include "create_extensible_field.h"

namespace lime {
namespace hdf5 {

// Functions to create a field with a scalar entry
template <class data_t>
void create_extensible_field_scalar(hid_t file_id, std::string field,
                                    data_t data, hsize_t chunk_size) {
  // Set initial dimension and unlimited max dimension
  hsize_t dims[2];
  dims[0] = 0;
  dims[1] = 1;
  hsize_t max_dims[2];
  max_dims[0] = H5S_UNLIMITED;
  max_dims[1] = 1;

  // Create chunking property
  hsize_t chunk_dims[2];
  chunk_dims[0] = chunk_size;
  chunk_dims[1] = 1;
  hid_t chunk_prop_id = H5Pcreate(H5P_DATASET_CREATE);
  H5Pset_chunk(chunk_prop_id, 2, chunk_dims);

  hid_t dataspace_id = H5Screate_simple(2, dims, max_dims);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id =
      H5Dcreate2(file_id, field.c_str(), datatype_id, dataspace_id, H5P_DEFAULT,
                 chunk_prop_id, H5P_DEFAULT);

  H5Dclose(dataset_id);
  H5Pclose(chunk_prop_id);
  H5Sclose(dataspace_id);
}

void create_extensible_field(hid_t file_id, std::string field, lime_int data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_int>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field, lime_uint data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_uint>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field, lime_long data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_long>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field, lime_ulong data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_ulong>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field, lime_llong data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_llong>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field, lime_ullong data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_ullong>(file_id, field, data, chunk_size);
}

void create_extensible_field(hid_t file_id, std::string field, lime_float data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_float>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field, lime_double data,
                             hsize_t chunk_size) {
  create_extensible_field_scalar<lime_double>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lime_scomplex data, hsize_t chunk_size) {
  create_extensible_field_scalar<lime_scomplex>(file_id, field, data,
                                                chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lime_complex data, hsize_t chunk_size) {
  create_extensible_field_scalar<lime_complex>(file_id, field, data,
                                               chunk_size);
}

// Functions to create a field with a vector entry
template <class data_t>
void create_extensible_field_vector(hid_t file_id, std::string field,
                                    lila::Vector<data_t> const &vector,
                                    hsize_t chunk_size) {
  // Set initial dimension and unlimited max dimension
  hsize_t dims[2];
  dims[0] = 0;
  dims[1] = (hsize_t)vector.size();
  hsize_t max_dims[2];
  max_dims[0] = H5S_UNLIMITED;
  max_dims[1] = (hsize_t)vector.size();

  // Create chunking property
  hsize_t chunk_dims[2];
  chunk_dims[0] = chunk_size;
  chunk_dims[1] = (hsize_t)vector.size();
  hid_t chunk_prop_id = H5Pcreate(H5P_DATASET_CREATE);
  H5Pset_chunk(chunk_prop_id, 2, chunk_dims);

  hid_t dataspace_id = H5Screate_simple(2, dims, max_dims);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id =
      H5Dcreate2(file_id, field.c_str(), datatype_id, dataspace_id, H5P_DEFAULT,
                 chunk_prop_id, H5P_DEFAULT);

  H5Dclose(dataset_id);
  H5Pclose(chunk_prop_id);
  H5Sclose(dataspace_id);
}

void create_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_float> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_vector<lime_float>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_double> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_vector<lime_double>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_scomplex> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_vector<lime_scomplex>(file_id, field, data,
                                                chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lila::Vector<lime_complex> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_vector<lime_complex>(file_id, field, data,
                                               chunk_size);
}

// Functions to create a field with a matrix entry
template <class data_t>
void create_extensible_field_matrix(hid_t file_id, std::string field,
                                    lila::Matrix<data_t> const &matrix,
                                    hsize_t chunk_size) {
  // Set initial dimension and unlimited max dimension
  hsize_t dims[3];
  dims[0] = 0;
  dims[1] = (hsize_t)matrix.nrows();
  dims[2] = (hsize_t)matrix.ncols();

  hsize_t max_dims[3];
  max_dims[0] = H5S_UNLIMITED;
  max_dims[1] = (hsize_t)matrix.nrows();
  max_dims[2] = (hsize_t)matrix.ncols();

  // Create chunking property
  hsize_t chunk_dims[3];
  chunk_dims[0] = chunk_size;
  chunk_dims[1] = (hsize_t)matrix.nrows();
  chunk_dims[2] = (hsize_t)matrix.ncols();
  hid_t chunk_prop_id = H5Pcreate(H5P_DATASET_CREATE);
  H5Pset_chunk(chunk_prop_id, 3, chunk_dims);

  hid_t dataspace_id = H5Screate_simple(3, dims, max_dims);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id =
      H5Dcreate2(file_id, field.c_str(), datatype_id, dataspace_id, H5P_DEFAULT,
                 chunk_prop_id, H5P_DEFAULT);

  H5Dclose(dataset_id);
  H5Pclose(chunk_prop_id);
  H5Sclose(dataspace_id);
}

void create_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_float> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_matrix<lime_float>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_double> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_matrix<lime_double>(file_id, field, data, chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_scomplex> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_matrix<lime_scomplex>(file_id, field, data,
                                                chunk_size);
}
void create_extensible_field(hid_t file_id, std::string field,
                             lila::Matrix<lime_complex> const &data,
                             hsize_t chunk_size) {
  create_extensible_field_matrix<lime_complex>(file_id, field, data,
                                               chunk_size);
}

} // namespace hdf5
} // namespace lime

#include "write_compatible.h"

#include <lime/hdf5/utils.h>

namespace lime {
namespace hdf5 {

// Functions to create a field with a scalar entry
template <class data_t>
bool write_compatible_scalar(hid_t file_id, std::string field, data_t data) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 1) || (dims[0] != 1))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool write_compatible(hid_t file_id, std::string field, lime_int data) {
  return write_compatible_scalar<lime_int>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_uint data) {
  return write_compatible_scalar<lime_uint>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_long data) {
  return write_compatible_scalar<lime_long>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_ulong data) {
  return write_compatible_scalar<lime_ulong>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_llong data) {
  return write_compatible_scalar<lime_llong>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_ullong data) {
  return write_compatible_scalar<lime_ullong>(file_id, field, data);
}

bool write_compatible(hid_t file_id, std::string field, lime_float data) {
  return write_compatible_scalar<lime_float>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_double data) {
  return write_compatible_scalar<lime_double>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_scomplex data) {
  return write_compatible_scalar<lime_scomplex>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field, lime_complex data) {
  return write_compatible_scalar<lime_complex>(file_id, field, data);
}

// Functions to create a field with a vector entry
template <class data_t>
bool write_compatible_vector(hid_t file_id, std::string field,
                             lila::Vector<data_t> vector) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 1) || (dims[0] != (hsize_t)vector.size()))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool write_compatible(hid_t file_id, std::string field,
                      lila::Vector<lime_float> data) {
  return write_compatible_vector<lime_float>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field,
                      lila::Vector<lime_double> data) {
  return write_compatible_vector<lime_double>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field,
                      lila::Vector<lime_scomplex> data) {
  return write_compatible_vector<lime_scomplex>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field,
                      lila::Vector<lime_complex> data) {
  return write_compatible_vector<lime_complex>(file_id, field, data);
}

// Functions to create a field with a matrix entry
template <class data_t>
bool write_compatible_matrix(hid_t file_id, std::string field,
                             lila::Matrix<data_t> matrix) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 2) || (dims[0] != (hsize_t)matrix.nrows()) ||
      (dims[1] != (hsize_t)matrix.ncols()))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool write_compatible(hid_t file_id, std::string field,
                      lila::Matrix<lime_float> data) {
  return write_compatible_matrix<lime_float>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field,
                      lila::Matrix<lime_double> data) {
  return write_compatible_matrix<lime_double>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field,
                      lila::Matrix<lime_scomplex> data) {
  return write_compatible_matrix<lime_scomplex>(file_id, field, data);
}
bool write_compatible(hid_t file_id, std::string field,
                      lila::Matrix<lime_complex> data) {
  return write_compatible_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

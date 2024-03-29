#include "append_compatible.h"

#include <lime/hdf5/utils.h>

namespace lime {
namespace hdf5 {

// Functions to check compatibilty of scalar extensible field
template <class data_t>
bool append_compatible_scalar(hid_t file_id, std::string field, data_t data) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 2) || (dims[1] != 1))
    compatible = false;

  // Check if max. dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 2) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != 1))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool append_compatible(hid_t file_id, std::string field, lime_int data) {
  return append_compatible_scalar<lime_int>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_uint data) {
  return append_compatible_scalar<lime_uint>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_long data) {
  return append_compatible_scalar<lime_long>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_ulong data) {
  return append_compatible_scalar<lime_ulong>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_llong data) {
  return append_compatible_scalar<lime_llong>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_ullong data) {
  return append_compatible_scalar<lime_ullong>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_float data) {
  return append_compatible_scalar<lime_float>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_double data) {
  return append_compatible_scalar<lime_double>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_scomplex data) {
  return append_compatible_scalar<lime_scomplex>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field, lime_complex data) {
  return append_compatible_scalar<lime_complex>(file_id, field, data);
}

// Functions to check compatibilty of vector extensible field
template <class data_t>
bool append_compatible_vector(hid_t file_id, std::string field,
                              lila::Vector<data_t> const &vector) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 2) || (dims[1] != (hsize_t)vector.size()))
    compatible = false;

  // Check if max. dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 2) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != (hsize_t)vector.size()))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool append_compatible(hid_t file_id, std::string field,
                       lila::Vector<lime_float> const &data) {
  return append_compatible_vector<lime_float>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field,
                       lila::Vector<lime_double> const &data) {
  return append_compatible_vector<lime_double>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field,
                       lila::Vector<lime_scomplex> const &data) {
  return append_compatible_vector<lime_scomplex>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field,
                       lila::Vector<lime_complex> const &data) {
  return append_compatible_vector<lime_complex>(file_id, field, data);
}

// Functions to check compatibilty of matrix extensible field
template <class data_t>
bool append_compatible_matrix(hid_t file_id, std::string field,
                              lila::Matrix<data_t> const &matrix) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 3) || (dims[1] != (hsize_t)matrix.nrows()) ||
      (dims[2] != (hsize_t)matrix.ncols()))
    compatible = false;

  // Check if max. dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 3) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != (hsize_t)matrix.nrows()) ||
      (max_dims[2] != (hsize_t)matrix.ncols()))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool append_compatible(hid_t file_id, std::string field,
                       lila::Matrix<lime_float> const &data) {
  return append_compatible_matrix<lime_float>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field,
                       lila::Matrix<lime_double> const &data) {
  return append_compatible_matrix<lime_double>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field,
                       lila::Matrix<lime_scomplex> const &data) {
  return append_compatible_matrix<lime_scomplex>(file_id, field, data);
}
bool append_compatible(hid_t file_id, std::string field,
                       lila::Matrix<lime_complex> const &data) {
  return append_compatible_matrix<lime_complex>(file_id, field, data);
}

} // namespace hdf5
} // namespace lime

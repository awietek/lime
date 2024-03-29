#include "read_extensible_compatible.h"

#include <lime/hdf5/types.h>
#include <lime/hdf5/utils.h>

namespace lime {
namespace hdf5 {

// Functions for a scalar entry
template <class data_t>
bool read_extensible_compatible_scalar(hid_t file_id, std::string field) {
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

  // Check if max dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 2) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != 1))
    compatible = false;
  H5Dclose(dataset_id);
  return compatible;
}

bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_int> const &data) {
  return read_extensible_compatible_scalar<lime_int>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_uint> const &data) {
  return read_extensible_compatible_scalar<lime_uint>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_long> const &data) {
  return read_extensible_compatible_scalar<lime_long>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_ulong> const &data) {
  return read_extensible_compatible_scalar<lime_ulong>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_llong> const &data) {
  return read_extensible_compatible_scalar<lime_llong>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_ullong> const &data) {
  return read_extensible_compatible_scalar<lime_ullong>(file_id, field);
}

bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_float> const &data) {
  return read_extensible_compatible_scalar<lime_float>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_double> const &data) {
  return read_extensible_compatible_scalar<lime_double>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_scomplex> const &data) {
  return read_extensible_compatible_scalar<lime_scomplex>(file_id, field);
}
bool read_extensible_compatible(hid_t file_id, std::string field,
                                std::vector<lime_complex> const &data) {
  return read_extensible_compatible_scalar<lime_complex>(file_id, field);
}

// Functions to create a field with a vector entry
template <class data_t>
bool read_extensible_compatible_vector(hid_t file_id, std::string field) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if (dims.size() != 2)
    compatible = false;

  // Check if max dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 2) || (max_dims[0] != H5S_UNLIMITED))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_float>> const &data) {
  return read_extensible_compatible_vector<lime_float>(file_id, field);
}
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_double>> const &data) {
  return read_extensible_compatible_vector<lime_double>(file_id, field);
}
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_scomplex>> const &data) {
  return read_extensible_compatible_vector<lime_scomplex>(file_id, field);
}
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Vector<lime_complex>> const &data) {
  return read_extensible_compatible_vector<lime_complex>(file_id, field);
}

// Functions to create a field with a matrix entry
template <class data_t>
bool read_extensible_compatible_matrix(hid_t file_id, std::string field) {
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if (dims.size() != 3)
    compatible = false;

  // Check if max dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 3) || (max_dims[0] != H5S_UNLIMITED))
    compatible = false;

  H5Dclose(dataset_id);
  return compatible;
}

bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_float>> const &data) {
  return read_extensible_compatible_matrix<lime_float>(file_id, field);
}
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_double>> const &data) {
  return read_extensible_compatible_matrix<lime_double>(file_id, field);
}
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_scomplex>> const &data) {
  return read_extensible_compatible_matrix<lime_scomplex>(file_id, field);
}
bool read_extensible_compatible(
    hid_t file_id, std::string field,
    std::vector<lila::Matrix<lime_complex>> const &data) {
  return read_extensible_compatible_matrix<lime_complex>(file_id, field);
}

} // namespace hdf5
} // namespace lime

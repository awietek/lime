#include "read_extensible_compatible.h"

#include <lime/hdf5/utils.h>
#include <lime/hdf5/types.h>
#include <lime/hdf5/field_type_string.h>

namespace lime { namespace hdf5 {
    
// Functions for a scalar entry
template <class data_t>
bool read_extensible_compatible_scalar(hid_t file_id, std::string field)
{
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
				std::vector<int> const& data)
{ return read_extensible_compatible_scalar<int>(file_id, field); }
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<unsigned> const& data)
{ return read_extensible_compatible_scalar<unsigned>(file_id, field); }
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<float> const& data)
{ return read_extensible_compatible_scalar<float>(file_id, field); }
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<double> const& data)
{ return read_extensible_compatible_scalar<double>(file_id, field); }
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<scomplex> const& data)
{ return read_extensible_compatible_scalar<scomplex>(file_id, field); }
bool read_extensible_compatible(hid_t file_id, std::string field,
				std::vector<complex> const& data)
{ return read_extensible_compatible_scalar<complex>(file_id, field); }


// Functions to create a field with a vector entry
template <class data_t>
bool read_extensible_compatible_vector(hid_t file_id, std::string field)
{
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

bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<float>> const& data)
{ return read_extensible_compatible_vector<float>(file_id, field); }
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<double>> const& data)
{ return read_extensible_compatible_vector<double>(file_id, field); }
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<scomplex>> const& data)
{ return read_extensible_compatible_vector<scomplex>(file_id, field); }
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Vector<complex>> const& data)
{ return read_extensible_compatible_vector<complex>(file_id, field); }


// Functions to create a field with a matrix entry
template <class data_t>
bool read_extensible_compatible_matrix(hid_t file_id, std::string field)
{
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

bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<float>> const& data)
{ return read_extensible_compatible_matrix<float>(file_id, field); }
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<double>> const& data)
{ return read_extensible_compatible_matrix<double>(file_id, field); }
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<scomplex>> const& data)
{ return read_extensible_compatible_matrix<scomplex>(file_id, field); }
bool read_extensible_compatible
(hid_t file_id, std::string field,
 std::vector<lila::Matrix<complex>> const& data)
{ return read_extensible_compatible_matrix<complex>(file_id, field); }

}}

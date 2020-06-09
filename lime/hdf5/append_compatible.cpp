#include "append_compatible.h"

#include <lime/hdf5/utils.h>
#include <lime/hdf5/types.h>

namespace lime { namespace hdf5 {

// Functions to check compatibilty of scalar extensible field
template <class data_t>
bool append_compatible_scalar(hid_t file_id, std::string field, data_t data)
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

  // Check if max. dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 2) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != 1))
    compatible = false;  
  
  H5Dclose(dataset_id);
  return compatible;
}

bool append_compatible(hid_t file_id, std::string field, int data)
{ return append_compatible_scalar<int>(file_id, field, data); }
bool append_compatible(hid_t file_id, std::string field, unsigned int data)
{ return append_compatible_scalar<unsigned int>(file_id, field, data); }
bool append_compatible(hid_t file_id, std::string field, float data)
{ return append_compatible_scalar<float>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field, double data)
{ return append_compatible_scalar<double>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field, scomplex data)
{ return append_compatible_scalar<scomplex>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field, complex data)
{ return append_compatible_scalar<complex>(file_id, field, data); }


// Functions to check compatibilty of vector extensible field
template <class data_t>
bool append_compatible_vector(hid_t file_id, std::string field,
			     lila::Vector<data_t> const& vector)
{
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  
  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 2) || (dims[1] != vector.size()))
    compatible = false;

  // Check if max. dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 2) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != vector.size()))
    compatible = false;  
  
  H5Dclose(dataset_id);
  return compatible;
}

bool append_compatible(hid_t file_id, std::string field,
		       lila::Vector<float> const& data)
{ return append_compatible_vector<float>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field,
		       lila::Vector<double> const& data)
{ return append_compatible_vector<double>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field,
		       lila::Vector<scomplex> const& data)
{ return append_compatible_vector<scomplex>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field,
		       lila::Vector<complex> const& data)
{ return append_compatible_vector<complex>(file_id, field, data); }

    
// Functions to check compatibilty of matrix extensible field
template <class data_t>
bool append_compatible_matrix(hid_t file_id, std::string field,
			      lila::Matrix<data_t> const& matrix)
{
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  
  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 3) || (dims[1] != matrix.nrows()) ||
      (dims[2] != matrix.ncols()))
    compatible = false;

  // Check if max. dimensions are OK
  auto max_dims = get_dataspace_max_dims(dataset_id);
  if ((max_dims.size() != 3) || (max_dims[0] != H5S_UNLIMITED) ||
      (max_dims[1] != matrix.nrows()) || (max_dims[2] != matrix.ncols()))
    compatible = false;  
  
  H5Dclose(dataset_id);
  return compatible;
}

bool append_compatible(hid_t file_id, std::string field,
		       lila::Matrix<float> const& data)
{ return append_compatible_matrix<float>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field,
		       lila::Matrix<double> const& data)
{ return append_compatible_matrix<double>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field,
		       lila::Matrix<scomplex> const& data)
{ return append_compatible_matrix<scomplex>(file_id, field, data); } 
bool append_compatible(hid_t file_id, std::string field,
		       lila::Matrix<complex> const& data)
{ return append_compatible_matrix<complex>(file_id, field, data); }
    
}}

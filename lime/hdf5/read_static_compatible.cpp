#include "read_static_compatible.h"

#include <lime/hdf5/utils.h>
#include <lime/hdf5/types.h>
#include <lime/hdf5/field_type_string.h>

namespace lime { namespace hdf5 {

// Functions to create a field with a scalar entry
template <class data_t>
bool read_static_compatible_scalar(hid_t file_id, std::string field,
				   data_t data)
{
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);

  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if ((dims.size() != 1) || (dims[0] != 1))
    {
      compatible = false;
    }

  H5Dclose(dataset_id);
  return compatible;
}

bool read_static_compatible(hid_t file_id, std::string field, int data)
{ return read_static_compatible_scalar<int>(file_id, field, data); }
bool read_static_compatible(hid_t file_id, std::string field,
			    unsigned int data)
{ return read_static_compatible_scalar<unsigned int>(file_id, field, data); }
bool read_static_compatible(hid_t file_id, std::string field, float data)
{ return read_static_compatible_scalar<float>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field, double data)
{ return read_static_compatible_scalar<double>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field, scomplex data)
{ return read_static_compatible_scalar<scomplex>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field, complex data)
{ return read_static_compatible_scalar<complex>(file_id, field, data); }


// Functions to create a field with a vector entry
template <class data_t>
bool read_static_compatible_vector(hid_t file_id, std::string field,
			     lila::Vector<data_t> vector)
{
  bool compatible = true;
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  
  // Check if correct datatype
  hid_t datatype_id = H5Dget_type(dataset_id);
  if (!H5Tequal(datatype_id, hdf5_datatype<data_t>()))
    compatible = false;

  // Check if dimensions are OK
  auto dims = get_dataspace_dims(dataset_id);
  if (dims.size() != 1)
    compatible = false;
  
  H5Dclose(dataset_id);
  return compatible;
}

bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Vector<float> data)
{ return read_static_compatible_vector<float>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Vector<double> data)
{ return read_static_compatible_vector<double>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Vector<scomplex> data)
{ return read_static_compatible_vector<scomplex>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Vector<complex> data)
{ return read_static_compatible_vector<complex>(file_id, field, data); }

    
// Functions to create a field with a matrix entry
template <class data_t>
bool read_static_compatible_matrix(hid_t file_id, std::string field,
				lila::Matrix<data_t> matrix)
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
  
  H5Dclose(dataset_id);
  return compatible;
}

bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Matrix<float> data)
{ return read_static_compatible_matrix<float>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Matrix<double> data)
{ return read_static_compatible_matrix<double>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Matrix<scomplex> data)
{ return read_static_compatible_matrix<scomplex>(file_id, field, data); } 
bool read_static_compatible(hid_t file_id, std::string field,
			 lila::Matrix<complex> data)
{ return read_static_compatible_matrix<complex>(file_id, field, data); }
    
}}

#include "create_static_field.h"

#include <lime/hdf5/types.h>

namespace lime { namespace hdf5 {

// Functions to create a field with a scalar entry
template <class data_t>
void create_static_field_scalar(hid_t file_id, std::string field, data_t data)
{
  hsize_t dims[1];
  dims[0] = 1; 
  hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id = H5Dcreate2(file_id, field.c_str(), datatype_id,
				dataspace_id, 
				H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
}

void create_static_field(hid_t file_id, std::string field, int data)
{ create_static_field_scalar<int>(file_id, field, data); }
void create_static_field(hid_t file_id, std::string field, unsigned int data)
{ create_static_field_scalar<unsigned int>(file_id, field, data); }
void create_static_field(hid_t file_id, std::string field, float data)
{ create_static_field_scalar<float>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field, double data)
{ create_static_field_scalar<double>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field, scomplex data)
{ create_static_field_scalar<scomplex>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field, complex data)
{ create_static_field_scalar<complex>(file_id, field, data); }


// Functions to create a field with a vector entry
template <class data_t>
void create_static_field_vector(hid_t file_id, std::string field,
				lila::Vector<data_t> vector)
{
  hsize_t dims[1];
  dims[0] = (hsize_t)vector.size(); 
  hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id = H5Dcreate2(file_id, field.c_str(), datatype_id,
				dataspace_id, 
				H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
}

void create_static_field(hid_t file_id, std::string field,
			 lila::Vector<float> data)
{ create_static_field_vector<float>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field,
			 lila::Vector<double> data)
{ create_static_field_vector<double>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field,
			 lila::Vector<scomplex> data)
{ create_static_field_vector<scomplex>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field,
			 lila::Vector<complex> data)
{ create_static_field_vector<complex>(file_id, field, data); }

    
// Functions to create a field with a matrix entry
template <class data_t>
void create_static_field_matrix(hid_t file_id, std::string field,
				lila::Matrix<data_t> matrix)
{
  hsize_t dims[2];
  dims[0] = matrix.nrows(); 
  dims[1] = matrix.ncols(); 
  hid_t dataspace_id = H5Screate_simple(2, dims, NULL);
  hid_t datatype_id = lime::hdf5::hdf5_datatype<data_t>();
  hid_t dataset_id = H5Dcreate2(file_id, field.c_str(), datatype_id,
				dataspace_id, 
				H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  H5Dclose(dataset_id);
  H5Sclose(dataspace_id);
}

void create_static_field(hid_t file_id, std::string field,
			 lila::Matrix<float> data)
{ create_static_field_matrix<float>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field,
			 lila::Matrix<double> data)
{ create_static_field_matrix<double>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field,
			 lila::Matrix<scomplex> data)
{ create_static_field_matrix<scomplex>(file_id, field, data); } 
void create_static_field(hid_t file_id, std::string field,
			 lila::Matrix<complex> data)
{ create_static_field_matrix<complex>(file_id, field, data); }
    
}}

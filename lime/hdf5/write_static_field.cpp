#include "write_static_field.h"

#include <lime/hdf5/types.h>

namespace lime { namespace hdf5 {

// Functions to write a field with a single entry
template <class data_t>
void write_static_field_single(hid_t file_id, std::string field, data_t data)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
	   &data);
  H5Dclose(dataset_id);
}

void write_static_field(hid_t file_id, std::string field, int data)
{ write_static_field_single<int>(file_id, field, data); }
void write_static_field(hid_t file_id, std::string field, unsigned int data)
{ write_static_field_single<unsigned int>(file_id, field, data); }
void write_static_field(hid_t file_id, std::string field, float data)
{ write_static_field_single<float>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field, double data)
{ write_static_field_single<double>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field, scomplex data)
{ write_static_field_single<scomplex>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field, complex data)
{ write_static_field_single<complex>(file_id, field, data); }


// Functions to write a field with a vector entry
template <class data_t>
void write_static_field_vector(hid_t file_id, std::string field,
				lila::Vector<data_t> vector)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
	   vector.data());
  H5Dclose(dataset_id);
}

void write_static_field(hid_t file_id, std::string field,
			 lila::Vector<float> data)
{ write_static_field_vector<float>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field,
			 lila::Vector<double> data)
{ write_static_field_vector<double>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field,
			 lila::Vector<scomplex> data)
{ write_static_field_vector<scomplex>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field,
			 lila::Vector<complex> data)
{ write_static_field_vector<complex>(file_id, field, data); }

    
// Functions to write a field with a matrix entry
template <class data_t>
void write_static_field_matrix(hid_t file_id, std::string field,
				lila::Matrix<data_t> matrix)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  H5Dwrite(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
	   matrix.data());
  H5Dclose(dataset_id);
}

void write_static_field(hid_t file_id, std::string field,
			 lila::Matrix<float> data)
{ write_static_field_matrix<float>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field,
			 lila::Matrix<double> data)
{ write_static_field_matrix<double>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field,
			 lila::Matrix<scomplex> data)
{ write_static_field_matrix<scomplex>(file_id, field, data); } 
void write_static_field(hid_t file_id, std::string field,
			 lila::Matrix<complex> data)
{ write_static_field_matrix<complex>(file_id, field, data); }
    
}}

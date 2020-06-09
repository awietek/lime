#include "append_extensible_field.h"

#include <lime/hdf5/types.h>
#include <lime/hdf5/utils.h>

namespace lime { namespace hdf5 {

// Functions to write a field with a scalar entry
template <class data_t>
void append_extensible_field_scalar(hid_t file_id, std::string field,
				    data_t data)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();

  // Make dataspace larger by one
  auto dims = get_dataspace_dims(dataset_id);
  assert(dims.size()==2);
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

void append_extensible_field(hid_t file_id, std::string field, int data)
{ append_extensible_field_scalar<int>(file_id, field, data); }
void append_extensible_field(hid_t file_id, std::string field, unsigned data)
{ append_extensible_field_scalar<unsigned int>(file_id, field, data); }
void append_extensible_field(hid_t file_id, std::string field, float data)
{ append_extensible_field_scalar<float>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field, double data)
{ append_extensible_field_scalar<double>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field, scomplex data)
{ append_extensible_field_scalar<scomplex>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field, complex data)
{ append_extensible_field_scalar<complex>(file_id, field, data); }


// Functions to write a field with a vector entry
template <class data_t>
void append_extensible_field_vector(hid_t file_id, std::string field,
				    lila::Vector<data_t> const& vector)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();

  // Make dataspace larger by one
  auto dims = get_dataspace_dims(dataset_id);
  assert(dims.size()==2);
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
			 lila::Vector<float> const& data)
{ append_extensible_field_vector<float>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field,
			 lila::Vector<double> const& data)
{ append_extensible_field_vector<double>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field,
			 lila::Vector<scomplex> const& data)
{ append_extensible_field_vector<scomplex>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field,
			 lila::Vector<complex> const& data)
{ append_extensible_field_vector<complex>(file_id, field, data); }

    
// Functions to write a field with a matrix entry
template <class data_t>
void append_extensible_field_matrix(hid_t file_id, std::string field,
				    lila::Matrix<data_t> const& matrix)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();

  // Make dataspace larger by one
  auto dims = get_dataspace_dims(dataset_id);
  assert(dims.size()==3);
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
  H5Dwrite(dataset_id, datatype_id, memspace_id, filespace_id, H5P_DEFAULT,
	   matrix.data());

  H5Sclose(memspace_id);
  H5Sclose(filespace_id);
  H5Dclose(dataset_id);
}

void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<float> const& data)
{ append_extensible_field_matrix<float>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<double> const& data)
{ append_extensible_field_matrix<double>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<scomplex> const& data)
{ append_extensible_field_matrix<scomplex>(file_id, field, data); } 
void append_extensible_field(hid_t file_id, std::string field,
			     lila::Matrix<complex> const& data)
{ append_extensible_field_matrix<complex>(file_id, field, data); }
    
}}

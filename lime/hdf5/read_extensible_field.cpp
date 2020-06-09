#include "read_extensible_field.h"

#include <lime/hdf5/types.h>
#include <lime/hdf5/utils.h>

namespace lime { namespace hdf5 {

// Functions to read an extensible field with a scalar entry
template <class data_t>
void read_extensible_field_scalar(hid_t file_id, std::string field,
				  std::vector<data_t>& data)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  data.clear();
  data.resize(dims[0]);
  H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
	  data.data());
  H5Dclose(dataset_id);
}

void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<int>& data)
{ read_extensible_field_scalar<int>(file_id, field, data); }
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<unsigned>& data)
{ read_extensible_field_scalar<unsigned int>(file_id, field, data); }
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<float>& data)
{ read_extensible_field_scalar<float>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<double>& data)
{ read_extensible_field_scalar<double>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<scomplex>& data)
{ read_extensible_field_scalar<scomplex>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<complex>& data)
{ read_extensible_field_scalar<complex>(file_id, field, data); }


// Functions to read an extensible field with a vector entry
template <class data_t>
void read_extensible_field_vector(hid_t file_id, std::string field,
				  std::vector<lila::Vector<data_t>>& vectors)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  vectors.clear();
  vectors.resize(dims[0]);
  for (hsize_t idx=0; idx<dims[0]; ++idx)
    {
      vectors[idx].clear();
      vectors[idx].resize(dims[1]);

      hid_t filespace_id = H5Dget_space(dataset_id);
      std::vector<hsize_t> offset = {idx, 0};
      std::vector<hsize_t> ext_dims = {1, dims[1]};
      H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
			  ext_dims.data(), NULL);
      hid_t memspace_id = H5Screate_simple(2, ext_dims.data(), NULL);

      H5Dread(dataset_id, datatype_id, memspace_id, filespace_id,
	      H5P_DEFAULT, vectors[idx].data());
      H5Sclose(filespace_id);
      H5Sclose(memspace_id);
    }
  H5Dclose(dataset_id);
}

void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<float>>& data)
{ read_extensible_field_vector<float>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<double>>& data)
{ read_extensible_field_vector<double>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<scomplex>>& data)
{ read_extensible_field_vector<scomplex>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Vector<complex>>& data)
{ read_extensible_field_vector<complex>(file_id, field, data); }

    
// Functions to read an extensible field with a matrix entry
template <class data_t>
void read_extensible_field_matrix(hid_t file_id, std::string field,
				  std::vector<lila::Matrix<data_t>>& matrices)
{
  hid_t dataset_id = H5Dopen2(file_id, field.c_str(), H5P_DEFAULT);
  hid_t datatype_id = hdf5_datatype<data_t>();
  std::vector<hsize_t> dims = get_dataspace_dims(dataset_id);
  matrices.clear();
  matrices.resize(dims[0]);
  for (hsize_t idx=0; idx<dims[0]; ++idx)
    {
      matrices[idx].clear();
      matrices[idx].resize(dims[1], dims[2]);

      hid_t filespace_id = H5Dget_space(dataset_id);
      std::vector<hsize_t> offset = {idx, 0, 0};
      std::vector<hsize_t> ext_dims = {1, dims[1], dims[2]};
      H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, offset.data(), NULL,
			  ext_dims.data(), NULL);
      hid_t memspace_id = H5Screate_simple(3, ext_dims.data(), NULL);

      H5Dread(dataset_id, datatype_id, memspace_id, filespace_id,
	      H5P_DEFAULT, matrices[idx].data());
      H5Sclose(filespace_id);
      H5Sclose(memspace_id);
    }
  H5Dclose(dataset_id);
}

void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<float>>& data)
{ read_extensible_field_matrix<float>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<double>>& data)
{ read_extensible_field_matrix<double>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<scomplex>>& data)
{ read_extensible_field_matrix<scomplex>(file_id, field, data); } 
void read_extensible_field(hid_t file_id, std::string field,
			   std::vector<lila::Matrix<complex>>& data)
{ read_extensible_field_matrix<complex>(file_id, field, data); }

}}

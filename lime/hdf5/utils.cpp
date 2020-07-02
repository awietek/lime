#include "utils.h"

#include <lime/hdf5/types.h>

namespace lime { namespace hdf5 {

std::vector<hsize_t> get_dataspace_dims(hid_t dataset_id)
{
  hid_t dataspace_id = H5Dget_space(dataset_id);
  int ndims = H5Sget_simple_extent_ndims(dataspace_id);
  std::vector<hsize_t> dims(ndims, 0);
  H5Sget_simple_extent_dims(dataspace_id, dims.data(), NULL);
  H5Sclose(dataspace_id);
  return dims;
}

std::vector<hsize_t> get_dataspace_max_dims(hid_t dataset_id)
{
  hid_t dataspace_id = H5Dget_space(dataset_id);
  int ndims = H5Sget_simple_extent_ndims(dataspace_id);
  std::vector<hsize_t> max_dims(ndims, 0);
  H5Sget_simple_extent_dims(dataspace_id, NULL, max_dims.data());
  H5Sclose(dataspace_id);
  return max_dims;
}

std::string get_attribute_value(hid_t dataset_id, std::string attribute_name)
{
  hid_t attribute_id = H5Aopen(dataset_id, attribute_name.c_str(),
			       H5P_DEFAULT);
  hid_t dtype_id = H5Aget_type(attribute_id);
  hsize_t sz = H5Aget_storage_size(attribute_id);
  char* attribute_value_c = new char[sz+1];
  H5Aread(attribute_id, dtype_id, attribute_value_c);
  attribute_value_c[sz] = '\0';
  std::string attribute_value = std::string(attribute_value_c);
  H5free_memory(attribute_value_c);
  H5Tclose(dtype_id);
  H5Aclose(attribute_id);
  return attribute_value;
}


herr_t H5OvisitCompatible( hid_t object_id, H5_index_t index_type, H5_iter_order_t order, 
			   H5O_iterate_t op, void *op_data )
{
#if defined(H5Ovisit_vers) && H5Ovisit_vers == 3
  return H5Ovisit(object_id, index_type, order, op, op_data, H5O_INFO_BASIC);
#else
  return H5Ovisit(object_id, index_type, order, op, op_data);
#endif
}
    
}}

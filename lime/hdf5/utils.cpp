#include "utils.h"

#include <lime/hdf5/types.h>

namespace lime { namespace hdf5 {

std::vector<hsize_t> dataspace_dims(hid_t dataset_id)
{
  hid_t dataspace_id = H5Dget_space(dataset_id);
  int ndims = H5Sget_simple_extent_ndims(dataspace_id);
  std::vector<hsize_t> dims(ndims, 0);
  H5Sget_simple_extent_dims(dataspace_id, dims.data(), NULL);
  H5Sclose(dataspace_id);
  return dims;
}

    
}}

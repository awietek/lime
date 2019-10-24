// Copyright 2018 Alexander Wietek - All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LIME_DUMPER_H5_DETAIL_H
#define LIME_DUMPER_H5_DETAIL_H

#include <hdf5.h>
#include <lime/detail/h5_types.h>
#include <lime/detail/h5_utils.h>

#ifndef LIME_H5_CHUNKSIZE
#define LIME_H5_CHUNKSIZE 1
#endif

namespace lime
{
  namespace detail
  {
   
    inline hid_t h5_create_timeseries_dataspace_scalar()
    {
      int rank = 1;
      hsize_t dims[1]  = {0};           /* dataset dimensions at creation time */		
      hsize_t maxdims[1] = {H5S_UNLIMITED};
      hid_t dataspace_id = H5Screate_simple(rank, dims, maxdims); 
      assert(dataspace_id > -1);
      return dataspace_id;
    }

    inline hid_t h5_timeseries_chunks_scalar()    
    {
      int rank = 1;
      hsize_t chunk_dims[1] = {LIME_H5_CHUNKSIZE};
      hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
      herr_t status = H5Pset_chunk(prop, rank, chunk_dims);
      assert(status > -1);
      return prop;
    }

    template <class coeff_t>
    inline hid_t h5_create_timeseries_dataset_scalar
    (hid_t file_id, hid_t dataspace_id, std::string tag)
    {
      hid_t datatype = hdf5_datatype<coeff_t>();
      hid_t chunk_prop = h5_timeseries_chunks_scalar();
      hid_t dataset_id = H5Dcreate2(file_id, tag.c_str(), datatype, dataspace_id, 
				    H5P_DEFAULT, chunk_prop, H5P_DEFAULT);
      assert(dataset_id > -1);
      return dataset_id;
    }




    template <class coeff_t>
    inline void dump_to_hdf5_file(Timeseries<coeff_t>& timeseries, hid_t file_id, 
				  std::map<std::string, hid_t>& dataspace_ids,
				  std::map<std::string, hid_t>& dataset_ids, 
				  std::map<std::string, hid_t>& dataset_types, 
				  std::string tag, int& previous_dump)
    {
      if (previous_dump == 0)
	{
	  dataspace_ids[tag] = 
	    h5_create_timeseries_dataspace_scalar();
	  dataset_ids[tag] = h5_create_timeseries_dataset_scalar<coeff_t>
	    (file_id, dataspace_ids[tag], tag);
	  dataset_types[tag] = H5Dget_type(dataset_ids[tag]);
	}

      // Determine current and new shape of dataspace
      int chunk_size = timeseries.size() - previous_dump;
      std::vector<hsize_t> shape = h5_get_shape(dataspace_ids[tag]);
      std::vector<hsize_t> newshape = shape;
      newshape[0] += chunk_size;
      std::vector<hsize_t> diffshape = newshape;
      for (int i=0; i<(int)diffshape.size(); ++i)
	diffshape[i] -= shape[i];
      std::vector<hsize_t> offset = shape;

      // Make dataset larger
      herr_t status = H5Dset_extent(dataset_ids[tag], newshape.data());
      assert(status > -1); 

      hid_t filespace = H5Dget_space(dataset_ids[tag]);
      status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset.data(), 
				   NULL, diffshape.data(), NULL);  
      assert(status > -1);

      hid_t memspace = H5Screate_simple(diffshape.size(), diffshape.data(), NULL);
      assert(memspace > -1);

      // Assemble data and write

      auto data = timeseries.data() + shape[0];

      status = H5Dwrite(dataset_ids[tag], dataset_types[tag], memspace, 
			filespace, H5P_DEFAULT, data);
      assert(status > -1);
      
      H5Sclose(memspace);
      H5Sclose(dataspace_ids[tag]);
      dataspace_ids[tag] = filespace;
      previous_dump = timeseries.size();
    }


  }  // namespace detail

}

#endif

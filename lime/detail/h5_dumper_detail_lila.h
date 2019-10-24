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

#include <map>
#include <string>
#include <algorithm>

#include <hdf5.h>
#include <lime/detail/h5_types.h>
#include <lime/detail/h5_utils.h>
#include <lime/detail/h5_dumper_detail.h>

#ifndef LIME_H5_CHUNKSIZE
#define LIME_H5_CHUNKSIZE 1
#endif

namespace lime
{
  namespace detail
  {

    inline hid_t h5_create_timeseries_dataspace_vector(hsize_t n)    
    {
      int rank = 2;
      hsize_t dims[2]  = {0, n};           /* dataset dimensions at creation time */		
      hsize_t maxdims[2] = {H5S_UNLIMITED, n};
      hid_t dataspace_id = H5Screate_simple(rank, dims, maxdims); 
      assert(dataspace_id > -1);
      return dataspace_id;
    }

    inline hid_t h5_timeseries_chunks_vector(hsize_t n)    
    {
      int rank = 2;
      hsize_t chunksize = std::max(LIME_H5_CHUNKSIZE / n, (hsize_t)1);
      hsize_t chunk_dims[2] = {chunksize, n};
      hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
      herr_t status = H5Pset_chunk(prop, rank, chunk_dims);
      assert(status > -1);
      return prop;
    }

    template <class coeff_t>
    inline hid_t h5_create_timeseries_dataset_vector
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t n)
    {
      hid_t datatype = hdf5_datatype<coeff_t>();
      hid_t chunk_prop = h5_timeseries_chunks_vector(n);
      hid_t dataset_id = H5Dcreate2(file_id, tag.c_str(), datatype, dataspace_id, 
				    H5P_DEFAULT, chunk_prop, H5P_DEFAULT);
      assert(dataset_id > -1);
      return dataset_id;
    }

    template <class coeff_t>
    inline void dump_to_hdf5_file(const Timeseries<lila::Vector<coeff_t>>& timeseries, 
				  hid_t file_id, 
				  std::map<std::string, hid_t>& dataspace_ids,
				  std::map<std::string, hid_t>& dataset_ids, 
				  std::map<std::string, hid_t>& dataset_types, 
				  std::string tag, int& previous_dump)
    {
      assert(timeseries.size() > 0);

      // Check whether timeseries is well-formed
      hsize_t size = (hsize_t)timeseries[0].size();
      for (hsize_t i=0; i<timeseries.size(); ++i)
	assert(timeseries[i].size()==size);
 
      if (previous_dump == 0)
      	{
      	  dataspace_ids[tag] = h5_create_timeseries_dataspace_vector(size);
      	  dataset_ids[tag] = 
      	    h5_create_timeseries_dataset_vector<coeff_t>(file_id, dataspace_ids[tag],
						tag, size);
      	  dataset_types[tag] = H5Dget_type(dataset_ids[tag]);
      	}

      long ndata = timeseries.size() - previous_dump;

      // Write new data layer-by-layer
      for (long layer=0; layer<ndata; ++layer)
	{
	  int chunk_size = 1;
	  std::vector<hsize_t> shape = h5_get_shape(dataspace_ids[tag]);

	  std::vector<hsize_t> newshape = shape;
	  newshape[0] += chunk_size;
	  std::vector<hsize_t> diffshape = newshape;
	  diffshape[0] -= shape[0];
	  std::vector<hsize_t> offset = shape;
	  offset[1] = 0;

	  // Make dataset larger
	  herr_t status = H5Dset_extent(dataset_ids[tag], newshape.data());
	  assert(status > -1); 
	  hid_t filespace = H5Dget_space(dataset_ids[tag]);
	  assert(filespace > -1);
	  
	  status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset.data(), 
				       NULL, diffshape.data(), NULL);  
	  assert(status > -1);
	  hid_t memspace = H5Screate_simple(diffshape.size(), diffshape.data(), NULL);
	  assert(memspace > -1);

	  // Assemble data and write
	  long idx = previous_dump + layer;
	  const coeff_t* data = timeseries[idx].data();

	  status = H5Dwrite(dataset_ids[tag], dataset_types[tag], memspace, 
			    filespace, H5P_DEFAULT, data);
	  assert(status > -1);
	  H5Sclose(memspace);
	  dataspace_ids[tag] = H5Dget_space(dataset_ids[tag]);
	}
      previous_dump = timeseries.size();
    }


  }  // namespace detail

}

#endif

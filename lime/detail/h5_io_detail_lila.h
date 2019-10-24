// Copyright 2019 Alexander Wietek - All Rights Reserved.
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

#ifndef LIME_IO_H5_DETAIL_LILA_H
#define LIME_IO_H5_DETAIL_LILA_H

#include <map>
#include <hdf5.h>
#include <lime/detail/h5_types.h>
#include <lime/detail/h5_utils.h>
#include <lime/detail/h5_dumper_detail_lila.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    inline void writeh5_timeseries_of_vectors
    (const Timeseries<lila::Vector<coeff_t>>& timeseries, 
     std::string filename, std::string tag)
    {
      // Check whether timeseries is well-formed
      assert(timeseries.size() > 0);
      hsize_t vec_length = timeseries[0].size();
      for (hsize_t i=0; i<timeseries.size(); ++i)
	assert(timeseries[i].size()==vec_length);
      
      hid_t file_id = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
      assert(file_id > -1);
      
      std::map<std::string, hid_t> dataspace_ids;
      std::map<std::string, hid_t> dataset_ids; 
      std::map<std::string, hid_t> dataset_types;
      int previous_dump = 0;
      dump_to_hdf5_file(timeseries, file_id, dataspace_ids, dataset_ids, dataset_types, tag, previous_dump);
      
      herr_t status = H5Sclose(dataspace_ids[tag]);
      status = H5Dclose(dataset_ids[tag]);
      status = H5Fclose(file_id);
      assert(status > -1);
    }

    template <class coeff_t>
    inline  Timeseries<lila::Vector<coeff_t>> 
    readh5_timeseries_of_vectors(std::string filename, std::string tag)
    {
      hid_t file = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file > -1);
      hid_t dset = H5Dopen(file, tag.c_str(), H5P_DEFAULT);
      assert(dset > -1);
      hid_t space = H5Dget_space (dset);
      assert(space > -1);

      hid_t ndims = H5Sget_simple_extent_ndims(space);
      assert(ndims == 2);
      hsize_t dims[2];
      H5Sget_simple_extent_dims (space, dims, NULL);
      
      std::vector<coeff_t> array(dims[0]*dims[1], 0);
      herr_t status = H5Dread(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL, H5P_DEFAULT,
			      array.data());
      assert(status > -1);
      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);

      // Assemble time-series
      Timeseries<lila::Vector<coeff_t>> timeseries;
      for (hsize_t i=0; i<dims[0]; ++i)
	{
	  lila::Vector<coeff_t> vec(dims[1]);
	  std::copy(array.begin() + i*dims[1], array.begin() + (i+1)*dims[1], vec.begin());
	  timeseries << vec;
	}
      return timeseries;
    }

  }  // namespace detail
}

#endif

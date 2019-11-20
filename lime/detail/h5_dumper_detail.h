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

#include <string>
#include <map>

#include <hdf5.h>
#include <lime/timeseries.h>

namespace lime
{
  namespace detail
  {
   
    hid_t h5_create_timeseries_dataspace_scalar();
    
    hid_t h5_timeseries_chunks_scalar();    
    
    template <class coeff_t>
    hid_t h5_create_timeseries_dataset_scalar
    (hid_t file_id, hid_t dataspace_id, std::string tag);
    
    template <class coeff_t>
    void dump_to_hdf5_file(Timeseries<coeff_t>& timeseries, hid_t file_id, 
			   std::map<std::string, hid_t>& dataspace_ids,
			   std::map<std::string, hid_t>& dataset_ids, 
			   std::map<std::string, hid_t>& dataset_types, 
			   std::string tag, int& previous_dump);
    
  }  // namespace detail

}

#endif

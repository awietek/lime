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

#ifndef LIME_DUMPER_DETAIL_H
#define LIME_DUMPER_DETAIL_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <lime/timeseries.h>
#include <lime/collection.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    void dump_to_file(Timeseries<coeff_t>& timeseries, 
		      std::ofstream& file, int& previous_dump, 
		      bool write_header, std::string header,
		      int precision)
    {
      assert(file.good());
      for (int idx = previous_dump; idx < timeseries.size(); ++idx)
	file << std::setprecision(precision)
	     << timeseries[idx] << std::endl;
      previous_dump = timeseries.size();
    }

    template <class key_t, class estimator_t>
    void dump_to_file(Collection<key_t, estimator_t>& collection, 
		      std::ofstream& file, int& previous_dump, 
		      bool write_header, std::string header,
		      int precision)
    {
      assert(file.good());
      int timeseries_size = collection.begin()->second.size();

      std::vector<key_t> keys = collection.keys();

      // Check whether all timeseries have the same length
      for (auto key_timeseries : collection)
	assert(timeseries_size == (int)key_timeseries.second.size());	 
    
      // Write the header
      if (write_header && (previous_dump == 0))
	{
	  std::string prefix = "#";
	  if (header != "")
	    file << prefix << " " << header << std::endl;
	  file << prefix << " ";
	  for (auto key : keys)
	    file << key << " ";
	  file << "\n";
	}
      
      // Write the data
      for (int idx = previous_dump; idx < timeseries_size; ++idx)
	{
	  for (auto& key : keys)
	    file << std::setprecision(precision)
		 << collection[key][idx] << " ";
	  file << std::endl;
	}
      previous_dump = timeseries_size;
    }
  }  // namespace detail

}

#endif

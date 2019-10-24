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

#ifndef LIME_DUMPERH5_H
#define LIME_DUMPERH5_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <map>

#include <lime/collection.h>
#include <lime/detail/h5_dumper_detail.h>

namespace lime
{
  template <class timeseries_t>
  class DumperH5
  {
  public:
    DumperH5(timeseries_t& timeseries, std::string filename, std::string tag = "data");
    ~DumperH5();
    void dump();

  private:
    timeseries_t& timeseries_;
    std::string filename_;
    std::string tag_;
    hid_t file_id_;
    std::map<std::string, hid_t> dataspace_ids_;
    std::map<std::string, hid_t> dataset_ids_;
    std::map<std::string, hid_t> dataset_types_;
    int previous_dump_;
  };

  template <class timeseries_t>
  DumperH5<timeseries_t>::DumperH5(timeseries_t& timeseries, 
				   std::string filename, std::string tag)
    : timeseries_(timeseries),
      filename_(filename),
      tag_(tag),
      previous_dump_(0)
  {
    file_id_ = H5Fcreate(filename_.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  }

  template <class timeseries_t>
  DumperH5<timeseries_t>::~DumperH5()
  { 
    herr_t status;
    for (auto id : dataspace_ids_)
      {
	status = H5Sclose(id.second);
	assert(status > -1);
      }

    for (auto id : dataset_ids_)
      {
	status = H5Dclose(id.second);
	assert(status > -1);
      }

    status = H5Fclose(file_id_);
    assert(status > -1);
  }

  template <class timeseries_t>
  void DumperH5<timeseries_t>::dump()
  { 
    detail::dump_to_hdf5_file
      (timeseries_, file_id_, dataspace_ids_, dataset_ids_, dataset_types_,
       tag_, previous_dump_); 
  }

  
  using DumpCollectionH5 = DumperH5<Collection<std::string, lime::Timeseries<double>>>;

  template <class timeseries_t>
  DumperH5<timeseries_t> makeDumperH5(timeseries_t& timeseries, std::string filename)
  { return DumperH5<timeseries_t>(timeseries, filename); }
}

#endif

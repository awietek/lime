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
// #include <lime/detail/h5_dumper_detail_lila.h>
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
  
  using DumpCollectionH5 = DumperH5<Collection<std::string, lime::Timeseries<double>>>;

  template <class timeseries_t>
  DumperH5<timeseries_t> makeDumperH5(timeseries_t& timeseries, std::string filename)
  { return DumperH5<timeseries_t>(timeseries, filename); }

}

#endif

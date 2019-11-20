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

#ifndef LIME_DUMPER_H
#define LIME_DUMPER_H

#include <fstream>
#include <string>

#include <lime/timeseries.h>
#include <lime/collection.h>

namespace lime
{
  template <class timeseries_t>
  class Dumper
  {
  public:
    Dumper(timeseries_t& timeseries, std::string filename,
	   int precision=20);
    ~Dumper();
    
    void set_header(std::string header);
    void dump(bool write_header=true);

  private:
    timeseries_t& timeseries_;
    std::string filename_;
    std::ofstream file_;
    int previous_dump_;
    std::string header_;
    int precision_;
  };

  using DumpCollection = Dumper<Collection<std::string, Timeseries<double>>>;
  
}

#endif

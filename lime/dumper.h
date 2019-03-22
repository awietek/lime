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

#include <cstdlib>
#include <fstream>
#include <string>

#include <lime/collection.h>
#include <lime/detail/dumperdetail.h>

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

  template <class timeseries_t>
  Dumper<timeseries_t>::Dumper(timeseries_t& timeseries, 
			       std::string filename, int precision)
    : timeseries_(timeseries),
      filename_(filename),
      previous_dump_(0),
      header_(""),
      precision_(precision)
  {
    file_.open(filename);
    if(file_.fail()) 
      {
	std::cerr << "Lime, Error while initializing Dumper: " 
		  << "Could not open file with filename ["
		  << filename << "] given. Abort." << std::endl;
	exit(EXIT_FAILURE);
      }
  }

  template <class timeseries_t>
  Dumper<timeseries_t>::~Dumper()
  { file_.close(); }

  template <class timeseries_t>
  void Dumper<timeseries_t>::set_header(std::string header)
  { header_ = header; } 

  template <class timeseries_t>
  void Dumper<timeseries_t>::dump(bool write_header)
  { detail::dump_to_file(timeseries_, file_, previous_dump_, 
			 write_header, header_, precision_); }

  
  using DumpCollection = Dumper<Collection<std::string, lime::Timeseries<double>>>;

}

#endif

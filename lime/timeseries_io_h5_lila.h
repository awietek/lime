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

#ifndef LIME_TIMESERIES_IO_H5_LILA_H
#define LIME_TIMESERIES_IO_H5_LILA_H

#include <string>
#include <complex>

#include <lila/all.h>
#include <lime/timeseries.h>
#include <lime/timeseries_io_h5.h>
#include <lime/detail/h5_io_detail_lila.h>

namespace lime
{

  template <>
  void writeh5<lila::Vector<float>>
  (const Timeseries<lila::Vector<float>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<float>(timeseries, filename, tag);
  }

  template <>
  void writeh5<lila::Vector<double>>
  (const Timeseries<lila::Vector<double>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<double>(timeseries, filename, tag);
  }
  template <>
  void writeh5<lila::Vector<std::complex<float>>>
  (const Timeseries<lila::Vector<std::complex<float>>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<std::complex<float>>
      (timeseries, filename, tag);
  }
  template <>
  void writeh5<lila::Vector<std::complex<double>>>
  (const Timeseries<lila::Vector<std::complex<double>>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<std::complex<double>>
      (timeseries, filename, tag);
  }
 
  template <>
  Timeseries<lila::Vector<float>> readh5(std::string filename, std::string tag)
  { return detail::readh5_timeseries_of_vectors<float>(filename, tag); }
  template <>
  Timeseries<lila::Vector<double>> readh5(std::string filename, std::string tag)
  { return detail::readh5_timeseries_of_vectors<double>(filename, tag); }
  template <>
  Timeseries<lila::Vector<std::complex<float>>> readh5(std::string filename, 
						       std::string tag)
  { return detail::readh5_timeseries_of_vectors<std::complex<float>>
      (filename, tag); }
  template <>
  Timeseries<lila::Vector<std::complex<double>>> readh5(std::string filename, 
							std::string tag)
  { return detail::readh5_timeseries_of_vectors<std::complex<double>>
      (filename, tag); }
 

}

#endif

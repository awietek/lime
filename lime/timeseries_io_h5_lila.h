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

namespace lime
{

  void writeh5
  (const Timeseries<lila::Vector<float>>& timeseries, 
   std::string filename, std::string tag="data");

  void writeh5
  (const Timeseries<lila::Vector<double>>& timeseries, 
   std::string filename, std::string tag="data");

  void writeh5
  (const Timeseries<lila::Vector<std::complex<float>>>& timeseries, 
   std::string filename, std::string tag="data");

  void writeh5
  (const Timeseries<lila::Vector<std::complex<double>>>& timeseries, 
   std::string filename, std::string tag="data");

 
  void writeh5
  (const Timeseries<lila::Matrix<float>>& timeseries, 
   std::string filename, std::string tag="data");

  void writeh5
  (const Timeseries<lila::Matrix<double>>& timeseries, 
   std::string filename, std::string tag="data");

  void writeh5
  (const Timeseries<lila::Matrix<std::complex<float>>>& timeseries, 
   std::string filename, std::string tag="data");

  void writeh5
  (const Timeseries<lila::Matrix<std::complex<double>>>& timeseries, 
   std::string filename, std::string tag="data");

}

#endif

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

#ifndef LIME_TIMESERIESIOH5_H
#define LIME_TIMESERIESIOH5_H

#include <string>
#include <complex>

#include <lime/timeseries.h>

namespace lime
{
  
  void writeh5
  (Timeseries<float> const& timeseries, 
   std::string filename, std::string tag);

  void writeh5
  (Timeseries<double> const& timeseries, 
   std::string filename, std::string tag);

  void writeh5
  (Timeseries<std::complex<float>> const& timeseries, 
   std::string filename, std::string tag);    

  void writeh5
  (Timeseries<std::complex<double>> const& timeseries, 
   std::string filename, std::string tag);

  template <class coeff_t>
  Timeseries<coeff_t> readh5(std::string filename, 
			     std::string tag="data");
  
}

#endif

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
#include <lime/detail/h5_io_detail.h>

namespace lime
{

  template <class coeff_t>
  inline void writeh5(const Timeseries<coeff_t>& timeseries, 
		      std::string filename, std::string tag="data");


  template <>
  inline void writeh5<float>(const Timeseries<float>& timeseries, 
			     std::string filename, std::string tag)
  { 
    detail::writeh5_array_1d<float>(timeseries.size(), timeseries.data(), 
				  filename, tag);
  }

  template <>
  inline void writeh5<double>(const Timeseries<double>& timeseries,
			      std::string filename, std::string tag)
  { 
    detail::writeh5_array_1d<double>(timeseries.size(), timeseries.data(), 
				   filename, tag);
  }
  template <>
  inline void writeh5<std::complex<float>>
  (const Timeseries<std::complex<float>>& timeseries, std::string filename, 
   std::string tag)
  { 
    detail::writeh5_array_1d<std::complex<float>>(timeseries.size(), 
						timeseries.data(), 
						filename, tag);
  }
  template <>
  inline void writeh5<std::complex<double>>
  (const Timeseries<std::complex<double>>& timeseries, std::string filename, 
		    std::string tag)
  { 
    detail::writeh5_array_1d<std::complex<double>>(timeseries.size(), 
						 timeseries.data(), 
						 filename, tag);
  }

  template <class coeff_t>
  inline Timeseries<coeff_t> readh5(std::string filename, 
				    std::string tag="data");
  
  template <>
  inline Timeseries<float> readh5(std::string filename, std::string tag)
  { return Timeseries<float>(detail::readh5_array_1d<float>(filename, tag)); }
    template <>
  inline Timeseries<double> readh5(std::string filename, std::string tag)
  { return Timeseries<double>(detail::readh5_array_1d<double>(filename, tag)); }
  template <>
  inline Timeseries<std::complex<float>> readh5
  (std::string filename, std::string tag)
  { 
    return Timeseries<std::complex<float>>
      (detail::readh5_array_1d<std::complex<float>>(filename, tag)); 
  }
  template <>
  inline Timeseries<std::complex<double>> readh5
  (std::string filename, std::string tag)
   { 
    return Timeseries<std::complex<double>>
      (detail::readh5_array_1d<std::complex<double>>(filename, tag)); 
  }

}

#endif

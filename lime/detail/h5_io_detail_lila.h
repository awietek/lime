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

#ifndef LIME_IO_H5_DETAIL_LILA_H
#define LIME_IO_H5_DETAIL_LILA_H

#include <string>
#include <lila/all.h>
#include <lime/timeseries.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    void writeh5_timeseries_of_vectors
    (Timeseries<lila::Vector<coeff_t>> const& timeseries, 
     std::string filename, std::string tag);

    template <class coeff_t>
    Timeseries<lila::Vector<coeff_t>> 
    readh5_timeseries_of_vectors(std::string filename, std::string tag);

    template <class coeff_t>
    void writeh5_timeseries_of_matrices
    (Timeseries<lila::Matrix<coeff_t>> const& timeseries, 
     std::string filename, std::string tag);

    template <class coeff_t>
    Timeseries<lila::Matrix<coeff_t>> 
    readh5_timeseries_of_matrices(std::string filename, std::string tag);
    
  }  // namespace detail
}

#endif

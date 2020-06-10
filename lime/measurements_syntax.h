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

#ifndef LIME_FILE_MEASUREMENTS_SYNTAX_HANDLER_H
#define LIME_FILE_MEASUREMENTS_SYNTAX_HANDLER_H

#include <string>
#include <vector>
#include <map>
#include <hdf5.h>

#include <lime/hdf5/measurements.h>

namespace lime
{
class MeasurementsSyntaxHandler
  {
  public:
    MeasurementsSyntaxHandler() = delete;
    MeasurementsSyntaxHandler(std::string field, Measurements& measurements);
    MeasurementsSyntaxHandler(MeasurementsSyntaxHandler const&) = delete;
    MeasurementsSyntaxHandler& operator=
    (MeasurementsSyntaxHandler const&) = delete;
    MeasurementsSyntaxHandler(MeasurementsSyntaxHandler&&) = default;
    MeasurementsSyntaxHandler& operator=
    (MeasurementsSyntaxHandler&&) = default;
    ~MeasurementsSyntaxHandler() = default;

    template <class data_t>
    MeasurementsSyntaxHandler& operator<<(data_t const& data);
    template <class data_t>
    MeasurementsSyntaxHandler& operator=(data_t const& data);
    
  private:
    const std::string field_;
    Measurements& measurements_; 
  };
}

#endif

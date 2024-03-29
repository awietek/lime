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

#ifndef LIME_MEASUREMENT_HANDLER_H
#define LIME_MEASUREMENT_HANDLER_H

#include <hdf5.h>
#include <map>
#include <string>
#include <vector>

namespace lime {

class Measurements;
class MeasurementHandler {
public:
  MeasurementHandler() = delete;
  MeasurementHandler(std::string field, Measurements &measurements);
  MeasurementHandler(MeasurementHandler const &) = delete;
  MeasurementHandler &operator=(MeasurementHandler const &) = delete;
  MeasurementHandler(MeasurementHandler &&) = default;
  MeasurementHandler &operator=(MeasurementHandler &&) = default;
  ~MeasurementHandler() = default;

  bool defined();
  std::string type() const;
  long previous_dump() const;
  long size() const;

  template <class data_t> void get(long idx, data_t &data);
  template <class data_t> void operator<<(data_t const &data);

private:
  std::string field_;
  Measurements *measurements_;
};

} // namespace lime

#endif

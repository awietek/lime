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

#ifndef LIME_MEASUREMENTS_H
#define LIME_MEASUREMENTS_H

#include <hdf5.h>
#include <map>
#include <string>
#include <vector>

#include <lime/file_h5.h>
#include <lime/measurement_handler.h>
#include <lime/types.h>

namespace lime {
class Measurements {

public:
  Measurements() = default;
  Measurements(Measurements const &other) = default;
  Measurements &operator=(Measurements const &other) = default;
  Measurements(Measurements &&other) = default;
  Measurements &operator=(Measurements &&other) = default;
  ~Measurements() = default;

  std::vector<std::string> fields() const;

  bool defined(std::string field) const;
  std::string type(std::string field) const;
  long previous_dump(std::string field) const;
  long size(std::string field) const;

  template <class data_t> void append(std::string field, data_t const &data);

  template <class data_t>
  void get(std::string field, long idx, data_t &data) const;

  void read(FileH5 const &file);
  void dump(FileH5 &file);

  MeasurementHandler operator[](std::string const &quantity) {
    return MeasurementHandler(quantity, *this);
  }

  MeasurementHandler operator[](const char *quantity) {
    return operator[](std::string(quantity));
  }

private:
  std::vector<std::string> fields_;
  std::map<std::string, std::string> type_;
  std::map<std::string, long> previous_dump_;

  template <class data_t>
  inline std::map<std::string, std::vector<data_t>> &
  collector(data_t const &data);

  template <class data_t>
  inline std::map<std::string, std::vector<data_t>> const &
  collector(data_t const &data) const;

  std::map<std::string, std::vector<int>> collector_i_sca_;
  std::map<std::string, std::vector<unsigned>> collector_u_sca_;
  std::map<std::string, std::vector<long>> collector_l_sca_;
  std::map<std::string, std::vector<unsigned long>> collector_ul_sca_;
  std::map<std::string, std::vector<long long>> collector_ll_sca_;
  std::map<std::string, std::vector<unsigned long long>> collector_ull_sca_;

  std::map<std::string, std::vector<sscalar>> collector_s_sca_;
  std::map<std::string, std::vector<dscalar>> collector_d_sca_;
  std::map<std::string, std::vector<cscalar>> collector_c_sca_;
  std::map<std::string, std::vector<zscalar>> collector_z_sca_;

  std::map<std::string, std::vector<svector>> collector_s_vec_;
  std::map<std::string, std::vector<dvector>> collector_d_vec_;
  std::map<std::string, std::vector<cvector>> collector_c_vec_;
  std::map<std::string, std::vector<zvector>> collector_z_vec_;

  std::map<std::string, std::vector<smatrix>> collector_s_mat_;
  std::map<std::string, std::vector<dmatrix>> collector_d_mat_;
  std::map<std::string, std::vector<cmatrix>> collector_c_mat_;
  std::map<std::string, std::vector<zmatrix>> collector_z_mat_;
};
} // namespace lime
#endif

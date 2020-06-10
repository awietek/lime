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

#include <string>
#include <vector>
#include <map>
#include <hdf5.h>

#include <lime/hdf5/file_h5.h>

namespace lime
{
  class MeasurementsSyntaxHandler;

  class Measurements
  {
    using scomplex = std::complex<double>;
    using complex = std::complex<double>;
    
    using svector = lila::Vector<float>;
    using dvector = lila::Vector<double>;
    using cvector = lila::Vector<std::complex<float>>;
    using zvector = lila::Vector<std::complex<double>>;
    
    using smatrix = lila::Matrix<float>;
    using dmatrix = lila::Matrix<double>;
    using cmatrix = lila::Matrix<std::complex<float>>;
    using zmatrix = lila::Matrix<std::complex<double>>;

  public:
    Measurements();
    Measurements(Measurements const& other) = default
    Measurements& operator=(Measurements const& other) = default;
    Measurements(Measurements&& other) = default;
    Measurements& operator=(Measurements&& other) = default;
    ~Measurements() = default;

    std::vector<std::string> fields() const { return fields_; }
    std::string type(std::string field) const
    { return type_[field]; }
    long previous_dump(std::string field) const
    { return previous_dump_[field]; }
    MeasurementsSyntaxHandler operator[](std::string quantity)
    { return MeasurementsSyntaxHandler(quantity, *this); }
    
    template <class data_t>
    void append(std::string field, data_t const& data);
    void dump(FileH5& file);
    
  private:
    std::vector<std::string> fields_;
    std::map<std::string, std::string> type_;
    std::map<std::string, long> previous_dump_;

    inline std::map<std::string, std::vector<data_t>>&
    collector_of_type(std::string const& type);
    
    std::map<std::string, std::vector<int>>      collector_i_;
    std::map<std::string, std::vector<unsigned>> collector_u_;
    std::map<std::string, std::vector<float>>    collector_s_;
    std::map<std::string, std::vector<double>>   collector_d_;
    std::map<std::string, std::vector<scomplex>> collector_c_;
    std::map<std::string, std::vector<complex>>  collector_z_;

    std::map<std::string, std::vector<svector>>  collector_s_vec_;
    std::map<std::string, std::vector<dvector>>  collector_d_vec_;
    std::map<std::string, std::vector<cvector>>  collector_c_vec_;
    std::map<std::string, std::vector<zvector>>  collector_z_vec_;
    
    std::map<std::string, std::vector<smatrix>>  collector_s_mat_;
    std::map<std::string, std::vector<dmatrix>>  collector_s_mat_;
    std::map<std::string, std::vector<cmatrix>>  collector_s_mat_;
    std::map<std::string, std::vector<zmatrix>>  collector_s_mat_;
  }

#endif

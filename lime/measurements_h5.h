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

#ifndef LIME_MEASUREMENTS_H5_H
#define LIME_MEASUREMENTS_H5_H

#include <string>
#include <map>
#include <hdf5.h>

#include <lila/all.h>
#include <lime/complex.h>
#include <lime/estimator.h>
#include <lime/timeseries.h>

namespace lime
{

  enum Type { scalar, cscalar, vector, cvector, matrix, cmatrix };

  struct IndexTypeDim
  {
    long index;
    Type type;
    long m,n;
  };

  template <class coeff_t> class AddHandler;
  
  template <class coeff_t=double>
  class MeasurementsH5Tpl
  {
    using rtype = complex::real_t<coeff_t>;
    using ctype = complex::complex_t<coeff_t>;
    using vec_rtype = lila::Vector<complex::real_t<coeff_t>>;
    using vec_ctype = lila::Vector<complex::complex_t<coeff_t>>;
    using mat_rtype = lila::Matrix<complex::real_t<coeff_t>>;
    using mat_ctype = lila::Matrix<complex::complex_t<coeff_t>>;

  public:
    MeasurementsH5Tpl() = delete;
    MeasurementsH5Tpl(std::string filename);
    MeasurementsH5Tpl(MeasurementsH5Tpl const&) = delete;
    MeasurementsH5Tpl& operator=(MeasurementsH5Tpl const&) = delete;
    MeasurementsH5Tpl(MeasurementsH5Tpl&&) = default;
    MeasurementsH5Tpl& operator=(MeasurementsH5Tpl&&) = default;
    ~MeasurementsH5Tpl();

    void add(std::string quantity, rtype const& measurement);
    void add(std::string quantity, ctype const& measurement);
    void add(std::string quantity, vec_rtype const& measurement);
    void add(std::string quantity, vec_ctype const& measurement);
    void add(std::string quantity, mat_rtype const& measurement);
    void add(std::string quantity, mat_ctype const& measurement);

    AddHandler<coeff_t> operator[](std::string quantity)
    { return AddHandler<coeff_t>(quantity, *this); }

    void dump();
    
  private:
    std::string filename_;
    std::vector<std::string> quantities_;
    std::map<std::string, IndexTypeDim> index_type_dim_of_quantity_;

    hid_t file_id_;
    std::map<std::string, hid_t> dataspace_of_quantity_;
    std::map<std::string, hid_t> dataset_of_quantity_;
    std::map<std::string, hid_t> dataset_types_of_quantity_;  
    std::map<std::string, long> previous_dump_of_quantity_;
   
    std::vector<Estimator<rtype>> scalar_estimators_;
    std::vector<Estimator<ctype>> cscalar_estimators_;
    std::vector<Estimator<vec_rtype>> vector_estimators_;
    std::vector<Estimator<vec_ctype>> cvector_estimators_;
    std::vector<Estimator<mat_rtype>> matrix_estimators_;
    std::vector<Estimator<mat_ctype>> cmatrix_estimators_;

    std::vector<Timeseries<rtype>> scalar_timeseries_;
    std::vector<Timeseries<ctype>> cscalar_timeseries_;
    std::vector<Timeseries<vec_rtype>> vector_timeseries_;
    std::vector<Timeseries<vec_ctype>> cvector_timeseries_;
    std::vector<Timeseries<mat_rtype>> matrix_timeseries_;
    std::vector<Timeseries<mat_ctype>> cmatrix_timeseries_;        
  };

  template <class coeff_t>
  class AddHandler
  {
    using rtype = complex::real_t<coeff_t>;
    using ctype = complex::complex_t<coeff_t>;
    using vec_rtype = lila::Vector<complex::real_t<coeff_t>>;
    using vec_ctype = lila::Vector<complex::complex_t<coeff_t>>;
    using mat_rtype = lila::Matrix<complex::real_t<coeff_t>>;
    using mat_ctype = lila::Matrix<complex::complex_t<coeff_t>>;

  public:
    AddHandler() = delete;
    AddHandler(std::string quantity, MeasurementsH5Tpl<coeff_t>& measurements)
      : quantity_(quantity), measurements_(measurements)
    {}
    AddHandler(AddHandler const&) = delete;
    AddHandler& operator=(AddHandler const&) = delete;
    AddHandler(AddHandler&&) = default;
    AddHandler& operator=(AddHandler&&) = default;
    ~AddHandler() = default;
    
    AddHandler& operator<<(rtype const& measurement)
    { measurements_.add(quantity_, measurement); return *this; }
    AddHandler& operator<<(ctype const& measurement)
    { measurements_.add(quantity_, measurement); return *this; }
    AddHandler& operator<<(vec_rtype const& measurement)
    { measurements_.add(quantity_, measurement); return *this; }
    AddHandler& operator<<(vec_ctype const& measurement)
    { measurements_.add(quantity_, measurement); return *this; }
    AddHandler& operator<<(mat_rtype const& measurement)
    { measurements_.add(quantity_, measurement); return *this; }
    AddHandler& operator<<(mat_ctype const& measurement)
    { measurements_.add(quantity_, measurement); return *this; }

  private:
    const std::string quantity_;
    MeasurementsH5Tpl<coeff_t>& measurements_;
  };

  using MeasurementsH5 = MeasurementsH5Tpl<double>;
  using MeasurementsH5Float = MeasurementsH5Tpl<float>;
}

#endif

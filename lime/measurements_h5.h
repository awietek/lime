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

#include <lila/all.h>

namespace lime
{
  
  template <class coeff_t = double>
  class MeasurementsH5
  {
    using rtype = real_t<coeff_t>;
    using ctype = complex_t<coeff_t>;
    using vec_rtype = real_t<coeff_t>;
    using vec_ctype = complex_t<coeff_t>;
    using mat_rtype = real_t<coeff_t>;
    using mat_ctype = complex_t<coeff_t>;

  public:
    MeasurementsH5() = default;
    MeasurementsH5(std::string dumpfile);

    void operator<<(const rtype& x);
    void operator<<(const ctype& x);
    void operator<<(const vec_rtype& x);
    void operator<<(const vec_ctype& x);
    void operator<<(const mat_rtype& x);
    void operator<<(const mat_ctype& x);

  private:
    struct IndexType
    {
      long index;
      enum type { scalar, cscalar, vector, cvector, matrix, cmatrix };
    }

    std::string dumpfile_;
    std::map<std::string, IndexType> index_type_of_quantity_;
    
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
  }

}

#endif

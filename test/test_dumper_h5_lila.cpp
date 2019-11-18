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

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <complex>

#include "catch.hpp"

#include <lime/allh5lila.h>
#include "testutils.h"

template <class coeff_t>
void test_write_timeseries_lila()
{    
  // Check vector functionality
  {
  using vec_t = lila::Vector<coeff_t>;
  int size = 5;

  lime::Timeseries<vec_t> timeseries;
  auto dumper = lime::makeDumperH5(timeseries, "dump.hdf5");
  for (int k = 0; k < 2; ++k)
    {
      for (int i = 0; i < 3; ++i)
  	{
  	  auto vec = lila::Random<coeff_t>(size);
  	  // LilaPrint(vec);
  	  timeseries << vec;
  	}
      dumper.dump();
    }

  // Write using normal write function and read again
  lime::writeh5(timeseries, "dump2.hdf5");
  auto timeseries2 = lime::readh5<vec_t>("dump.hdf5");
  auto timeseries3 = lime::readh5<vec_t>("dump2.hdf5");  

  // Check, whether timeseries after IO is still the same
  REQUIRE(timeseries.size() == timeseries2.size());
  REQUIRE(timeseries.size() == timeseries3.size());
  for (int i=0; i<(int)timeseries.size(); ++i)
    {
      for(int m=0; m<timeseries[i].size(); ++m)
  	{
  	  REQUIRE(timeseries[i](m) == timeseries2[i](m));
  	  REQUIRE(timeseries[i](m) == timeseries3[i](m));
  	}
    }
  }

  // Check matrix funcitonality
  {
    using mat_t = lila::Matrix<coeff_t>;
    int nrows = 3;
    int ncols = 4;

    lime::Timeseries<mat_t> timeseries;
    auto dumper = lime::makeDumperH5(timeseries, "dump.hdf5");
    for (int k = 0; k < 2; ++k)
      {
	for (int i = 0; i < 2; ++i)
	  {
	    auto mat = lila::Random<coeff_t>(nrows, ncols);
	    // LilaPrint(mat);
	    timeseries << mat;
	  }
	dumper.dump();
      }

    // Write using normal write function and read again
    lime::writeh5(timeseries, "dump2.hdf5");
    auto timeseries2 = lime::readh5<mat_t>("dump.hdf5");
    auto timeseries3 = lime::readh5<mat_t>("dump2.hdf5");  

    // Check, whether timeseries after IO is still the same
    REQUIRE(timeseries.size() == timeseries2.size());
    REQUIRE(timeseries.size() == timeseries3.size());
    for (int i=0; i<(int)timeseries.size(); ++i)
      {
	for(int m=0; m<nrows; ++m)
	  for(int n=0; n<ncols; ++n)
	    {
	      REQUIRE(timeseries[i](m, n) == timeseries2[i](m, n));
	      REQUIRE(timeseries[i](m, n) == timeseries3[i](m, n));
	    }
      }
  }
}

TEST_CASE( "hdf5dumper lila test", "[hdf5dumperlila]" ) {
  test_write_timeseries_lila<float>();
  test_write_timeseries_lila<double>();
  test_write_timeseries_lila<std::complex<float>>();
  test_write_timeseries_lila<std::complex<double>>();  
}

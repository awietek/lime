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

#include <lime/allh5.h>
#include "testutils.h"


template <class coeff_t>
void test_write_timeseries()
{    
  std::random_device rd{};
  std::mt19937 gen{rd()};

  lime::Timeseries<coeff_t> timeseries;

  // Create timeseries and write using dumper
  auto dumper = lime::makeDumperH5(timeseries, "dump.hdf5");
  for (int k = 0; k < 10; ++k)
    {
      for (int i = 0; i < 10; ++i)
	{
	  coeff_t val = testutils::rdm<coeff_t>(gen);
	  timeseries << val;
	}
      dumper.dump();
    }

  // // Write using normal write function and read again
  lime::writeh5(timeseries, "dump2.hdf5");
  auto timeseries2 = lime::readh5<coeff_t>("dump.hdf5");
  auto timeseries3 = lime::readh5<coeff_t>("dump2.hdf5");  

  // Check, whether timeseries after IO is still the same
  REQUIRE(timeseries.size() == timeseries2.size());
  REQUIRE(timeseries.size() == timeseries3.size());
  for (int i=0; i<(int)timeseries.size(); ++i)
    {
      REQUIRE(timeseries[i] == timeseries2[i]);
      REQUIRE(timeseries[i] == timeseries3[i]);
      // std::cout << timeseries[i] << " " << timeseries2[i] << " " 
      // 		<< timeseries3[i] << "\n";
    }
}

TEST_CASE( "hdf5dumper test", "[hdf5dumper]" ) {
  test_write_timeseries<float>();
  test_write_timeseries<double>();
  test_write_timeseries<std::complex<float>>();
  test_write_timeseries<std::complex<double>>();  
}

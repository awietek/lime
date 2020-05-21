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
#include <random>
#include <chrono>

#include "catch.hpp"

#include <lila/all.h>
#include <lime/all.h>

#define DURATION(label, t1, t2) std::cout<<label<<" "<<std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<"\n"
#define CLK(t) t=std::chrono::high_resolution_clock::now()

TEST_CASE( "measurements_h5", "[measurements_h5]" ) {
  std::string dumpfile = "dumpm.hdf5";
  auto measurements = lime::MeasurementsH5(dumpfile);

  int niters = 10;
  int dim=128;

  auto CLK(t1);
  for (int i=0; i<niters; ++i)
    {
      measurements["test"] << (double)i;
      measurements.dump();
    }
  auto CLK(t2);

  // auto measurements2 = lime::ReadMeasurementsH5(dumpfile);

  // REQUIRE(measurements == measurements2);
  
  DURATION("Time2 ", t1, t2);
}

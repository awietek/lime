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

  int niters = 1000000;
  int dim=128;

  auto CLK(t1);
  for (int i=0; i<niters; ++i)
    {
      // auto v1 = lila::Random<double>(dim);
      // auto cv1 = lila::Random<std::complex<double>>(dim);
      // auto m1 = lila::Random<double>(dim,dim);
      // auto cm1 = lila::Random<std::complex<double>>(dim,dim);
      // double s1 = v1(0);
      // std::complex<double> cs1 = cv1(0);  

      // if (i >= 9995)
      // 	{
      // 	  LilaPrint(s1);
      // 	  LilaPrint(cs1);
      // 	  LilaPrint(v1);
      // 	  LilaPrint(cv1);
      // 	  LilaPrint(m1);
      // 	  LilaPrint(cm1);
      // 	}

      // measurements.add("s", s1);
      // measurements.add("cs", cs1);
      // measurements.add("v", v1);
      // measurements.add("cv", cv1);
      // measurements.add("m", m1);
      // measurements.add("cm", cm1);



      // measurements["s"] << s1;
      // measurements["cs"] << cs1;
      // measurements["v"] << v1;
      // measurements["cv"] << cv1;
      // measurements["m"] << m1;
      // measurements["cm"] << cm1;

      // measurements["s"] << 1.23;
      // measurements.add("s", 1.23);

      measurements.dump();
    }
  auto CLK(t2);
  DURATION("Time2 ", t1, t2);
}

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

#include "catch.hpp"

#include <lila/all.h>
#include <lime/all.h>

using namespace lime;

template <class data_t>
void check_field_agrees(Measurements &m1, Measurements &m2, std::string field) {
  REQUIRE(m1[field].size() == m2[field].size());
  for (long idx = 0; idx < m1[field].size(); ++idx) {
    data_t d1, d2;
    m1[field].get(idx, d1);
    m2[field].get(idx, d2);
    REQUIRE(d1 == d2);
  }
}

void check_all_fields_agree(Measurements &m1, Measurements &m2) {
  check_field_agrees<int>(m1, m2, "int");
  check_field_agrees<unsigned>(m1, m2, "unsigned");
  check_field_agrees<long>(m1, m2, "long");
  check_field_agrees<unsigned long>(m1, m2, "unsigned long");
  check_field_agrees<long long>(m1, m2, "long long");
  check_field_agrees<unsigned long long>(m1, m2, "unsigned long long");

  check_field_agrees<sscalar>(m1, m2, "sscalar");
  check_field_agrees<dscalar>(m1, m2, "dscalar");
  check_field_agrees<cscalar>(m1, m2, "cscalar");
  check_field_agrees<zscalar>(m1, m2, "zscalar");

  check_field_agrees<svector>(m1, m2, "svector");
  check_field_agrees<dvector>(m1, m2, "dvector");
  check_field_agrees<cvector>(m1, m2, "cvector");
  check_field_agrees<zvector>(m1, m2, "zvector");

  check_field_agrees<smatrix>(m1, m2, "smatrix");
  check_field_agrees<dmatrix>(m1, m2, "dmatrix");
  check_field_agrees<cmatrix>(m1, m2, "cmatrix");
  check_field_agrees<zmatrix>(m1, m2, "zmatrix");
}

TEST_CASE("measurements", "[measurements]") {

  std::string filename = "test_file.h5";
  remove(filename.c_str());
  auto file = lime::FileH5(filename, "w");
  auto m1 = lime::Measurements();

  // Perform measurements
  for (int idx = 0; idx < 10; ++idx) {
    m1["int"] << (int)idx;
    m1["unsigned"] << (unsigned)idx;
    m1["long"] << (long)idx;
    m1["unsigned long"] << (unsigned long)idx;
    m1["long long"] << (long long)idx;
    m1["unsigned long long"] << (unsigned long long)idx;

    m1["sscalar"] << (sscalar)idx;
    m1["dscalar"] << (dscalar)idx;
    m1["cscalar"] << (cscalar)idx;
    m1["zscalar"] << (zscalar)idx;

    m1["svector"] << lila::Random<sscalar>(5);
    m1["dvector"] << lila::Random<dscalar>(5);
    m1["cvector"] << lila::Random<cscalar>(5);
    m1["zvector"] << lila::Random<zscalar>(5);

    m1["smatrix"] << lila::Random<sscalar>(5, 4);
    m1["dmatrix"] << lila::Random<dscalar>(5, 4);
    m1["cmatrix"] << lila::Random<cscalar>(5, 4);
    m1["zmatrix"] << lila::Random<zscalar>(5, 4);
    if (idx % 3 == 0)
      m1.dump(file);
  }
  file.close();

  // Read in measurements from file and check if same value
  file = lime::FileH5(filename, "a");
  auto m2 = lime::Measurements();
  m2.read(file);
  check_all_fields_agree(m1, m2);

  // Perform more measurements
  for (int idx = 0; idx < 10; ++idx) {
    m2["int"] << (int)idx;
    m2["unsigned"] << (unsigned)idx;
    m2["long"] << (long)idx;
    m2["unsigned long"] << (unsigned long)idx;
    m2["long long"] << (long long)idx;
    m2["unsigned long long"] << (unsigned long long)idx;

    m2["sscalar"] << (sscalar)idx;
    m2["dscalar"] << (dscalar)idx;
    m2["cscalar"] << (cscalar)idx;
    m2["zscalar"] << (zscalar)idx;

    m2["svector"] << lila::Random<sscalar>(5);
    m2["dvector"] << lila::Random<dscalar>(5);
    m2["cvector"] << lila::Random<cscalar>(5);
    m2["zvector"] << lila::Random<zscalar>(5);

    m2["smatrix"] << lila::Random<sscalar>(5, 4);
    m2["dmatrix"] << lila::Random<dscalar>(5, 4);
    m2["cmatrix"] << lila::Random<cscalar>(5, 4);
    m2["zmatrix"] << lila::Random<zscalar>(5, 4);
    if (idx % 3 == 0)
      m2.dump(file);
  }
  file.close();

  // Read in measurements from file and check if same value
  file = lime::FileH5(filename, "r");
  auto m3 = lime::Measurements();
  m3.read(file);
  check_all_fields_agree(m2, m3);
  file.close();

  remove(filename.c_str());
}

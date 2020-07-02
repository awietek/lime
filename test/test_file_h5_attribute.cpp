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

#include <complex>
#include <iostream>
#include <stdio.h>

#include "catch.hpp"

#include <lime/all.h>

template <class data_t> void test_file_h5_attribute_scalar() {
  std::string filename = "test_file.h5";
  std::string attribute_name = "namesca";
  std::string attribute_value = "valuesca";
  remove(filename.c_str());
  // Test write/read
  data_t val1 = (data_t)42;
  auto file = lime::FileH5(filename, "w");
  file["test"] = val1;
  file["test"].set_attribute(attribute_name, attribute_value);
  REQUIRE(file["test"].has_attribute(attribute_name));
  REQUIRE(file["test"].attribute(attribute_name) == attribute_value);
  file.close();

  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].has_attribute(attribute_name));
  REQUIRE(file["test"].attribute(attribute_name) == attribute_value);
  file.close();
  remove(filename.c_str());
}

template <class data_t> void test_file_h5_attribute_vector() {
  std::string filename = "test_file.h5";
  std::string attribute_name = "namevec";
  std::string attribute_value = "valuevec";
  remove(filename.c_str());

  auto vec1 = lila::Random<data_t>(10);
  auto file = lime::FileH5(filename, "w");
  file["test"] = vec1;
  file["test"].set_attribute(attribute_name, attribute_value);
  REQUIRE(file["test"].has_attribute(attribute_name));
  REQUIRE(file["test"].attribute(attribute_name) == attribute_value);
  file.close();

  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].has_attribute(attribute_name));
  REQUIRE(file["test"].attribute(attribute_name) == attribute_value);
  file.close();
  remove(filename.c_str());
}

template <class data_t> void test_file_h5_attribute_matrix() {
  std::string filename = "test_file.h5";
  std::string attribute_name = "namemat";
  std::string attribute_value = "valuemat";
  remove(filename.c_str());

  auto mat1 = lila::Random<data_t>(10, 10);
  auto file = lime::FileH5(filename, "w");
  file["test"] = mat1;
  file["test"].set_attribute(attribute_name, attribute_value);
  REQUIRE(file["test"].has_attribute(attribute_name));
  REQUIRE(file["test"].attribute(attribute_name) == attribute_value);
  file.close();

  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].has_attribute(attribute_name));
  REQUIRE(file["test"].attribute(attribute_name) == attribute_value);
  file.close();
  remove(filename.c_str());
}

TEST_CASE("file_h5_attribute", "[file]") {
  test_file_h5_attribute_scalar<int>();
  test_file_h5_attribute_scalar<unsigned int>();
  test_file_h5_attribute_scalar<long>();
  test_file_h5_attribute_scalar<unsigned long>();
  test_file_h5_attribute_scalar<long long>();
  test_file_h5_attribute_scalar<unsigned long long>();

  test_file_h5_attribute_scalar<float>();
  test_file_h5_attribute_scalar<double>();
  test_file_h5_attribute_scalar<std::complex<float>>();
  test_file_h5_attribute_scalar<std::complex<double>>();

  test_file_h5_attribute_vector<float>();
  test_file_h5_attribute_vector<double>();
  test_file_h5_attribute_vector<std::complex<float>>();
  test_file_h5_attribute_vector<std::complex<double>>();

  test_file_h5_attribute_matrix<float>();
  test_file_h5_attribute_matrix<double>();
  test_file_h5_attribute_matrix<std::complex<float>>();
  test_file_h5_attribute_matrix<std::complex<double>>();
}

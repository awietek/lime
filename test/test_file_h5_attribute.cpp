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
#include <complex>
#include <stdio.h>


#include "catch.hpp"

#include <lime/all.h>

template <class data_t>
void test_file_h5_attribute_single()
{
  std::string filename = "test_file.h5";
  std::string attribute_name = "namesca";
  std::string attribute_value = "valuesca";
  remove(filename.c_str());
  // Test write/read
  data_t val1 = (data_t)42;
  auto file = lime::FileH5(filename, "w");
  file.write("test", val1);
  file.set_attribute("test", attribute_name, attribute_value);
  REQUIRE(file.has_attribute("test", attribute_name));
  REQUIRE(file.attribute("test", attribute_name) == attribute_value);
  file.close();

  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.has_attribute("test", attribute_name));
  REQUIRE(file.attribute("test", attribute_name) == attribute_value);
  file.close();
  remove(filename.c_str());
}

template <class data_t>
void test_file_h5_attribute_vector()
{
  std::string filename = "test_file.h5";
  std::string attribute_name = "namevec";
  std::string attribute_value = "valuevec";
  remove(filename.c_str());
  
  auto vec1 = lila::Random<data_t>(10);
  auto file = lime::FileH5(filename, "w");
  file.write("test", vec1);
  file.set_attribute("test", attribute_name, attribute_value);
  REQUIRE(file.has_attribute("test", attribute_name));
  REQUIRE(file.attribute("test", attribute_name) == attribute_value);
  file.close();

  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.has_attribute("test", attribute_name));
  REQUIRE(file.attribute("test", attribute_name) == attribute_value);
  file.close();
  remove(filename.c_str());
}

template <class data_t>
void test_file_h5_attribute_matrix()
{
  std::string filename = "test_file.h5";
  std::string attribute_name = "namemat";
  std::string attribute_value = "valuemat";
  remove(filename.c_str());

  auto mat1 = lila::Random<data_t>(10,10);
  auto file = lime::FileH5(filename, "w");
  file.write("test", mat1);
  file.set_attribute("test", attribute_name, attribute_value);
  REQUIRE(file.has_attribute("test", attribute_name));
  REQUIRE(file.attribute("test", attribute_name) == attribute_value);
  file.close();

  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.has_attribute("test", attribute_name));
  REQUIRE(file.attribute("test", attribute_name) == attribute_value);
  file.close();  
  remove(filename.c_str());
}

TEST_CASE( "file_h5_attribute", "[file]" ) {
  test_file_h5_attribute_single<int>();
  test_file_h5_attribute_single<unsigned int>();
  test_file_h5_attribute_single<float>();
  test_file_h5_attribute_single<double>();
  test_file_h5_attribute_single<std::complex<float>>();
  test_file_h5_attribute_single<std::complex<double>>();

  test_file_h5_attribute_vector<float>();
  test_file_h5_attribute_vector<double>();
  test_file_h5_attribute_vector<std::complex<float>>();
  test_file_h5_attribute_vector<std::complex<double>>();

  test_file_h5_attribute_matrix<float>();
  test_file_h5_attribute_matrix<double>();
  test_file_h5_attribute_matrix<std::complex<float>>();
  test_file_h5_attribute_matrix<std::complex<double>>();
}

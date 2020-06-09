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
void test_file_h5_rdwr_single()
{
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  data_t val1 = (data_t)42;
  auto file = lime::FileH5(filename, "w");
  file.write("test", val1);
  file.close();

  data_t val2;
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(!file.field_extensible("test"));
  file.read("test", val2);
  file.close();

  REQUIRE(val1 == val2);
  remove(filename.c_str());
}

template <class data_t>
void test_file_h5_rdwr_vector()
{
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  
  auto vec1 = lila::Random<data_t>(10);
  auto file = lime::FileH5(filename, "w");
  file.write("test", vec1);
  file.close();
    
  auto vec2 = lila::Vector<data_t>();
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(vec1));
  REQUIRE(!file.field_extensible("test"));
  file.read("test", vec2);
  file.close();

  REQUIRE(lila::equal(vec1, vec2));
  remove(filename.c_str());
}

template <class data_t>
void test_file_h5_rdwr_matrix()
{
  std::string filename = "test_file.h5";
  remove(filename.c_str());

  auto mat1 = lila::Random<data_t>(10,10);
  auto file = lime::FileH5(filename, "w");
  file.write("test", mat1);
  file.close();
    
  auto mat2 = lila::Matrix<data_t>();
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(mat1));
  REQUIRE(!file.field_extensible("test"));
  file.read("test", mat2);
  file.close();
    
  REQUIRE(lila::equal(mat1, mat2));    
  remove(filename.c_str());
}

TEST_CASE( "file_h5_rdwr", "[file]" ) {
  test_file_h5_rdwr_single<int>();
  test_file_h5_rdwr_single<unsigned int>();
  test_file_h5_rdwr_single<float>();
  test_file_h5_rdwr_single<double>();
  test_file_h5_rdwr_single<std::complex<float>>();
  test_file_h5_rdwr_single<std::complex<double>>();

  test_file_h5_rdwr_vector<float>();
  test_file_h5_rdwr_vector<double>();
  test_file_h5_rdwr_vector<std::complex<float>>();
  test_file_h5_rdwr_vector<std::complex<double>>();

  test_file_h5_rdwr_matrix<float>();
  test_file_h5_rdwr_matrix<double>();
  test_file_h5_rdwr_matrix<std::complex<float>>();
  test_file_h5_rdwr_matrix<std::complex<double>>();
}

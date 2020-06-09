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
void test_file_h5_append_single()
{
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  data_t val1 = (data_t)42;
  data_t val2 = (data_t)43;
  auto file = lime::FileH5(filename, "w");
  file.append("test", val1);
  file.append("test", val2);
  file.close();

  // reopen in append mode and append
  file = lime::FileH5(filename, "a");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  data_t val3 = (data_t)44;
  data_t val4 = (data_t)45;
  data_t val5 = (data_t)46;
  file.append("test", val3);
  file.append("test", val4);
  file.append("test", val5);
  file.close();

  // reopen in read mode and see if all 5 values agree
  std::vector<data_t> vals;
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  file.read("test", vals);
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();


  // Test reading
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  file.read("test", vals);
  data_t valx = (data_t)44;
  try
    {
      file.append("test", valx);
    }
  catch (std::runtime_error e)
    {
      std::string msg = e.what();
      REQUIRE(msg.find(std::string("cannot append in read mode")));
    }
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();
  
  remove(filename.c_str());
}

template <class data_t>
void test_file_h5_append_vector()
{
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  auto val1 = lila::Random<data_t>(10);
  auto val2 = lila::Random<data_t>(10);
  auto file = lime::FileH5(filename, "w");
  file.append("test", val1);
  file.append("test", val2);
  file.close();

  // reopen in append mode and append
  file = lime::FileH5(filename, "a");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  auto val3 = lila::Random<data_t>(10);
  auto val4 = lila::Random<data_t>(10);
  auto val5 = lila::Random<data_t>(10);
  file.append("test", val3);
  file.append("test", val4);
  file.append("test", val5);
  file.close();

  // reopen in read mode and see if all 5 values agree
  std::vector<lila::Vector<data_t>> vals;
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  file.read("test", vals);
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();


  // Test reading
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  file.read("test", vals);
  auto valx = lila::Random<data_t>(10);
  try
    {
      file.append("test", valx);
    }
  catch (std::runtime_error e)
    {
      std::string msg = e.what();
      REQUIRE(msg.find(std::string("cannot append in read mode")));
    }
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();
  
  remove(filename.c_str());
}

template <class data_t>
void test_file_h5_append_matrix()
{
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  auto val1 = lila::Random<data_t>(10,9);
  auto val2 = lila::Random<data_t>(10,9);
  auto file = lime::FileH5(filename, "w");
  file.append("test", val1);
  file.append("test", val2);
  file.close();

  // reopen in append mode and append
  file = lime::FileH5(filename, "a");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  auto val3 = lila::Random<data_t>(10,9);
  auto val4 = lila::Random<data_t>(10,9);
  auto val5 = lila::Random<data_t>(10,9);
  file.append("test", val3);
  file.append("test", val4);
  file.append("test", val5);
  file.close();

  // reopen in read mode and see if all 5 values agree
  std::vector<lila::Matrix<data_t>> vals;
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  file.read("test", vals);
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();


  // Test reading
  file = lime::FileH5(filename, "r");
  REQUIRE(file.has_field("test"));
  REQUIRE(file.field_type("test") == lime::hdf5::field_type_string(val1));
  REQUIRE(file.field_extensible("test"));
  file.read("test", vals);
  auto valx = lila::Random<data_t>(10,9);
  try
    {
      file.append("test", valx);
    }
  catch (std::runtime_error e)
    {
      std::string msg = e.what();
      REQUIRE(msg.find(std::string("cannot append in read mode")));
    }
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();
  
  remove(filename.c_str());
}

TEST_CASE( "file_h5_append", "[file]" ) {
  test_file_h5_append_single<int>();
  test_file_h5_append_single<unsigned int>();
  test_file_h5_append_single<float>();
  test_file_h5_append_single<double>();
  test_file_h5_append_single<std::complex<float>>();
  test_file_h5_append_single<std::complex<double>>();

  test_file_h5_append_vector<float>();
  test_file_h5_append_vector<double>();
  test_file_h5_append_vector<std::complex<float>>();
  test_file_h5_append_vector<std::complex<double>>();

  test_file_h5_append_matrix<float>();
  test_file_h5_append_matrix<double>();
  test_file_h5_append_matrix<std::complex<float>>();
  test_file_h5_append_matrix<std::complex<double>>();
}

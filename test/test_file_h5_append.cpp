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

template <class data_t> void test_file_h5_append_scalar() {
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  data_t val1 = (data_t)42;
  data_t val2 = (data_t)43;
  auto file = lime::FileH5(filename, "w");
  file["test"] << val1;
  file["test"] << val2;
  file.close();

  // reopen in append mode and append
  file = lime::FileH5(filename, "a");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  data_t val3 = (data_t)44;
  data_t val4 = (data_t)45;
  data_t val5 = (data_t)46;
  file["test"] << val3;
  file["test"] << val4;
  file["test"] << val5;
  file.close();

  // reopen in read mode and see if all 5 values agree
  std::vector<data_t> vals;
  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  file["test"].read(vals);
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();

  // Test reading
  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  file["test"].read(vals);
  data_t valx = (data_t)44;
  try {
    file["test"] << valx;
  } catch (std::runtime_error const& e) {
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

template <class data_t> void test_file_h5_append_vector() {
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  auto val1 = lila::Random<data_t>(10);
  auto val2 = lila::Random<data_t>(10);
  auto file = lime::FileH5(filename, "w");
  file["test"] << val1;
  file["test"] << val2;
  file.close();

  // reopen in append mode and append
  file = lime::FileH5(filename, "a");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  auto val3 = lila::Random<data_t>(10);
  auto val4 = lila::Random<data_t>(10);
  auto val5 = lila::Random<data_t>(10);
  file["test"] << val3;
  file["test"] << val4;
  file["test"] << val5;
  file.close();

  // reopen in read mode and see if all 5 values agree
  std::vector<lila::Vector<data_t>> vals;
  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  file["test"].read(vals);
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();

  // Test reading
  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  file["test"].read(vals);
  auto valx = lila::Random<data_t>(10);
  try {
    file["test"] << valx;
  } catch (std::runtime_error const& e) {
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

template <class data_t> void test_file_h5_append_matrix() {
  std::string filename = "test_file.h5";
  remove(filename.c_str());
  // Test write/read
  auto val1 = lila::Random<data_t>(10, 9);
  auto val2 = lila::Random<data_t>(10, 9);
  auto file = lime::FileH5(filename, "w");
  file["test"] << val1;
  file["test"] << val2;
  file.close();

  // reopen in append mode and append
  file = lime::FileH5(filename, "a");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  auto val3 = lila::Random<data_t>(10, 9);
  auto val4 = lila::Random<data_t>(10, 9);
  auto val5 = lila::Random<data_t>(10, 9);
  file["test"] << val3;
  file["test"] << val4;
  file["test"] << val5;
  file.close();

  // reopen in read mode and see if all 5 values agree
  std::vector<lila::Matrix<data_t>> vals;
  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  file["test"].read(vals);
  REQUIRE(val1 == vals[0]);
  REQUIRE(val2 == vals[1]);
  REQUIRE(val3 == vals[2]);
  REQUIRE(val4 == vals[3]);
  REQUIRE(val5 == vals[4]);
  file.close();

  // Test reading
  file = lime::FileH5(filename, "r");
  REQUIRE(file["test"].defined());
  REQUIRE(file["test"].type() == lime::type_string(val1));
  REQUIRE(file["test"].extensible());
  file["test"].read(vals);
  auto valx = lila::Random<data_t>(10, 9);
  try {
    file["test"] << valx;
  } catch (std::runtime_error const& e) {
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

TEST_CASE("file_h5_append", "[file]") {
  test_file_h5_append_scalar<int>();
  test_file_h5_append_scalar<unsigned int>();
  test_file_h5_append_scalar<long>();
  test_file_h5_append_scalar<unsigned long>();
  test_file_h5_append_scalar<long long>();
  test_file_h5_append_scalar<unsigned long long>();

  test_file_h5_append_scalar<float>();
  test_file_h5_append_scalar<double>();
  test_file_h5_append_scalar<std::complex<float>>();
  test_file_h5_append_scalar<std::complex<double>>();

  test_file_h5_append_vector<float>();
  test_file_h5_append_vector<double>();
  test_file_h5_append_vector<std::complex<float>>();
  test_file_h5_append_vector<std::complex<double>>();

  test_file_h5_append_matrix<float>();
  test_file_h5_append_matrix<double>();
  test_file_h5_append_matrix<std::complex<float>>();
  test_file_h5_append_matrix<std::complex<double>>();
}

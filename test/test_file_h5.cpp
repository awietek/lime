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
#include <stdexcept>
#include <stdio.h>


#include "catch.hpp"

#include <lime/all.h>

TEST_CASE( "file_h5", "[file]" ) {

  std::string filename = "test_file.h5";

  
  // File opening tests
  auto file_default_construct = lime::FileH5();
  REQUIRE(!file_default_construct);

  // Check if reading non-existent file throws correct exception
  remove(filename.c_str()); 
  try
    {
      auto fl = lime::FileH5(filename, "r");
    }
  catch (std::runtime_error e)
    {
      std::string msg = e.what();
      REQUIRE(msg.find(std::string("(r)")));
      REQUIRE(msg.find(filename));
    }

  // Test opening a file in write mode
  remove(filename.c_str());
  auto file = lime::FileH5(filename, "w");
  REQUIRE(file);

  // Check trying to open existing file in write mode throws expection
  try
    {
      auto fl = lime::FileH5(filename, "w");
    }
  catch (std::runtime_error e)
    {
      std::string msg = e.what();
      REQUIRE(msg.find(std::string("(w)")));
      REQUIRE(msg.find(filename));
    } 

  // Check trying to open already opened existing file in forced
  // write mode throws expection
  try
    {
      auto fl = lime::FileH5(filename, "w!");
    }
  catch (std::runtime_error e)
    {
      std::string msg = e.what();
      REQUIRE(msg.find(std::string("(w!)")));
      REQUIRE(msg.find(filename));
    }

  // Check if overwriting file works
  file.close();
  REQUIRE(!file);
  file = lime::FileH5(filename, "w!");
  REQUIRE(file);
  file.close();

  // // Check if appending to  file works
  file = lime::FileH5(filename, "a");
  REQUIRE(file);
  file.close();
  
  remove(filename.c_str());

}

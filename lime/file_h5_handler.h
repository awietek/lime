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

#ifndef LIME_FILE_H5_HANDLER_H
#define LIME_FILE_H5_HANDLER_H

#include <string>
#include <vector>
#include <map>
#include <hdf5.h>

namespace lime
{
class FileH5;
class FileH5Handler
  {
  public:
    FileH5Handler() = delete;
    FileH5Handler(std::string field, FileH5& fileh5);
    FileH5Handler(FileH5Handler const&) = delete;
    FileH5Handler& operator=(FileH5Handler const&) = delete;
    FileH5Handler(FileH5Handler&&) = default;
    FileH5Handler& operator=(FileH5Handler&&) = default;
    ~FileH5Handler() = default;

    bool defined();
    std::string type();
    bool extensible();

    template <class data_t> void read(data_t& data);
    template <class data_t> void read(std::vector<data_t>& data);
    template <class data_t> void operator<<(data_t const& data);
    template <class data_t> void operator=(data_t const& data);

    std::string attribute(std::string attribute_name);
    bool has_attribute(std::string attribute_name);
    void set_attribute(std::string attribute_name,
		       std::string attribute_value);
  private:
    std::string field_;
    FileH5* fileh5_; 
  };
}

#endif

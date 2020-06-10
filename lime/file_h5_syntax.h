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

#ifndef LIME_FILE_H5_SYNTAX_H
#define LIME_FILE_H5_SYNTAX_H

#include <string>
#include <vector>
#include <map>
#include <hdf5.h>

#include <lime/hdf5/file_h5.h>

namespace lime
{
class FileH5SyntaxHandler
  {
  public:
    FileH5SyntaxHandler() = delete;
    FileH5SyntaxHandler(std::string field, FileH5& fileh5);
    FileH5SyntaxHandler(FileH5SyntaxHandler const&) = delete;
    FileH5SyntaxHandler& operator=(FileH5SyntaxHandler const&) = delete;
    FileH5SyntaxHandler(FileH5SyntaxHandler&&) = default;
    FileH5SyntaxHandler& operator=(FileH5SyntaxHandler&&) = default;
    ~FileH5SyntaxHandler() = default;

    template <class data_t>
    FileH5SyntaxHandler& operator<<(data_t const& data);
    template <class data_t>
    FileH5SyntaxHandler& operator=(data_t const& data);
    
  private:
    const std::string field_;
    FileH5& fileh5_; 
  };
}

#endif

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

#ifndef LIME_FILE_H5_H
#define LIME_FILE_H5_H

#include <hdf5.h>
#include <map>
#include <string>
#include <vector>

#include <lime/file_h5_handler.h>
#include <lime/hdf5/parse_file.h>

namespace lime {

class FileH5Handler;
class FileH5 {
public:
  FileH5() = default;
  operator bool() const; // returns whether default constructed

  FileH5(std::string filename, std::string iomode = "r");
  ~FileH5() = default;

  FileH5(FileH5 const &other) = delete;            // FileH5 can't be copied
  FileH5 &operator=(FileH5 const &other) = delete; // FileH5 can't be copied

  FileH5(FileH5 &&other) = default;
  FileH5 &operator=(FileH5 &&other) = default;

  inline std::string filename() const { return filename_; }
  inline std::string iomode() const { return iomode_; }
  inline std::vector<std::string> fields() const { return fields_; }

  bool defined(std::string field) const;
  std::string type(std::string field) const;
  bool extensible(std::string field) const;

  template <class data_t> void read(std::string field, data_t &data) const;

  template <class data_t>
  void read(std::string field, std::vector<data_t> &data) const;

  template <class data_t>
  void write(std::string field, data_t const &data, bool force = false);

  template <class data_t> void append(std::string field, data_t const &data);

  std::string attribute(std::string field, std::string attribute_name) const;
  bool has_attribute(std::string field, std::string attribute_name);
  void set_attribute(std::string field, std::string attribute_name,
                     std::string attribute_value);

  FileH5Handler operator[](std::string const &field) {
    return FileH5Handler(field, *this);
  }

  FileH5Handler operator[](const char *field) {
    return operator[](std::string(field));
  }

  void close();

  friend herr_t lime::hdf5::parse_file(hid_t loc_id, const char *name,
                                       const H5O_info_t *info, void *fileh5);

private:
  std::string filename_;
  std::string iomode_;
  std::vector<std::string> fields_;
  std::map<std::string, std::string> field_types_;
  std::map<std::string, bool> field_extensible_;

  hid_t file_id_;
};

} // namespace lime

#endif

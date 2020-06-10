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

#include <string>
#include <vector>
#include <map>
#include <hdf5.h>

#include <lime/hdf5/file_h5.h>

namespace lime
{
  FileH5SyntaxHandler::FileH5SyntaxHandler(std::string field,
					   FileH5& fileh5)
    : field_(field), fileh5_(fileh5)
  {}

  template <class data_t>
  FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<(data_t const& data);
  { fileh5_.append(field_, data); }

  template <class data_t>
  FileH5SyntaxHandler& FileH5SyntaxHandler::operator=(data_t const& data);
  { fileh5_.write(field_, data); }

  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (int const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (unsigned const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (float const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (double const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (scomplex const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (complex const&);

  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Vector<float> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Vector<double> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Vector<scomplex> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Vector<complex> const&);

  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Matrix<float> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Matrix<double> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Matrix<scomplex> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator<<
  (lila::Matrix<complex> const&);

  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (int const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (unsigned const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (float const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (double const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (scomplex const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (complex const&);

  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Vector<float> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Vector<double> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Vector<scomplex> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Vector<complex> const&);

  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Matrix<float> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Matrix<double> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Matrix<scomplex> const&);
  template FileH5SyntaxHandler& FileH5SyntaxHandler::operator=
  (lila::Matrix<complex> const&);

}

#endif

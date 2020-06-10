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

#ifndef LIME_ALL_H
#define LIME_ALL_H

#include <hdf5.h>

#include "file_h5.h"
#include "file_h5_syntax.h"
#include "type_string.h"
#include "measurements.h"

#include "hdf5/utils.h"
#include "hdf5/types.h"
#include "hdf5/parse_file.h"

#include "hdf5/create_static_field.h"
#include "hdf5/create_extensible_field.h"

#include "hdf5/read_static_field.h"
#include "hdf5/read_static_compatible.h"

#include "hdf5/write_static_field.h"
#include "hdf5/write_compatible.h"

#include "hdf5/append_compatible.h"
#include "hdf5/append_extensible_field.h"

#include "estimator.h"
#include "timeseries.h"
#include "timeseries_io_h5.h"
#include "timeseries_io_h5_lila.h"
#include "measurements_h5.h"

#endif

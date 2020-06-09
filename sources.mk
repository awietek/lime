sources+= lime/file_h5.cpp
sources+= lime/hdf5/utils.cpp
sources+= lime/hdf5/parse_file.cpp
sources+= lime/hdf5/field_type_string.cpp

sources+= lime/hdf5/create_static_field.cpp
sources+= lime/hdf5/read_static_compatible.cpp
sources+= lime/hdf5/read_static_field.cpp
sources+= lime/hdf5/write_compatible.cpp
sources+= lime/hdf5/write_static_field.cpp

sources+= lime/hdf5/create_extensible_field.cpp
sources+= lime/hdf5/read_extensible_compatible.cpp
sources+= lime/hdf5/read_extensible_field.cpp
sources+= lime/hdf5/append_compatible.cpp
sources+= lime/hdf5/append_extensible_field.cpp

xsources+= lime/arithmetics.cpp
xsources+= lime/measurements_h5.cpp
xsources+= lime/estimator.cpp
xsources+= lime/print.cpp
xsources+= lime/timeseries.cpp
xsources+= lime/timeseries_io_h5.cpp
xsources+= lime/timeseries_io_h5_lila.cpp
xsources+= lime/detail/h5_dumper_detail.cpp
xsources+= lime/detail/h5_io_detail.cpp
xsources+= lime/detail/h5_io_detail_lila.cpp



testsources+= test/tests.cpp
testsources+= test/test_file_h5.cpp
testsources+= test/test_file_h5_rdwr.cpp
testsources+= test/test_file_h5_append.cpp
testsources+= test/test_file_h5_attribute.cpp


xtestsources+= test/test_estimator.cpp
xtestsources+= test/test_measurements_h5.cpp

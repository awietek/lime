sources+= lime/file_h5.cpp
sources+= lime/file_h5_handler.cpp
sources+= lime/measurements.cpp
sources+= lime/measurement_handler.cpp
sources+= lime/filesystem.cpp

sources+= lime/hdf5/utils.cpp
sources+= lime/hdf5/parse_file.cpp
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

testsources+= test/tests.cpp
testsources+= test/test_file_h5.cpp
testsources+= test/test_file_h5_rdwr.cpp
testsources+= test/test_file_h5_append.cpp
testsources+= test/test_file_h5_attribute.cpp
testsources+= test/test_measurements.cpp

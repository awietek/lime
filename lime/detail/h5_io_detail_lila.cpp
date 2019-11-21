#include <map>
#include <complex>
#include <hdf5.h>

#include "h5_io_detail_lila.h"

#include <lime/detail/h5_types.h>
#include <lime/detail/h5_dumper_detail.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    void writeh5_timeseries_of_vectors
    (Timeseries<lila::Vector<coeff_t>> const& timeseries, 
     std::string filename, std::string tag)
    {
      // Check whether timeseries is well-formed
      assert(timeseries.size() > 0);
      hsize_t vec_length = timeseries[0].size();
      for (hsize_t i=0; i<timeseries.size(); ++i)
	assert((hsize_t)timeseries[i].size()==vec_length);
      
      hid_t file_id = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
      assert(file_id > -1);
      
      std::map<std::string, hid_t> dataspace_ids;
      std::map<std::string, hid_t> dataset_ids; 
      std::map<std::string, hid_t> dataset_types;
      int previous_dump = 0;
      dump_to_hdf5_file(timeseries, file_id, dataspace_ids, dataset_ids, dataset_types, tag, previous_dump);
      
      herr_t status = H5Sclose(dataspace_ids[tag]);
      status = H5Dclose(dataset_ids[tag]);
      status = H5Fclose(file_id);
      assert(status > -1);
    }

    template <class coeff_t>
    Timeseries<lila::Vector<coeff_t>> 
    readh5_timeseries_of_vectors(std::string filename, std::string tag)
    {
      hid_t file = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file > -1);
      hid_t dset = H5Dopen(file, tag.c_str(), H5P_DEFAULT);
      assert(dset > -1);
      hid_t space = H5Dget_space (dset);
      assert(space > -1);

      hid_t ndims = H5Sget_simple_extent_ndims(space);
      assert(ndims == 2);
      hsize_t dims[2];
      H5Sget_simple_extent_dims (space, dims, NULL);
      
      std::vector<coeff_t> array(dims[0]*dims[1], 0);
      herr_t status = H5Dread(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL, H5P_DEFAULT,
			      array.data());
      assert(status > -1);
      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);

      // Assemble time-series
      Timeseries<lila::Vector<coeff_t>> timeseries;
      for (hsize_t i=0; i<dims[0]; ++i)
	{
	  lila::Vector<coeff_t> vec(dims[1]);
	  std::copy(array.begin() + i*dims[1], array.begin() + (i+1)*dims[1], vec.begin());
	  timeseries << vec;
	}
      return timeseries;
    }



    template <class coeff_t>
    void writeh5_timeseries_of_matrices
    (Timeseries<lila::Matrix<coeff_t>> const& timeseries, 
     std::string filename, std::string tag)
    {
      // Check whether timeseries is well-formed
      hsize_t nrows = (hsize_t)timeseries[0].nrows();
      hsize_t ncols = (hsize_t)timeseries[0].ncols();
      for (hsize_t i=0; i<(hsize_t)timeseries.size(); ++i)
	{
	  assert((hsize_t)timeseries[i].nrows()==nrows);
	  assert((hsize_t)timeseries[i].ncols()==ncols);
 	}
      
      hid_t file_id = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
      assert(file_id > -1);
      
      std::map<std::string, hid_t> dataspace_ids;
      std::map<std::string, hid_t> dataset_ids; 
      std::map<std::string, hid_t> dataset_types;
      int previous_dump = 0;
      dump_to_hdf5_file(timeseries, file_id, dataspace_ids, dataset_ids, dataset_types, tag, previous_dump);
      
      herr_t status = H5Sclose(dataspace_ids[tag]);
      status = H5Dclose(dataset_ids[tag]);
      status = H5Fclose(file_id);
      assert(status > -1);
    }



    template <class coeff_t>
    Timeseries<lila::Matrix<coeff_t>> 
    readh5_timeseries_of_matrices(std::string filename, std::string tag)
    {
      hid_t file = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file > -1);
      hid_t dset = H5Dopen(file, tag.c_str(), H5P_DEFAULT);
      assert(dset > -1);
      hid_t space = H5Dget_space (dset);
      assert(space > -1);

      hid_t ndims = H5Sget_simple_extent_ndims(space);
      assert(ndims == 3);
      hsize_t dims[3];
      H5Sget_simple_extent_dims (space, dims, NULL);
      
      std::vector<coeff_t> array(dims[0]*dims[1]*dims[2], 0);
      herr_t status = H5Dread(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL, H5P_DEFAULT,
			      array.data());
      assert(status > -1);
      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);

      // Assemble time-series
      Timeseries<lila::Matrix<coeff_t>> timeseries;
      for (hsize_t i=0; i<dims[0]; ++i)
	{
	  lila::Matrix<coeff_t> vec(dims[1], dims[2]);
	  std::copy(array.begin() + i*dims[1]*dims[2], 
		    array.begin() + (i+1)*dims[1]*dims[2], vec.begin());
	  timeseries << vec;
	}
      return timeseries;
    }

    template 
    void writeh5_timeseries_of_vectors<float>
    (Timeseries<lila::Vector<float>> const& timeseries, 
     std::string filename, std::string tag);
    template
    void writeh5_timeseries_of_vectors<double>
    (Timeseries<lila::Vector<double>> const& timeseries, 
     std::string filename, std::string tag);
    template
    void writeh5_timeseries_of_vectors<std::complex<float>>
    (Timeseries<lila::Vector<std::complex<float>>> const& timeseries, 
     std::string filename, std::string tag);
    template
    void writeh5_timeseries_of_vectors<std::complex<double>>
    (Timeseries<lila::Vector<std::complex<double>>> const& timeseries, 
     std::string filename, std::string tag);

    template
    Timeseries<lila::Vector<float>> 
    readh5_timeseries_of_vectors<float>
    (std::string filename, std::string tag);
    template
    Timeseries<lila::Vector<double>> 
    readh5_timeseries_of_vectors<double>
    (std::string filename, std::string tag);
    template
    Timeseries<lila::Vector<std::complex<float>>> 
    readh5_timeseries_of_vectors<std::complex<float>>
    (std::string filename, std::string tag);
    template
    Timeseries<lila::Vector<std::complex<double>>> 
    readh5_timeseries_of_vectors<std::complex<double>>
    (std::string filename, std::string tag);

    template 
    void writeh5_timeseries_of_matrices<float>
    (Timeseries<lila::Matrix<float>> const& timeseries, 
     std::string filename, std::string tag);
    template
    void writeh5_timeseries_of_matrices<double>
    (Timeseries<lila::Matrix<double>> const& timeseries, 
     std::string filename, std::string tag);
    template
    void writeh5_timeseries_of_matrices<std::complex<float>>
    (Timeseries<lila::Matrix<std::complex<float>>> const& timeseries, 
     std::string filename, std::string tag);
    template
    void writeh5_timeseries_of_matrices<std::complex<double>>
    (Timeseries<lila::Matrix<std::complex<double>>> const& timeseries, 
     std::string filename, std::string tag);

    template
    Timeseries<lila::Matrix<float>> 
    readh5_timeseries_of_matrices<float>
    (std::string filename, std::string tag);
    template
    Timeseries<lila::Matrix<double>> 
    readh5_timeseries_of_matrices<double>
    (std::string filename, std::string tag);
    template
    Timeseries<lila::Matrix<std::complex<float>>> 
    readh5_timeseries_of_matrices<std::complex<float>>
    (std::string filename, std::string tag);
    template
    Timeseries<lila::Matrix<std::complex<double>>> 
    readh5_timeseries_of_matrices<std::complex<double>>
    (std::string filename, std::string tag);

  }  // namespace detail
}

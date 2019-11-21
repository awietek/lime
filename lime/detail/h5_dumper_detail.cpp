#include <complex>

#include "h5_dumper_detail.h"

#include <lime/detail/h5_types.h>
#include <lime/detail/h5_utils.h>

#ifndef LIME_H5_CHUNKSIZE
#define LIME_H5_CHUNKSIZE 1
#endif

namespace lime
{
  namespace detail
  {
   
    hid_t h5_create_timeseries_dataspace_scalar()
    {
      int rank = 1;
      hsize_t dims[1]  = {0};           /* dataset dimensions at creation time */		
      hsize_t maxdims[1] = {H5S_UNLIMITED};
      hid_t dataspace_id = H5Screate_simple(rank, dims, maxdims); 
      assert(dataspace_id > -1);
      return dataspace_id;
    }

    hid_t h5_timeseries_chunks_scalar()    
    {
      int rank = 1;
      hsize_t chunk_dims[1] = {LIME_H5_CHUNKSIZE};
      hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
      herr_t status = H5Pset_chunk(prop, rank, chunk_dims);
      assert(status > -1);
      // status = H5Pset_deflate(prop, 8);
      // assert(status > -1);
      return prop;
    }

    template <class coeff_t>
    hid_t h5_create_timeseries_dataset_scalar
    (hid_t file_id, hid_t dataspace_id, std::string tag)
    {
      hid_t datatype = hdf5_datatype<coeff_t>();
      hid_t chunk_prop = h5_timeseries_chunks_scalar();
      hid_t dataset_id = H5Dcreate2(file_id, tag.c_str(), datatype, dataspace_id, 
				    H5P_DEFAULT, chunk_prop, H5P_DEFAULT);
      assert(dataset_id > -1);
      return dataset_id;
    }


    template <class coeff_t>
    void dump_to_hdf5_file_scalar(Timeseries<coeff_t> const& timeseries, hid_t file_id, 
				  std::map<std::string, hid_t>& dataspace_ids,
				  std::map<std::string, hid_t>& dataset_ids, 
				  std::map<std::string, hid_t>& dataset_types, 
				  std::string tag, int& previous_dump)
    {
      // if (previous_dump == 0)
      // 	{
      // 	  dataspace_ids[tag] = 
      // 	    h5_create_timeseries_dataspace_scalar();
      // 	  dataset_ids[tag] = h5_create_timeseries_dataset_scalar<coeff_t>
      // 	    (file_id, dataspace_ids[tag], tag);
      // 	  dataset_types[tag] = H5Dget_type(dataset_ids[tag]);
      // 	}

      // Determine current and new shape of dataspace
      int chunk_size = timeseries.size() - previous_dump;
      std::vector<hsize_t> shape = h5_get_shape(dataspace_ids[tag]);
      std::vector<hsize_t> newshape = shape;
      newshape[0] += chunk_size;
      std::vector<hsize_t> diffshape = newshape;
      for (int i=0; i<(int)diffshape.size(); ++i)
	diffshape[i] -= shape[i];
      std::vector<hsize_t> offset = shape;

      // Make dataset larger
      herr_t status = H5Dset_extent(dataset_ids[tag], newshape.data());
      assert(status > -1); 

      hid_t filespace = H5Dget_space(dataset_ids[tag]);
      status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset.data(), 
				   NULL, diffshape.data(), NULL);  
      assert(status > -1);
      
      hid_t memspace = H5Screate_simple(diffshape.size(), diffshape.data(), NULL);
      assert(memspace > -1);

      // Assemble data and write
      auto data = timeseries.data() + shape[0];
      status = H5Dwrite(dataset_ids[tag], dataset_types[tag], memspace, 
			filespace, H5P_DEFAULT, data);
      assert(status > -1);
      H5Sclose(memspace);
      H5Sclose(dataspace_ids[tag]);
      dataspace_ids[tag] = filespace;
      previous_dump = timeseries.size();
    }



    template
    hid_t h5_create_timeseries_dataset_scalar<float>
    (hid_t file_id, hid_t dataspace_id, std::string tag);
    template
    hid_t h5_create_timeseries_dataset_scalar<double>
    (hid_t file_id, hid_t dataspace_id, std::string tag);
    template
    hid_t h5_create_timeseries_dataset_scalar<std::complex<float>>
    (hid_t file_id, hid_t dataspace_id, std::string tag);
    template
    hid_t h5_create_timeseries_dataset_scalar<std::complex<double>>
    (hid_t file_id, hid_t dataspace_id, std::string tag);

    template 
    void dump_to_hdf5_file_scalar<float>
    (Timeseries<float> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template 
    void dump_to_hdf5_file_scalar<double>
    (Timeseries<double> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template 
    void dump_to_hdf5_file_scalar<std::complex<float>>
    (Timeseries<std::complex<float>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template 
    void dump_to_hdf5_file_scalar<std::complex<double>>
    (Timeseries<std::complex<double>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);




 
    void dump_to_hdf5_file
    (Timeseries<float> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_scalar<float>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<double> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_scalar<double>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<std::complex<float>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_scalar<std::complex<float>>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<std::complex<double>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_scalar<std::complex<double>>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 




    hid_t h5_create_timeseries_dataspace_vector(hsize_t n)    
    {
      int rank = 2;
      hsize_t dims[2]  = {0, n};           /* dataset dimensions at creation time */		
      hsize_t maxdims[2] = {H5S_UNLIMITED, n};
      hid_t dataspace_id = H5Screate_simple(rank, dims, maxdims); 
      assert(dataspace_id > -1);
      return dataspace_id;
    }

    hid_t h5_create_timeseries_dataspace_matrix(hsize_t m, hsize_t n)    
    {
      int rank = 3;
      hsize_t dims[3]  = {0, m, n};           /* dataset dimensions at creation time */		
      hsize_t maxdims[3] = {H5S_UNLIMITED, m, n};
      hid_t dataspace_id = H5Screate_simple(rank, dims, maxdims); 
      assert(dataspace_id > -1);
      return dataspace_id;
    }

    hid_t h5_timeseries_chunks_vector(hsize_t n)    
    {
      int rank = 2;
      hsize_t chunksize = 1;
      hsize_t chunk_dims[2] = {chunksize, n};
      hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
      herr_t status = H5Pset_chunk(prop, rank, chunk_dims);
      assert(status > -1);
      return prop;
    }

    hid_t h5_timeseries_chunks_matrix(hsize_t m, hsize_t n)    
    {
      int rank = 3;
      hsize_t chunksize = 1;
      hsize_t chunk_dims[3] = {chunksize, m, n};
      hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
      herr_t status = H5Pset_chunk(prop, rank, chunk_dims);
      assert(status > -1);
      return prop;
    }

    template <class coeff_t>
    hid_t h5_create_timeseries_dataset_vector
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t n)
    {
      hid_t datatype = hdf5_datatype<coeff_t>();
      hid_t chunk_prop = h5_timeseries_chunks_vector(n);
      hid_t dataset_id = H5Dcreate2(file_id, tag.c_str(), datatype, dataspace_id, 
				    H5P_DEFAULT, chunk_prop, H5P_DEFAULT);
      assert(dataset_id > -1);
      return dataset_id;
    }


    template <class coeff_t>
    hid_t h5_create_timeseries_dataset_matrix
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t m, hsize_t n)
    {
      hid_t datatype = hdf5_datatype<coeff_t>();
      hid_t chunk_prop = h5_timeseries_chunks_matrix(m, n);
      hid_t dataset_id = H5Dcreate2(file_id, tag.c_str(), datatype, dataspace_id, 
				    H5P_DEFAULT, chunk_prop, H5P_DEFAULT);
      assert(dataset_id > -1);
      return dataset_id;
    }

    template <class coeff_t>
    void dump_to_hdf5_file_vector(Timeseries<lila::Vector<coeff_t>> const& timeseries, 
				  hid_t file_id, 
				  std::map<std::string, hid_t>& dataspace_ids,
				  std::map<std::string, hid_t>& dataset_ids, 
				  std::map<std::string, hid_t>& dataset_types, 
				  std::string tag, int& previous_dump)
    {
      if (timeseries.size() == 0) return;

      // Check whether timeseries is well-formed
      hsize_t size = (hsize_t)timeseries[0].size();
      for (hsize_t i=0; i<(hsize_t)timeseries.size(); ++i)
	assert((hsize_t)timeseries[i].size()==size);
 
      // if (previous_dump == 0)
      // 	{
      // 	  dataspace_ids[tag] = h5_create_timeseries_dataspace_vector(size);
      // 	  dataset_ids[tag] = 
      // 	    h5_create_timeseries_dataset_vector<coeff_t>(file_id, dataspace_ids[tag],
      // 							 tag, size);
      // 	  dataset_types[tag] = H5Dget_type(dataset_ids[tag]);
      // 	}

      long ndata = timeseries.size() - previous_dump;

      // Write new data layer-by-layer
      for (long layer=0; layer<ndata; ++layer)
	{
	  int chunk_size = 1;
	  std::vector<hsize_t> shape = h5_get_shape(dataspace_ids[tag]);

	  std::vector<hsize_t> newshape = shape;
	  newshape[0] += chunk_size;
	  std::vector<hsize_t> diffshape = newshape;
	  diffshape[0] -= shape[0];
	  std::vector<hsize_t> offset = shape;
	  offset[1] = 0;

	  // Make dataset larger
	  herr_t status = H5Dset_extent(dataset_ids[tag], newshape.data());
	  assert(status > -1); 
	  hid_t filespace = H5Dget_space(dataset_ids[tag]);
	  assert(filespace > -1);
	  
	  status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset.data(), 
				       NULL, diffshape.data(), NULL);  
	  assert(status > -1);
	  hid_t memspace = H5Screate_simple(diffshape.size(), diffshape.data(), NULL);
	  assert(memspace > -1);

	  // Assemble data and write
	  long idx = previous_dump + layer;
	  const coeff_t* data = timeseries[idx].data();

	  status = H5Dwrite(dataset_ids[tag], dataset_types[tag], memspace, 
			    filespace, H5P_DEFAULT, data);
	  assert(status > -1);
	  H5Sclose(memspace);
	  dataspace_ids[tag] = H5Dget_space(dataset_ids[tag]);
	}
      previous_dump = timeseries.size();
    }


    template <class coeff_t>
    void dump_to_hdf5_file_matrix(Timeseries<lila::Matrix<coeff_t>> const& timeseries, 
				  hid_t file_id, 
				  std::map<std::string, hid_t>& dataspace_ids,
				  std::map<std::string, hid_t>& dataset_ids, 
				  std::map<std::string, hid_t>& dataset_types, 
				  std::string tag, int& previous_dump)
    {
      if (timeseries.size() == 0) return;

      // Check whether timeseries is well-formed
      hsize_t nrows = (hsize_t)timeseries[0].nrows();
      hsize_t ncols = (hsize_t)timeseries[0].ncols();
      for (hsize_t i=0; i<(hsize_t)timeseries.size(); ++i)
	{
	  assert((hsize_t)timeseries[i].nrows()==nrows);
	  assert((hsize_t)timeseries[i].ncols()==ncols);
 	}

      // if (previous_dump == 0)
      // 	{
      // 	  dataspace_ids[tag] = h5_create_timeseries_dataspace_matrix(nrows, ncols);
      // 	  dataset_ids[tag] = 
      // 	    h5_create_timeseries_dataset_matrix<coeff_t>(file_id, dataspace_ids[tag],
      // 							 tag, nrows, ncols);
      // 	  dataset_types[tag] = H5Dget_type(dataset_ids[tag]);
      // 	}

      long ndata = timeseries.size() - previous_dump;

      // Write new data layer-by-layer
      for (long layer=0; layer<ndata; ++layer)
	{
	  int chunk_size = 1;
	  std::vector<hsize_t> shape = h5_get_shape(dataspace_ids[tag]);

	  std::vector<hsize_t> newshape = shape;
	  newshape[0] += chunk_size;
	  std::vector<hsize_t> diffshape = newshape;
	  diffshape[0] -= shape[0];
	  std::vector<hsize_t> offset = shape;
	  offset[1] = 0;
	  offset[2] = 0;

	  // Make dataset larger
	  herr_t status = H5Dset_extent(dataset_ids[tag], newshape.data());
	  assert(status > -1); 
	  hid_t filespace = H5Dget_space(dataset_ids[tag]);
	  assert(filespace > -1);
	  
	  status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset.data(), 
				       NULL, diffshape.data(), NULL);  
	  assert(status > -1);
	  hid_t memspace = H5Screate_simple(diffshape.size(), diffshape.data(), NULL);
	  assert(memspace > -1);

	  // Assemble data and write
	  long idx = previous_dump + layer;

	  // lila uses Fortan order internallu, hdf5 uses C order
	  auto tm = lila::Transpose(timeseries[idx]);
	  const coeff_t* data = tm.data(); 

	  status = H5Dwrite(dataset_ids[tag], dataset_types[tag], memspace, 
			    filespace, H5P_DEFAULT, data);
	  assert(status > -1);
	  H5Sclose(memspace);
	  dataspace_ids[tag] = H5Dget_space(dataset_ids[tag]);
	}
      previous_dump = timeseries.size();
    }




    template 
    hid_t h5_create_timeseries_dataset_vector<float>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t n);
    template 
    hid_t h5_create_timeseries_dataset_vector<double>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t n);
    template 
    hid_t h5_create_timeseries_dataset_vector<std::complex<float>>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t n);
    template 
    hid_t h5_create_timeseries_dataset_vector<std::complex<double>>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t n);
 
    template
    hid_t h5_create_timeseries_dataset_matrix<float>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t m, hsize_t n);   
    template
    hid_t h5_create_timeseries_dataset_matrix<double>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t m, hsize_t n);   
    template
    hid_t h5_create_timeseries_dataset_matrix<std::complex<float>>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t m, hsize_t n);   
    template
    hid_t h5_create_timeseries_dataset_matrix<std::complex<double>>
    (hid_t file_id, hid_t dataspace_id, std::string tag, hsize_t m, hsize_t n);   


    template
    void dump_to_hdf5_file_vector<float>
    (Timeseries<lila::Vector<float>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template
    void dump_to_hdf5_file_vector<double>
    (Timeseries<lila::Vector<double>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template
    void dump_to_hdf5_file_vector<std::complex<float>>
    (Timeseries<lila::Vector<std::complex<float>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template
    void dump_to_hdf5_file_vector<std::complex<double>>
    (Timeseries<lila::Vector<std::complex<double>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);


    template
    void dump_to_hdf5_file_matrix<float>
    (Timeseries<lila::Matrix<float>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template
    void dump_to_hdf5_file_matrix<double>
    (Timeseries<lila::Matrix<double>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template
    void dump_to_hdf5_file_matrix<std::complex<float>>
    (Timeseries<lila::Matrix<std::complex<float>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);
    template
    void dump_to_hdf5_file_matrix<std::complex<double>>
    (Timeseries<lila::Matrix<std::complex<double>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump);


    void dump_to_hdf5_file
    (Timeseries<lila::Vector<float>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_vector<float>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<lila::Vector<double>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_vector<double>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<lila::Vector<std::complex<float>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_vector<std::complex<float>>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<lila::Vector<std::complex<double>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_vector<std::complex<double>>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 





    void dump_to_hdf5_file
    (Timeseries<lila::Matrix<float>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_matrix<float>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<lila::Matrix<double>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_matrix<double>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<lila::Matrix<std::complex<float>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_matrix<std::complex<float>>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 
    void dump_to_hdf5_file
    (Timeseries<lila::Matrix<std::complex<double>>> const& timeseries, hid_t file_id, 
     std::map<std::string, hid_t>& dataspace_ids,
     std::map<std::string, hid_t>& dataset_ids, 
     std::map<std::string, hid_t>& dataset_types, 
     std::string tag, int& previous_dump)
    {
      dump_to_hdf5_file_matrix<std::complex<double>>
	(timeseries, file_id, dataspace_ids, 
	 dataset_ids, dataset_types, tag, previous_dump);
    } 


  }  // namespace detail

}

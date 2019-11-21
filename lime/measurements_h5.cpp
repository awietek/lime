#include <cstdlib>

#include "measurements_h5.h"

#include <lime/detail/h5_dumper_detail.h>

#include <hdf5.h>

namespace lime
{
  
  template <class coeff_t>
  MeasurementsH5Tpl<coeff_t>::MeasurementsH5Tpl(std::string filename)
    : filename_(filename)
  {
    file_id_ = H5Fcreate(filename_.c_str(), H5F_ACC_TRUNC, 
			 H5P_DEFAULT, H5P_DEFAULT);
  }

  template <class coeff_t>
  MeasurementsH5Tpl<coeff_t>::~MeasurementsH5Tpl()
  {
    herr_t status;
    for (auto id : dataspace_of_quantity_)
      {
	status = H5Sclose(id.second);
	assert(status > -1);
      }

    for (auto id : dataset_of_quantity_)
      {
	status = H5Dclose(id.second);
	assert(status > -1);
      }

    status = H5Fclose(file_id_);
    assert(status > -1);
  }

  namespace detail
  {
    std::string type_to_string(Type type)
    {
      std::string type_string;
      switch (type)
	{
	case(scalar):
	  type_string = "real scalar";
	  break;
	case(cscalar):
	  type_string = "complex scalar";
	  break;
	case(vector):
	  type_string = "real vector";
	  break;
	case(cvector):
	  type_string = "complex vector";
	  break;	
	case(matrix):
	  type_string = "real matrix";
	  break;
	case(cmatrix):
	  type_string = "complex matrix";
	  break;
	}
      return type_string;
    }


    void wrong_measurement_format_error(Type add_type, int add_m, int add_n,
					Type def_type, int def_m, int def_n)
    {
      auto add_type_str = type_to_string(add_type);
      auto def_type_str = type_to_string(def_type);
      std::cerr << "Lime Error: cannot add measurement of type/dim "
		<<"(" << add_type_str << "," << add_m << "," << add_n << ") " 
		<< "to container of type/dim " 
		<<"(" << def_type_str << "," << def_m << "," << def_n << ") " 
		<< "\n";
      exit(EXIT_FAILURE);
    }    

    bool operator==(IndexTypeDim const& a, IndexTypeDim const& b)
    { 
      return (a.index == b.index) && (a.type == b.type) && (a.m == b.m) 
	&& (a.n == b.n);
    }
    bool operator!=(IndexTypeDim const& a, IndexTypeDim const& b)
    { return !(a == b); }




    template <class T, class dspace_create_f,  class dset_create_f>
    inline void add_to_measurements
    (std::string quantity, T const& measurement, int m, int n, Type type,
     std::vector<std::string>& quantities,
     std::vector<Estimator<T>>& estimators,
     std::vector<Timeseries<T>>& timeseries,
     std::map<std::string, IndexTypeDim>& index_type_dim_of_quantity,
     std::map<std::string, hid_t>& dataspace_of_quantity,
     std::map<std::string, hid_t>& dataset_of_quantity,
     std::map<std::string, hid_t>& dataset_types_of_quantity,
     std::map<std::string, long>& previous_dump_of_quantity,
     dspace_create_f dspace_create, dset_create_f dset_create,
     hid_t file_id)
    {
      // Quantity not already defined
      if (std::find(quantities.begin(), quantities.end(), quantity) ==
	  quantities.end())
	{
	  quantities.push_back(quantity);

	  // Define index in vector of estimators, its type, and dimension
	  long index = estimators.size();
	  assert(timeseries.size() == index);
	  index_type_dim_of_quantity[quantity] = 
	    IndexTypeDim({index, type, m, n});

	  // Create a dataspace and dataset in the hdf5 file
	  dataspace_of_quantity[quantity] = dspace_create();
	  dataset_of_quantity[quantity] = 
	    dset_create(file_id, dataspace_of_quantity[quantity], quantity);
	  dataset_types_of_quantity[quantity] = 
	    H5Dget_type(dataset_of_quantity[quantity]);

	  // Estimator<T> estimator;
	  Timeseries<T> timeserie;
	  // estimator << measurement;
	  timeserie << measurement;
	  // estimators.push_back(estimator);
	  timeseries.push_back(timeserie);
	}

      // Quantity already defined
      else
	{
	  auto index_type_dim = index_type_dim_of_quantity[quantity];
	  auto index = index_type_dim.index;
	  
	  if (index_type_dim != IndexTypeDim{index, type, m, n})
	    wrong_measurement_format_error(type, m, n, 
					   index_type_dim.type, 
					   index_type_dim.m, 
					   index_type_dim.n);

	  // estimators[index] << measurement;
	  timeseries[index] << measurement;
	}
    }

  }
  
  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::add(std::string quantity, 
				       rtype const& measurement)
  {
    // printf("Add real scalar\n");
    int m = 0;
    int n = 0;    
    detail::add_to_measurements
      (quantity, measurement, m, n, scalar, quantities_, 
       scalar_estimators_, scalar_timeseries_, 
       index_type_dim_of_quantity_, 
       dataspace_of_quantity_, dataset_of_quantity_,
       dataset_types_of_quantity_,
       previous_dump_of_quantity_, 
       detail::h5_create_timeseries_dataspace_scalar,
       detail::h5_create_timeseries_dataset_scalar<coeff_t>, file_id_);
  }

  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::add
  (std::string quantity, ctype const& measurement)
  {
    // printf("Add complex scalar\n");
    int m = 0;
    int n = 0;
    detail::add_to_measurements
      (quantity, measurement, m, n, cscalar, quantities_, 
       cscalar_estimators_, cscalar_timeseries_, 
       index_type_dim_of_quantity_, 
       dataspace_of_quantity_, dataset_of_quantity_,
       dataset_types_of_quantity_, 
       previous_dump_of_quantity_,
       detail::h5_create_timeseries_dataspace_scalar,
       detail::h5_create_timeseries_dataset_scalar<complex::complex_t<coeff_t>>,
       file_id_);
  }

  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::add
  (std::string quantity, vec_rtype const& measurement)
  {
    // printf("Add real vector\n");
    int m = measurement.size();
    int n = 0;    
    detail::add_to_measurements
      (quantity, measurement, m, n, vector, quantities_, 
       vector_estimators_, vector_timeseries_, 
       index_type_dim_of_quantity_, 
       dataspace_of_quantity_, dataset_of_quantity_,
       dataset_types_of_quantity_, 
       previous_dump_of_quantity_,
       [m](){ return detail::h5_create_timeseries_dataspace_vector(m); },
       [m](hid_t file_id, hid_t dataspace_id, std::string tag)
       { 
	 return detail::h5_create_timeseries_dataset_vector<coeff_t>
	   (file_id, dataspace_id, tag, m);
       },
       file_id_);
  }

  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::add
  (std::string quantity, vec_ctype const& measurement)
  {
    // printf("Add complex vector\n");
    int m = measurement.size();
    int n = 0;    
    detail::add_to_measurements
      (quantity, measurement, m, n, cvector, quantities_, 
       cvector_estimators_, cvector_timeseries_, 
       index_type_dim_of_quantity_, 
       dataspace_of_quantity_, dataset_of_quantity_,
       dataset_types_of_quantity_, 
       previous_dump_of_quantity_,
       [m](){ return detail::h5_create_timeseries_dataspace_vector(m); },
       [m](hid_t file_id, hid_t dataspace_id, std::string tag)
       { 
	 return detail::h5_create_timeseries_dataset_vector<complex::complex_t<coeff_t>>
	   (file_id, dataspace_id, tag, m);
       },
       file_id_);
  }

  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::add
  (std::string quantity, mat_rtype const& measurement)
  {
    // printf("Add real matrix\n");
    int m = measurement.nrows();
    int n = measurement.ncols();
    detail::add_to_measurements
      (quantity, measurement, m, n, matrix, quantities_, 
       matrix_estimators_, matrix_timeseries_, 
       index_type_dim_of_quantity_, 
       dataspace_of_quantity_, dataset_of_quantity_,
       dataset_types_of_quantity_, 
       previous_dump_of_quantity_,
       [m,n](){ return detail::h5_create_timeseries_dataspace_matrix(m, n); },
       [m,n](hid_t file_id, hid_t dataspace_id, std::string tag)
       { 
	 return detail::h5_create_timeseries_dataset_matrix<coeff_t>
	   (file_id, dataspace_id, tag, m, n);
       },
       file_id_);
  }

  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::add
  (std::string quantity, mat_ctype const& measurement)
  {
    // printf("Add complex matrix\n");
    int m = measurement.nrows();
    int n = measurement.ncols();
    detail::add_to_measurements
      (quantity, measurement, m, n, cmatrix, quantities_, 
       cmatrix_estimators_, cmatrix_timeseries_, 
       index_type_dim_of_quantity_, 
       dataspace_of_quantity_, dataset_of_quantity_,
       dataset_types_of_quantity_, 
       previous_dump_of_quantity_,
       [m,n](){ return detail::h5_create_timeseries_dataspace_matrix(m,n); },
       [m,n](hid_t file_id, hid_t dataspace_id, std::string tag)
       { 
	 return detail::h5_create_timeseries_dataset_matrix<complex::complex_t<coeff_t>>
	   (file_id, dataspace_id, tag, m, n);
       },
       file_id_);
  }



  template <class coeff_t>
  void MeasurementsH5Tpl<coeff_t>::dump()
  {
    for (auto quantity : quantities_)
      {
	auto index_type_dim = index_type_dim_of_quantity_[quantity];
	long index = index_type_dim.index;
	Type type = index_type_dim.type;
	int previous_dump = previous_dump_of_quantity_[quantity];

	switch (type)
	{
	case(scalar):
	  detail::dump_to_hdf5_file
	    (scalar_timeseries_[index], file_id_, dataspace_of_quantity_,
	     dataset_of_quantity_, dataset_types_of_quantity_, quantity,
	     previous_dump);	    
	  break;

	case(cscalar):
	  detail::dump_to_hdf5_file
	    (cscalar_timeseries_[index], file_id_, dataspace_of_quantity_,
	     dataset_of_quantity_, dataset_types_of_quantity_, quantity,
	     previous_dump);
	  break;

	case(vector):
	  detail::dump_to_hdf5_file
	    (vector_timeseries_[index], file_id_, dataspace_of_quantity_,
	     dataset_of_quantity_, dataset_types_of_quantity_, quantity,
	     previous_dump);	  
	  break;

	case(cvector):
	  detail::dump_to_hdf5_file
	    (cvector_timeseries_[index], file_id_, dataspace_of_quantity_,
	     dataset_of_quantity_, dataset_types_of_quantity_, quantity,
	     previous_dump);
	  break;	

	case(matrix):
	  detail::dump_to_hdf5_file
	    (matrix_timeseries_[index], file_id_, dataspace_of_quantity_,
	     dataset_of_quantity_, dataset_types_of_quantity_, quantity,
	     previous_dump);
	  break;

	case(cmatrix):
	  detail::dump_to_hdf5_file
	    (cmatrix_timeseries_[index], file_id_, dataspace_of_quantity_,
	     dataset_of_quantity_, dataset_types_of_quantity_, quantity,
	     previous_dump);
	  break;
	}

	// Update previous_dump
	previous_dump_of_quantity_[quantity] = previous_dump;

      }

  }

  template class MeasurementsH5Tpl<float>;
  template class MeasurementsH5Tpl<double>;

}

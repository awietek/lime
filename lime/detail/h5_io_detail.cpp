#include <complex>

#include "h5_io_detail.h"

#include <lime/detail/h5_types.h>

namespace lime
{
  namespace detail
  {
    template <class coeff_t>
    void writeh5_array_1d(hsize_t size, coeff_t const* array, 
			  std::string filename, std::string tag)
    {
      hsize_t dims[1] = {size};

      hid_t file = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, 
			     H5P_DEFAULT, H5P_DEFAULT);
      assert(file > -1);
      hid_t space = H5Screate_simple (1, dims, NULL);
      assert(space > -1);
      hid_t dset = H5Dcreate(file, tag.c_str(), hdf5_datatype<coeff_t>(), space,
			     H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
      assert(dset > -1);
      herr_t status = H5Dwrite(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL,
			       H5P_DEFAULT, array);
      assert(status > -1);

      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);
    }

    template <class coeff_t>
    std::vector<coeff_t> readh5_array_1d(std::string filename, std::string tag)
    {
      hid_t file = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file > -1);
      hid_t dset = H5Dopen(file, tag.c_str(), H5P_DEFAULT);
      assert(dset > -1);
      hid_t space = H5Dget_space (dset);
      assert(space > -1);
      hsize_t dims[1];
      hid_t ndims = H5Sget_simple_extent_dims (space, dims, NULL);
      assert(ndims == 1);
      
      std::vector<coeff_t> array(dims[0], 0);
      herr_t status = H5Dread(dset, hdf5_datatype<coeff_t>(), H5S_ALL, H5S_ALL,
			      H5P_DEFAULT, array.data());
      assert(status > -1);

      status = H5Dclose (dset);
      assert(status > -1);
      status = H5Sclose (space);
      assert(status > -1);
      status = H5Fclose(file);
      assert(status != -1);
      return array;
    }

    
    template 
    void writeh5_array_1d<float>
    (hsize_t size, float const* array, std::string filename, std::string tag);
    template 
    void writeh5_array_1d<double>
    (hsize_t size, double const* array, std::string filename, std::string tag);
    template 
    void writeh5_array_1d<std::complex<float>>
    (hsize_t size, std::complex<float> const* array, 
     std::string filename, std::string tag);
    template 
    void writeh5_array_1d<std::complex<double>>
    (hsize_t size, std::complex<double> const* array, 
     std::string filename, std::string tag);

    template
    std::vector<float> 
    readh5_array_1d<float>(std::string filename, std::string tag);
    template
    std::vector<double> 
    readh5_array_1d<double>(std::string filename, std::string tag);
    template
    std::vector<std::complex<float>>
    readh5_array_1d<std::complex<float>>(std::string filename, std::string tag);
    template
    std::vector<std::complex<double>> 
    readh5_array_1d<std::complex<double>>(std::string filename, std::string tag);

  }  // namespace detail

}

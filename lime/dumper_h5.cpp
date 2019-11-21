#include <cassert>

#include "dumper_h5.h"

namespace lime
{

  template <class timeseries_t>
  DumperH5<timeseries_t>::DumperH5(timeseries_t& timeseries, 
				   std::string filename, std::string tag)
    : timeseries_(timeseries),
      filename_(filename),
      tag_(tag),
      previous_dump_(0)
  {
    file_id_ = H5Fcreate(filename_.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  }

  template <class timeseries_t>
  DumperH5<timeseries_t>::~DumperH5()
  { 
    herr_t status;
    for (auto id : dataspace_ids_)
      {
	status = H5Sclose(id.second);
	assert(status > -1);
      }

    for (auto id : dataset_ids_)
      {
	status = H5Dclose(id.second);
	assert(status > -1);
      }

    status = H5Fclose(file_id_);
    assert(status > -1);
  }

  template <class timeseries_t>
  void DumperH5<timeseries_t>::dump()
  { 
    detail::dump_to_hdf5_file
      (timeseries_, file_id_, dataspace_ids_, dataset_ids_, dataset_types_,
       tag_, previous_dump_); 
  }

  template class DumperH5<Timeseries<float>>;
  template class DumperH5<Timeseries<double>>;
  template class DumperH5<Timeseries<std::complex<float>>>;
  template class DumperH5<Timeseries<std::complex<double>>>;

  template class DumperH5<Timeseries<lila::Vector<float>>>;
  template class DumperH5<Timeseries<lila::Vector<double>>>;
  template class DumperH5<Timeseries<lila::Vector<std::complex<float>>>>;
  template class DumperH5<Timeseries<lila::Vector<std::complex<double>>>>;

  template class DumperH5<Timeseries<lila::Matrix<float>>>;
  template class DumperH5<Timeseries<lila::Matrix<double>>>;
  template class DumperH5<Timeseries<lila::Matrix<std::complex<float>>>>;
  template class DumperH5<Timeseries<lila::Matrix<std::complex<double>>>>;

}

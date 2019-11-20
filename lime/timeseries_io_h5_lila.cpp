#include "timeseries_io_h5_lila.h"

#include <lime/timeseries_io_h5.h>
#include <lime/detail/h5_io_detail_lila.h>

namespace lime
{

  void writeh5
  (const Timeseries<lila::Vector<float>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<float>(timeseries, filename, tag);
  }

  void writeh5
  (const Timeseries<lila::Vector<double>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<double>(timeseries, filename, tag);
  }

  void writeh5
  (const Timeseries<lila::Vector<std::complex<float>>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<std::complex<float>>
      (timeseries, filename, tag);
  }

  void writeh5
  (const Timeseries<lila::Vector<std::complex<double>>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_vectors<std::complex<double>>
      (timeseries, filename, tag);
  }

 
  template <>
  Timeseries<lila::Vector<float>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_vectors<float>(filename, tag); 
  }
  
  template <>
  Timeseries<lila::Vector<double>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_vectors<double>(filename, tag); 
  }

  template <>
  Timeseries<lila::Vector<std::complex<float>>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_vectors<std::complex<float>>
      (filename, tag); 
  }

  template <>
  Timeseries<lila::Vector<std::complex<double>>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_vectors<std::complex<double>>
      (filename, tag); 
  }
 


  void writeh5
  (const Timeseries<lila::Matrix<float>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_matrices<float>(timeseries, filename, tag);
  }

  void writeh5
  (const Timeseries<lila::Matrix<double>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_matrices<double>(timeseries, filename, tag);
  }

  void writeh5
  (const Timeseries<lila::Matrix<std::complex<float>>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_matrices<std::complex<float>>
      (timeseries, filename, tag);
  }

  void writeh5
  (const Timeseries<lila::Matrix<std::complex<double>>>& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_timeseries_of_matrices<std::complex<double>>
      (timeseries, filename, tag);
  }


  template <>
  Timeseries<lila::Matrix<float>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_matrices<float>(filename, tag); 
  }
  
  template <>
  Timeseries<lila::Matrix<double>> readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_matrices<double>(filename, tag); 
  }
  
  template <>
  Timeseries<lila::Matrix<std::complex<float>>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_matrices<std::complex<float>>
      (filename, tag); 
  }

  template <>
  Timeseries<lila::Matrix<std::complex<double>>> 
  readh5(std::string filename, std::string tag)
  { 
    return detail::readh5_timeseries_of_matrices<std::complex<double>>
      (filename, tag); 
  }
 
}

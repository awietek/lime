#include "timeseries_io_h5.h"

#include <lime/detail/h5_io_detail.h>

namespace lime
{

  void writeh5
  (Timeseries<float> const& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_array_1d<float>(timeseries.size(), timeseries.data(), 
				    filename, tag);
  }

  void writeh5
  (Timeseries<double> const& timeseries,
   std::string filename, std::string tag)
  { 
    detail::writeh5_array_1d<double>(timeseries.size(), timeseries.data(), 
				     filename, tag);
  }

  void writeh5
  (Timeseries<std::complex<float>> const& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_array_1d<std::complex<float>>(timeseries.size(), 
						  timeseries.data(), 
						  filename, tag);
  }

  void writeh5
  (Timeseries<std::complex<double>> const& timeseries, 
   std::string filename, std::string tag)
  { 
    detail::writeh5_array_1d<std::complex<double>>(timeseries.size(), 
						   timeseries.data(), 
						   filename, tag);
  }

  
  template <>
  Timeseries<float> 
  readh5(std::string filename, std::string tag)
  { 
    return Timeseries<float>(detail::readh5_array_1d<float>(filename, tag)); 
  }

  template <>
  Timeseries<double> 
  readh5(std::string filename, std::string tag)
  { 
    return Timeseries<double>(detail::readh5_array_1d<double>(filename, tag)); 
  }
  
  template <>
  Timeseries<std::complex<float>> 
  readh5(std::string filename, std::string tag)
  { 
    return Timeseries<std::complex<float>>
      (detail::readh5_array_1d<std::complex<float>>(filename, tag)); 
  }
  
  template <>
  Timeseries<std::complex<double>> 
  readh5(std::string filename, std::string tag)
   { 
    return Timeseries<std::complex<double>>
      (detail::readh5_array_1d<std::complex<double>>(filename, tag)); 
   }

}

#include <cstdlib>
#include <iostream>

#include "dumper.h"

#include <lime/detail/dumper_detail.h>

namespace lime
{
  template <class timeseries_t>
  Dumper<timeseries_t>::Dumper(timeseries_t& timeseries, 
			       std::string filename, int precision)
    : timeseries_(timeseries),
      filename_(filename),
      previous_dump_(0),
      header_(""),
      precision_(precision)
  {
    file_.open(filename);
    if(file_.fail()) 
      {
	std::cerr << "Lime, Error while initializing Dumper: " 
		  << "Could not open file with filename ["
		  << filename << "] given. Abort." << std::endl;
	exit(EXIT_FAILURE);
      }
  }

  template <class timeseries_t>
  Dumper<timeseries_t>::~Dumper()
  { file_.close(); }

  template <class timeseries_t>
  void Dumper<timeseries_t>::set_header(std::string header)
  { header_ = header; } 

  template <class timeseries_t>
  void Dumper<timeseries_t>::dump(bool write_header)
  { detail::dump_to_file(timeseries_, file_, previous_dump_, 
			 write_header, header_, precision_); }

  template class Dumper<Timeseries<float>>;
  template class Dumper<Timeseries<double>>;
  template class Dumper<Timeseries<std::complex<float>>>;
  template class Dumper<Timeseries<std::complex<double>>>;

}

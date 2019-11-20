#include <iomanip>

#include "dumper_detail.h"

namespace lime
{
  namespace detail
  {

    template <class coeff_t>
    void dump_to_file(Timeseries<coeff_t>& timeseries, 
		      std::ofstream& file, int& previous_dump, 
		      bool write_header, std::string header,
		      int precision)
    {
      assert(file.good());
      for (int idx = previous_dump; idx < timeseries.size(); ++idx)
	file << std::setprecision(precision)
	     << timeseries[idx] << std::endl;
      previous_dump = timeseries.size();
    }


    template <class key_t, class estimator_t>
    void dump_to_file(Collection<key_t, estimator_t>& collection, 
		      std::ofstream& file, int& previous_dump, 
		      bool write_header, std::string header,
		      int precision)
    {
      assert(file.good());
      int timeseries_size = collection.begin()->second.size();

      std::vector<key_t> keys = collection.keys();

      // Check whether all timeseries have the same length
      for (auto key_timeseries : collection)
	assert(timeseries_size == (int)key_timeseries.second.size());	 
    
      // Write the header
      if (write_header && (previous_dump == 0))
	{
	  std::string prefix = "#";
	  if (header != "")
	    file << prefix << " " << header << std::endl;
	  file << prefix << " ";
	  for (auto key : keys)
	    file << key << " ";
	  file << "\n";
	}
      
      // Write the data
      for (int idx = previous_dump; idx < timeseries_size; ++idx)
	{
	  for (auto& key : keys)
	    file << std::setprecision(precision)
		 << collection[key][idx] << " ";
	  file << std::endl;
	}
      previous_dump = timeseries_size;
    }


    template 
    void dump_to_file<float>
    (Timeseries<float>& timeseries, std::ofstream& file, int& previous_dump, 
     bool write_header, std::string header, int precision);
    template 
    void dump_to_file<double>
    (Timeseries<double>& timeseries, std::ofstream& file, int& previous_dump, 
     bool write_header, std::string header, int precision);
    template 
    void dump_to_file<std::complex<float>>
    (Timeseries<std::complex<float>>& timeseries, std::ofstream& file, int& previous_dump, 
     bool write_header, std::string header, int precision);
    template 
    void dump_to_file<std::complex<double>>
    (Timeseries<std::complex<double>>& timeseries, std::ofstream& file, int& previous_dump, 
     bool write_header, std::string header, int precision);

    template 
    void dump_to_file<std::string, Timeseries<float>>
    (Collection<std::string, Timeseries<float>>& collection, 
     std::ofstream& file, int& previous_dump, bool write_header, std::string header,
     int precision);
    template 
    void dump_to_file<std::string, Timeseries<double>>
    (Collection<std::string, Timeseries<double>>& collection, 
     std::ofstream& file, int& previous_dump, bool write_header, std::string header,
     int precision);
    template 
    void dump_to_file<std::string, Timeseries<std::complex<float>>>
    (Collection<std::string, Timeseries<std::complex<float>>>& collection, 
     std::ofstream& file, int& previous_dump, bool write_header, std::string header,
     int precision);
    template 
    void dump_to_file<std::string, Timeseries<std::complex<double>>>
    (Collection<std::string, Timeseries<std::complex<double>>>& collection, 
     std::ofstream& file, int& previous_dump, bool write_header, std::string header,
     int precision);


  }  // namespace detail

}

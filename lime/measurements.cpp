#include "measurements.h"

#include <algorithm>

#include <lime/type_string.h>

namespace lime 
{
  Measurements::Measurements()
    : previous_dump_(0)
  {};

  template <class data_t>
  void Measurements::append(std::string field, data_t const& data)
  {
    std::string type = type_string(data);

    // Create new field if not already present
    if (std::find(fields_.begin(), fields_.end(), field) == fields_.end())
      {
	fields_.push_back(field);
	type_[field] = type;	
      }
    // Check if type agrees with previously defined type
    else
      {
	if (type != type_[field])
	  {
	    auto msg = std::string("Lime error: field already defined with "
				   "different type.");
	    throw std::runtime_error(msg);
	  }
      }
    collector(data)[field].push_back(data);
  }

  template <class data_t>
  long dump_collector(FileH5& file, std::string field, long start,
		      std::map<std::string, std::vector<data_t>> const&
		      collector)
  {
    long end = (long)collector.size();
    for (long idx=start; idx<end; ++idx)
      file.append(field, collector.at(field).at(idx));
    return end;
  }
  
  void Measurements::dump(FileH5& file)
  {
    for (auto field : fields)
      {
	long start = previous_dump(field);
	long end=0;
	if (type(field) == "IntScalar")
	  end = dump_collector(file, field, start, collector_i_);
	else if (type(field) == "UintScalar")
	  end = dump_collector(file, field, start, collector_u_);
	else if (type(field) == "FloatScalar")
	  end = dump_collector(file, field, start, collector_s_);
	else if (type(field) == "DoubleScalar")
	  end = dump_collector(file, field, start, collector_d_);
	else if (type(field) == "ComplexFloatScalar")
	  end = dump_collector(file, field, start, collector_c_);
	else if (type(field) == "ComplexDoubleScalar")
	  end = dump_collector(file, field, start, collector_z_);
	else if (type(field) == "FloatVector")
	  end = dump_collector(file, field, start, collector_s_vec_);
	else if (type(field) == "DoubleVector")
	  end = dump_collector(file, field, start, collector_d_vec_);
	else if (type(field) == "ComplexFloatVector")
	  end = dump_collector(file, field, start, collector_c_vec_);
	else if (type(field) == "ComplexDoubleVector")
	  end = dump_collector(file, field, start, collector_z_vec_);
	else if (type(field) == "FloatMatrix")
	  end = dump_collector(file, field, start, collector_s_mat_);
	else if (type(field) == "DoubleMatrix")
	  end = dump_collector(file, field, start, collector_d_mat_);
	else if (type(field) == "ComplexFloatMatrix")
	  end = dump_collector(file, field, start, collector_c_mat_);
	else if (type(field) == "ComplexDoubleMatrix")
	  end = dump_collector(file, field, start, collector_z_mat_);
	else
	  {
	    auto msg = std::string("Lime error: Invalid field type in dump");
	    throw std::runtime_error(msg);
	  }
	previous_dump_[field] = end;
      }
  }
    
  template <>
  inline std::map<std::string, std::vector<int>>&
  Measurements::collector(int const& data)
  { return collector_i_; }  
  template <>
  inline std::map<std::string, std::vector<unsigned>>&
  Measurements::collector(unsigned const& data)
  { return collector_u_; }
  template <>
  inline std::map<std::string, std::vector<float>>&
  Measurements::collector(float const& data)
  { return collector_s_; }
  template <>
  inline std::map<std::string, std::vector<double>>&
  Measurements::collector(double const& data)
  { return collector_d_; }
  template <>
  inline std::map<std::string, std::vector<scomplex>>&
  Measurements::collector(scomplex const& data)
  { return collector_c_; }
  template <>
  inline std::map<std::string, std::vector<complex>>&
  Measurements::collector(complex const& data)
  { return collector_z_; }

  template <>
  inline std::map<std::string, std::vector<svector>>&
  Measurements::collector(svector const& data)
  { return collector_s_vec_; }
  template <>
  inline std::map<std::string, std::vector<dvector>>&
  Measurements::collector(dvector const& data)
  { return collector_d_vec_; }
  template <>
  inline std::map<std::string, std::vector<cvector>>&
  Measurements::collector(cvector const& data)
  { return collector_c_vec_; }
  template <>
  inline std::map<std::string, std::vector<zvector>>&
  Measurements::collector(zvector const& data)
  { return collector_z_vec_; }

  template <>
  inline std::map<std::string, std::vector<smatrix>>&
  Measurements::collector(smatrix const& data)
  { return collector_s_mat_; }
  template <>
  inline std::map<std::string, std::vector<dmatrix>>&
  Measurements::collector(dmatrix const& data)
  { return collector_d_mat_; }
  template <>
  inline std::map<std::string, std::vector<cmatrix>>&
  Measurements::collector(cmatrix const& data)
  { return collector_c_mat_; }
  template <>
  inline std::map<std::string, std::vector<zmatrix>>&
  Measurements::collector(zmatrix const& data)
  { return collector_z_mat_; }

  template void Measurements::append(std::string, int const&);
  template void Measurements::append(std::string, unsigned const&);
  template void Measurements::append(std::string, float const&);
  template void Measurements::append(std::string, double const&);
  template void Measurements::append(std::string, scomplex const&);
  template void Measurements::append(std::string, complex const&);
  template void Measurements::append(std::string, svector const&);
  template void Measurements::append(std::string, dvector const&);
  template void Measurements::append(std::string, cvector const&);
  template void Measurements::append(std::string, zvector const&);
  template void Measurements::append(std::string, smatrix const&);
  template void Measurements::append(std::string, dmatrix const&);
  template void Measurements::append(std::string, cmatrix const&);
  template void Measurements::append(std::string, zmatrix const&);
  
}

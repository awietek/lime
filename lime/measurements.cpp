#include "measurements.h"

#include <algorithm>

#include <lime/type_string.h>

namespace lime 
{
  std::vector<std::string> Measurements::fields() const
  { return fields_; }

  bool Measurements::defined(std::string field) const
  {
    return std::find(fields_.begin(), fields_.end(), field) != fields_.end();
  }
  
  std::string Measurements::type(std::string field) const
  { return type_.at(field); }
  
  long Measurements::previous_dump(std::string field) const
  { return previous_dump_.at(field); }

  long Measurements::size(std::string field) const
  {
    long size = 0;
    if (type(field) == "IntScalar")
      size = (long)collector_i_sca_.at(field).size();
    else if (type(field) == "UintScalar")
      size = (long)collector_u_sca_.at(field).size();
    else if (type(field) == "FloatScalar")
      size = (long)collector_s_sca_.at(field).size();
    else if (type(field) == "DoubleScalar")
      size = (long)collector_d_sca_.at(field).size();
    else if (type(field) == "ComplexFloatScalar")
      size = (long)collector_c_sca_.at(field).size();
    else if (type(field) == "ComplexDoubleScalar")
      size = (long)collector_z_sca_.at(field).size();
    else if (type(field) == "FloatVector")
      size = (long)collector_s_vec_.at(field).size();
    else if (type(field) == "DoubleVector")
      size = (long)collector_d_vec_.at(field).size();
    else if (type(field) == "ComplexFloatVector")
      size = (long)collector_c_vec_.at(field).size();
    else if (type(field) == "ComplexDoubleVector")
      size = (long)collector_z_vec_.at(field).size();
    else if (type(field) == "FloatMatrix")
      size = (long)collector_s_mat_.at(field).size();
    else if (type(field) == "DoubleMatrix")
      size = (long)collector_d_mat_.at(field).size();
    else if (type(field) == "ComplexFloatMatrix")
      size = (long)collector_c_mat_.at(field).size();
    else if (type(field) == "ComplexDoubleMatrix")
      size = (long)collector_z_mat_.at(field).size();
    else
      {
	auto msg = std::string("Lime error: Invalid field type in dump");
	throw std::runtime_error(msg);
      }
    return size;
  }
  
  template <class data_t>
  void Measurements::append(std::string field, data_t const& data)
  {
    std::string type = type_string(data);

    // Create new field if not already present
    if (!defined(field))
      {
	fields_.push_back(field);
	type_[field] = type;
	previous_dump_[field] = (long)0;
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
  void Measurements::get(std::string field, long idx, data_t& data) const
  {
    if (defined(field))
      {
	if (type(field) == type_string(data))
	  data = collector(data).at(field).at(idx);
	else
	  {
	    auto msg = std::string("Lime error: cannot get field in "
				   "measurements. Incompatible types.");
	    throw std::runtime_error(msg);
	  }
      }
    else
      {
	auto msg = std::string("Lime error: cannot find field in \"get\""
			       " for measurements.");
	throw std::runtime_error(msg);
      }
  }
  
  template <class data_t>
  long read_collector(FileH5 const& file, std::string field, 
		      std::map<std::string, std::vector<data_t>>&
		      collector)
  {
    std::vector<data_t> data;
    file.read(field, data);
    for (auto const& val : data)
      collector[field].push_back(val);
    return collector[field].size();
  }
  
  void Measurements::read(FileH5 const& file)
  {
    for (std::string field : file.fields())
      {
	// Only read extensible fields
	if (file.extensible(field))
	  {
	    fields_.push_back(field);
	    type_[field] = file.type(field);

	    long prev_dump = 0;
	    if (type(field) == "IntScalar")
	      prev_dump = read_collector(file, field, collector_i_sca_);
	    else if (type(field) == "UintScalar")
	      prev_dump = read_collector(file, field, collector_u_sca_);
	    else if (type(field) == "FloatScalar")
	      prev_dump = read_collector(file, field, collector_s_sca_);
	    else if (type(field) == "DoubleScalar")
	      prev_dump = read_collector(file, field, collector_d_sca_);
	    else if (type(field) == "ComplexFloatScalar")
	      prev_dump = read_collector(file, field, collector_c_sca_);
	    else if (type(field) == "ComplexDoubleScalar")
	      prev_dump = read_collector(file, field, collector_z_sca_);
	    else if (type(field) == "FloatVector")
	      prev_dump = read_collector(file, field, collector_s_vec_);
	    else if (type(field) == "DoubleVector")
	      prev_dump = read_collector(file, field, collector_d_vec_);
	    else if (type(field) == "ComplexFloatVector")
	      prev_dump = read_collector(file, field, collector_c_vec_);
	    else if (type(field) == "ComplexDoubleVector")
	      prev_dump = read_collector(file, field, collector_z_vec_);
	    else if (type(field) == "FloatMatrix")
	      prev_dump = read_collector(file, field, collector_s_mat_);
	    else if (type(field) == "DoubleMatrix")
	      prev_dump = read_collector(file, field, collector_d_mat_);
	    else if (type(field) == "ComplexFloatMatrix")
	      prev_dump = read_collector(file, field, collector_c_mat_);
	    else if (type(field) == "ComplexDoubleMatrix")
	      prev_dump = read_collector(file, field, collector_z_mat_);
	    else
	      {
		auto msg = std::string("Lime error: Invalid field type in "
				       "read");
		throw std::runtime_error(msg);
	      }
	    previous_dump_[field] = prev_dump;
	  }
      }
  }

  
  template <class data_t>
  long dump_collector(FileH5& file, std::string field, long start,
		      std::map<std::string, std::vector<data_t>> const&
		      collector)
  {
    long end = (long)collector.at(field).size();
    for (long idx=start; idx<end; ++idx)
      file.append(field, collector.at(field).at(idx));
    return end;
  }
  
  void Measurements::dump(FileH5& file)
  {
    for (auto field : fields_)
      {
	long start = previous_dump(field);
	long end=0;
	if (type(field) == "IntScalar")
	  end = dump_collector(file, field, start, collector_i_sca_);
	else if (type(field) == "UintScalar")
	  end = dump_collector(file, field, start, collector_u_sca_);
	else if (type(field) == "FloatScalar")
	  end = dump_collector(file, field, start, collector_s_sca_);
	else if (type(field) == "DoubleScalar")
	  end = dump_collector(file, field, start, collector_d_sca_);
	else if (type(field) == "ComplexFloatScalar")
	  end = dump_collector(file, field, start, collector_c_sca_);
	else if (type(field) == "ComplexDoubleScalar")
	  end = dump_collector(file, field, start, collector_z_sca_);
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

  // Collector as reference
  template <>
  inline std::map<std::string, std::vector<int>>&
  Measurements::collector(int const& data)
  { return collector_i_sca_; }  
  template <>
  inline std::map<std::string, std::vector<unsigned>>&
  Measurements::collector(unsigned const& data)
  { return collector_u_sca_; }
  
  template <>
  inline std::map<std::string, std::vector<sscalar>>&
  Measurements::collector(sscalar const& data)
  { return collector_s_sca_; }
  template <>
  inline std::map<std::string, std::vector<dscalar>>&
  Measurements::collector(dscalar const& data)
  { return collector_d_sca_; }
  template <>
  inline std::map<std::string, std::vector<cscalar>>&
  Measurements::collector(cscalar const& data)
  { return collector_c_sca_; }
  template <>
  inline std::map<std::string, std::vector<zscalar>>&
  Measurements::collector(zscalar const& data)
  { return collector_z_sca_; }

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


  
  // Collector as const-reference
  template <>
  inline std::map<std::string, std::vector<int>> const&
  Measurements::collector(int const& data) const
  { return collector_i_sca_; }  
  template <>
  inline std::map<std::string, std::vector<unsigned>> const&
  Measurements::collector(unsigned const& data) const
  { return collector_u_sca_; }
  
  template <>
  inline std::map<std::string, std::vector<sscalar>> const&
  Measurements::collector(sscalar const& data) const
  { return collector_s_sca_; }
  template <>
  inline std::map<std::string, std::vector<dscalar>> const&
  Measurements::collector(dscalar const& data) const
  { return collector_d_sca_; }
  template <>
  inline std::map<std::string, std::vector<cscalar>> const&
  Measurements::collector(cscalar const& data) const
  { return collector_c_sca_; }
  template <>
  inline std::map<std::string, std::vector<zscalar>> const&
  Measurements::collector(zscalar const& data) const
  { return collector_z_sca_; }

  template <>
  inline std::map<std::string, std::vector<svector>> const&
  Measurements::collector(svector const& data) const
  { return collector_s_vec_; }
  template <>
  inline std::map<std::string, std::vector<dvector>> const&
  Measurements::collector(dvector const& data) const
  { return collector_d_vec_; }
  template <>
  inline std::map<std::string, std::vector<cvector>> const&
  Measurements::collector(cvector const& data) const
  { return collector_c_vec_; }
  template <>
  inline std::map<std::string, std::vector<zvector>> const&
  Measurements::collector(zvector const& data) const
  { return collector_z_vec_; }

  template <>
  inline std::map<std::string, std::vector<smatrix>> const&
  Measurements::collector(smatrix const& data) const
  { return collector_s_mat_; }
  template <>
  inline std::map<std::string, std::vector<dmatrix>> const&
  Measurements::collector(dmatrix const& data) const
  { return collector_d_mat_; }
  template <>
  inline std::map<std::string, std::vector<cmatrix>> const&
  Measurements::collector(cmatrix const& data) const 
  { return collector_c_mat_; }
  template <>
  inline std::map<std::string, std::vector<zmatrix>> const&
  Measurements::collector(zmatrix const& data) const
  { return collector_z_mat_; }

  template void Measurements::append(std::string, int const&);
  template void Measurements::append(std::string, unsigned const&);
  
  template void Measurements::append(std::string, sscalar const&);
  template void Measurements::append(std::string, dscalar const&);
  template void Measurements::append(std::string, cscalar const&);
  template void Measurements::append(std::string, zscalar const&);
  
  template void Measurements::append(std::string, svector const&);
  template void Measurements::append(std::string, dvector const&);
  template void Measurements::append(std::string, cvector const&);
  template void Measurements::append(std::string, zvector const&);
  
  template void Measurements::append(std::string, smatrix const&);
  template void Measurements::append(std::string, dmatrix const&);
  template void Measurements::append(std::string, cmatrix const&);
  template void Measurements::append(std::string, zmatrix const&);

  
  template void Measurements::get(std::string, long, int&) const;
  template void Measurements::get(std::string, long, unsigned&) const;
  
  template void Measurements::get(std::string, long, sscalar&) const;
  template void Measurements::get(std::string, long, dscalar&) const;
  template void Measurements::get(std::string, long, cscalar&) const;
  template void Measurements::get(std::string, long, zscalar&) const;
  
  template void Measurements::get(std::string, long, svector&) const;
  template void Measurements::get(std::string, long, dvector&) const;
  template void Measurements::get(std::string, long, cvector&) const;
  template void Measurements::get(std::string, long, zvector&) const;
  
  template void Measurements::get(std::string, long, smatrix&) const;
  template void Measurements::get(std::string, long, dmatrix&) const;
  template void Measurements::get(std::string, long, cmatrix&) const;
  template void Measurements::get(std::string, long, zmatrix&) const;
  
}

#include "file_h5.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

#include <lime/hdf5/create_static_field.h>
#include <lime/hdf5/read_static_field.h>
#include <lime/hdf5/read_static_compatible.h>
#include <lime/hdf5/write_static_field.h>
#include <lime/hdf5/write_compatible.h>

#include <lime/hdf5/create_extensible_field.h>
#include <lime/hdf5/read_extensible_field.h>
#include <lime/hdf5/read_extensible_compatible.h>
#include <lime/hdf5/append_extensible_field.h>
#include <lime/hdf5/append_compatible.h>

#include <lime/hdf5/field_type_string.h>
#include <lime/hdf5/utils.h>
#include <lime/hdf5/types.h>

namespace lime
{

  FileH5::operator bool() const { return file_id_ != hid_t(); }
  
  FileH5::FileH5(std::string filename, std::string iomode)
    : filename_(filename), iomode_(iomode)
  {
    // Open file in read-only mode
    if (iomode == "r")
      {
	file_id_ = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
	H5Ovisit(file_id_, H5_INDEX_NAME, H5_ITER_NATIVE,
		 &lime::hdf5::parse_file, this, H5O_INFO_BASIC);

	if (file_id_ < 0)
	  {
	    auto msg = std::string("Lime error: can't open file (r): ") +
	      filename;
	    throw std::runtime_error(msg);
	  }
      }
    // Open file in forced write mode
    else if (iomode == "w!")
      {
	file_id_ = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC,
			     H5P_DEFAULT, H5P_DEFAULT);
	if (file_id_ < 0)
	  {
	    auto msg = std::string("Lime error: can't open file (w!): ")+
	      filename;
	    throw std::runtime_error(msg);
	  }
      }
    // Open file in secure write mode
    else if (iomode == "w")
      {
	file_id_ = H5Fcreate(filename.c_str(), H5F_ACC_EXCL,
			     H5P_DEFAULT, H5P_DEFAULT);
	if (file_id_ < 0)
	  {
	    auto msg = std::string("Lime error: can't open file (w): ") +
	      filename;
	    throw std::runtime_error(msg);
	  }
      }
    // Open file in append mode
    else if (iomode == "a")
      {
	file_id_ = H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
	H5Ovisit(file_id_, H5_INDEX_NAME, H5_ITER_NATIVE,
		 &lime::hdf5::parse_file, this, H5O_INFO_BASIC);

	if (file_id_ < 0)
	  {
	    auto msg = std::string("Lime error: can't open file (a): ") +
	      filename;
	    throw std::runtime_error(msg);
	  }
      }
    else
      throw std::runtime_error("Lime error: invalid iomode for FileH5!");
  }

  
  std::string FileH5::field_type(std::string field) const
  { return field_types_.at(field); }

  bool FileH5::has_field(std::string field) const
  {
    return std::find(fields_.begin(), fields_.end(), field) != fields_.end();
  }

  bool FileH5::field_extensible(std::string field) const
  { return field_extensible_.at(field); }

  template <class data_t>
  void FileH5::read(std::string field, data_t& data)
  {
    // Read a field into data
    if (has_field(field))
      {
	// check if field datatype agrees with data
	if (attribute(field, LIME_FIELD_TYPE_STRING) !=
	    lime::hdf5::field_type_string(data))
	  {
	    auto msg = std::string("Lime error: wrong field type in read");
	    throw std::runtime_error(msg);
	  }

	// check if field extensibility is static
	if (attribute(field, LIME_FIELD_STATIC_EXTENSIBLE_STRING) !=
	    "Static")
	  {
	    auto msg = std::string("Lime error: trying to read a static "
				   "field from non-static dataset");
	    throw std::runtime_error(msg);
	  }

	// Check if low level dimensions are OK
	if (lime::hdf5::read_static_compatible(file_id_, field, data))
	  lime::hdf5::read_static_field(file_id_, field, data);
	else
	  {
	    auto msg = std::string("Lime error: cannot read static field! "
				   "Wrong type/shape of field: ")
	      + field;
	    throw std::runtime_error(msg);
	  }
      }
    // Throw error "Field not found"
    else
      {
	auto msg = std::string("Lime error: field not found while "
			       "trying to read: ") + field;
	throw std::runtime_error(msg);
      }
  }

  template <class data_t>
  void FileH5::read(std::string field, std::vector<data_t>& data)
  {
    // Read a field into data
    if (has_field(field))
      {
	// check if field datatype agrees with data
	if (attribute(field, LIME_FIELD_TYPE_STRING) !=
	    lime::hdf5::field_type_string(data))
	  {
	    auto msg = std::string("Lime error: wrong field type in read");
	    throw std::runtime_error(msg);
	  }

	// check if field extensibility is extensible
	if (attribute(field, LIME_FIELD_STATIC_EXTENSIBLE_STRING) !=
	    "Extensible")
	  {
	    auto msg = std::string("Lime error: trying to read an "
				   "extensible field from non-extensible "
				   "dataset");
	    throw std::runtime_error(msg);
	  }

	// Check if low level dimensions are OK
	if (lime::hdf5::read_extensible_compatible(file_id_, field, data))
	  lime::hdf5::read_extensible_field(file_id_, field, data);
	else
	  {
	    auto msg = std::string("Lime error: cannot read extensible "
				   "field! Wrong type/shape of field: ")
	      + field;
	    throw std::runtime_error(msg);
	  }
      }
    // Throw error "Field not found"
    else
      {
	auto msg = std::string("Lime error: field not found while "
			       "trying to read: ") + field;
	throw std::runtime_error(msg);
      }
  }
  
  
  template <class data_t>
  void FileH5::write(std::string field, data_t const& data, bool force)
  {
    if (iomode_=="r")
      {
	throw std::runtime_error("Lime error: cannot write in read mode");
      }
    else
      {
	// Try to write to existing field
	if (has_field(field))
	  {
	    // Write to existing field if possible
	    if (force)
	      {
		// Throw error if field is extensible
		if (field_extensible(field))
		  {
		    auto msg = std::string("Lime error: can't write to "
					   "extensible field. "
					   "Must be appended");
		    throw std::runtime_error(msg);
		  }

		// Write to field if type/shape agree
		if (lime::hdf5::write_compatible(file_id_, field, data))
		  lime::hdf5::write_static_field(file_id_, field, data);

		// Type/shape don't agree -> throw error
		else
		  {
		    auto msg = std::string("Lime error: can't write to "
					   "field. Incompatible type/shape");
		    throw std::runtime_error(msg);
		  }
	      }

	    // Throw error if field already exists
	    else
	      {
		auto msg = std::string("Lime error: can't write to already "
				       "existing field. Use parameter "
				       "force=true to overwrite");
		throw std::runtime_error(msg);
	      }    
	  }
	// Create new field and write
	else
	  {
	    fields_.push_back(field);
	    std::string field_type = lime::hdf5::field_type_string(data);
	    field_types_[field] = field_type;
	    field_extensible_[field] = false;
	    lime::hdf5::create_static_field(file_id_, field, data);
	    set_attribute(field, LIME_FIELD_TYPE_STRING, field_type);
	    set_attribute(field, LIME_FIELD_STATIC_EXTENSIBLE_STRING,
			  "Static");
	    lime::hdf5::write_static_field(file_id_, field, data);
	  }
      }
  }

  template <class data_t>
  void FileH5::append(std::string field, data_t const& data)
  {
    if (iomode_=="r")
      throw std::runtime_error("Lime error: cannot append in read mode");
    else
      {
	// Try to write to existing field
	if (has_field(field))
	  {
	    // Throw error if field is not extensible
	    if (!field_extensible(field))
	      {
		auto msg = std::string("Lime error: can't append to "
				       "non-extensible field.");
		throw std::runtime_error(msg);
	      }

	    // Write to field if type/shape agree
	    if (lime::hdf5::append_compatible(file_id_, field, data))
	      lime::hdf5::append_extensible_field(file_id_, field, data);

	    // Type/shape don't agree -> throw error
	    else
	      {
		auto msg = std::string("Lime error: can't append to "
				       "field. Incompatible type/shape");
		throw std::runtime_error(msg);
	      }
	  }
	// Create new field and append
	else
	  {
	    fields_.push_back(field);
	    std::string field_type = lime::hdf5::field_type_string(data);
	    field_types_[field] = field_type;
	    field_extensible_[field] = true;
	    lime::hdf5::create_extensible_field(file_id_, field, data);
	    set_attribute(field, LIME_FIELD_TYPE_STRING, field_type);
	    set_attribute(field, LIME_FIELD_STATIC_EXTENSIBLE_STRING,
			  "Extensible");
	    lime::hdf5::append_extensible_field(file_id_, field, data);
	  }
      }
  }


  std::string FileH5::attribute(std::string field,std::string attribute_name)
  {
    std::string attribute_value;
    if (has_field(field))
      {
	hid_t dataset_id = H5Dopen2(file_id_, field.c_str(), H5P_DEFAULT);

	if(H5Aexists(dataset_id, attribute_name.c_str()))
	  attribute_value = hdf5::get_attribute_value(dataset_id,
						      attribute_name);
	else
	  {
	    auto msg = std::string("Lime error: given attribute doesn't "
				   "not defined");
	    throw std::runtime_error(msg);
	  }
	H5Dclose(dataset_id);
      }
    else
    {
      auto msg = std::string("Lime error: can't attribute to "
			     "field. Field not found.");
      throw std::runtime_error(msg);
    }
    return attribute_value;
  }


  bool FileH5::has_attribute(std::string field,std::string attribute_name)
  {
    bool has_it = false;
    if (has_field(field))
      {
	hid_t dataset_id = H5Dopen2(file_id_, field.c_str(), H5P_DEFAULT);
	has_it = H5Aexists(dataset_id, attribute_name.c_str());
    	H5Dclose(dataset_id);
      }
    else
      {
	auto msg = std::string("Lime error: can't call has_attribute(...). "
			       "Field not found.");
	throw std::runtime_error(msg);
      }
    return has_it;
  }

  void FileH5::set_attribute(std::string field, std::string attribute_name,
			     std::string attribute_value)
  {
    if (has_field(field))
      {
	hid_t dataset_id = H5Dopen2(file_id_, field.c_str(), H5P_DEFAULT);
	hid_t str_type_id = H5Tcopy(H5T_C_S1);
	hid_t string_space_id = H5Screate(H5S_SCALAR);
	H5Tset_size(str_type_id, attribute_value.length());
	hid_t attribute_id = H5Acreate(dataset_id, attribute_name.c_str(),
				       str_type_id, string_space_id,
				       H5P_DEFAULT, H5P_DEFAULT);
	H5Awrite(attribute_id, str_type_id, attribute_value.c_str());
	H5Aclose(attribute_id);
	H5Sclose(string_space_id);
	H5Tclose(str_type_id);
	H5Dclose(dataset_id);
      }
    else
    {
      auto msg = std::string("Lime error: can't attribute to "
			     "field. Field not found.");
      throw std::runtime_error(msg);
    }
  }
  
  void FileH5::close()
  {
    H5Fclose(file_id_);
    file_id_ = hid_t();
  }
  
}

// Write instantiations
template void lime::FileH5::write(std::string, int const&, bool);
template void lime::FileH5::write(std::string, unsigned const& , bool);
template void lime::FileH5::write(std::string, float const&, bool);
template void lime::FileH5::write(std::string, double const&, bool);
template
void lime::FileH5::write(std::string, std::complex<float> const&, bool);
template
void lime::FileH5::write(std::string, std::complex<double> const&, bool);
template
void lime::FileH5::write(std::string, lila::Vector<float> const&, bool);
template
void lime::FileH5::write(std::string, lila::Vector<double> const&, bool);
template
void lime::FileH5::write(std::string,
			 lila::Vector<std::complex<float>> const&, bool);
template
void lime::FileH5::write(std::string,
			 lila::Vector<std::complex<double>> const&, bool);

template
void lime::FileH5::write(std::string, lila::Matrix<float> const&, bool);
template
void lime::FileH5::write(std::string, lila::Matrix<double> const&, bool);
template
void lime::FileH5::write(std::string,
			 lila::Matrix<std::complex<float>> const&, bool);
template
void lime::FileH5::write(std::string,
			 lila::Matrix<std::complex<double>> const&, bool);

// Read static instantiations
template void lime::FileH5::read(std::string, int&);
template void lime::FileH5::read(std::string, unsigned&);
template void lime::FileH5::read(std::string, float&);
template void lime::FileH5::read(std::string, double&);
template
void lime::FileH5::read(std::string, std::complex<float>&);
template
void lime::FileH5::read(std::string, std::complex<double>&);
template
void lime::FileH5::read(std::string, lila::Vector<float>&);
template
void lime::FileH5::read(std::string, lila::Vector<double>&);
template
void lime::FileH5::read(std::string,
			lila::Vector<std::complex<float>>&);
template
void lime::FileH5::read(std::string,
			lila::Vector<std::complex<double>>&);

template
void lime::FileH5::read(std::string, lila::Matrix<float>&);
template
void lime::FileH5::read(std::string, lila::Matrix<double>&);
template
void lime::FileH5::read(std::string,
			lila::Matrix<std::complex<float>>&);
template
void lime::FileH5::read(std::string,
			lila::Matrix<std::complex<double>>&);


// Read extensible instantiations
template void lime::FileH5::read(std::string, std::vector<int>&);
template void lime::FileH5::read(std::string, std::vector<unsigned>&);
template void lime::FileH5::read(std::string, std::vector<float>&);
template void lime::FileH5::read(std::string, std::vector<double>&);
template
void lime::FileH5::read(std::string, std::vector<std::complex<float>>&);
template
void lime::FileH5::read(std::string, std::vector<std::complex<double>>&);
template
void lime::FileH5::read(std::string, std::vector<lila::Vector<float>>&);
template
void lime::FileH5::read(std::string, std::vector<lila::Vector<double>>&);
template
void lime::FileH5::read(std::string,
			std::vector<lila::Vector<std::complex<float>>>&);
template
void lime::FileH5::read(std::string,
			std::vector<lila::Vector<std::complex<double>>>&);

template
void lime::FileH5::read(std::string, std::vector<lila::Matrix<float>>&);
template
void lime::FileH5::read(std::string, std::vector<lila::Matrix<double>>&);
template
void lime::FileH5::read(std::string,
			std::vector<lila::Matrix<std::complex<float>>>&);
template
void lime::FileH5::read(std::string,
			std::vector<lila::Matrix<std::complex<double>>>&);

// append instantiations
template void lime::FileH5::append(std::string, int const&);
template void lime::FileH5::append(std::string, unsigned const&);
template void lime::FileH5::append(std::string, float const&);
template void lime::FileH5::append(std::string, double const&);
template
void lime::FileH5::append(std::string, std::complex<float> const&);
template
void lime::FileH5::append(std::string, std::complex<double> const&);
template
void lime::FileH5::append(std::string, lila::Vector<float> const&);
template
void lime::FileH5::append(std::string, lila::Vector<double> const&);
template
void lime::FileH5::append(std::string,
			  lila::Vector<std::complex<float>> const&);
template
void lime::FileH5::append(std::string,
			  lila::Vector<std::complex<double>> const&);

template
void lime::FileH5::append(std::string, lila::Matrix<float> const&);
template
void lime::FileH5::append(std::string, lila::Matrix<double> const&);
template
void lime::FileH5::append(std::string,
			  lila::Matrix<std::complex<float>> const&);
template
void lime::FileH5::append(std::string,
			  lila::Matrix<std::complex<double>> const&);
#include "file_h5.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

#include <lime/hdf5/create_static_field.h>
#include <lime/hdf5/write_static_field.h>
#include <lime/hdf5/write_compatible.h>
#include <lime/hdf5/read_field.h>
#include <lime/hdf5/read_compatible.h>
#include <lime/hdf5/field_type_string.h>
#include <lime/hdf5/utils.h>

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
	if (lime::hdf5::read_compatible(file_id_, field, data))
	  lime::hdf5::read_field(file_id_, field, data);
	else
	  {
	    auto msg = std::string("Lime error: cannot read field! "
				   "Wrong type/shape of field ")
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
	    field_types_[field] = lime::hdf5::field_type_string(data);
	    field_extensible_[field] = false;
	    lime::hdf5::create_static_field(file_id_, field, data);
	    lime::hdf5::write_static_field(file_id_, field, data);
	  }
      }
  }

  template <class data_t>
  void FileH5::append(std::string field, data_t const& data)
  {
    // // append to an extensible field
    // if (has_field(field) && field_extensible(field))
    //   {	
    // 	lime::hdf5::append_extensible_field(field, data);
    //   }
    // // Throw error: "Cannot append to static field"
    // else if (has_field(field) && !field_extensible(field))
    //   {
    // 	std::cerr << "Lime Error in FileH5::append: "
    // 		  << "cannot append to field \""
    // 		  << field << "\". Field exists but is static.\n";
    // 	exit(EXIT_FAILURE);
    //   }
    // // Create new extensible field 
    // else if (!has_field(field))
    //   {
    // 	fields_.append(field);
    // 	field_types_[field] = lime::hdf5::type_string(data);
    // 	field_extensible_[field] = true;
    // 	lime::hdf5::create_extensible_field(field, data);
    // 	lime::hdf5::append_extensible_field(field, data);
    //   }
  }

  void FileH5::close()
  {
    if (*this) H5Fclose(file_id_);
    file_id_ = hid_t();
  }



  
}

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

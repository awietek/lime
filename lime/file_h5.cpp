#include "file_h5.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

namespace lime
{
  FileH5::operator bool() const { return file_id_ != hid_t();}
  
  FileH5::FileH5(std::string filename, std::string iomode)
    : filename_(filename), iomode_(iomode)
  {
    // Open file in read-only mode
    if (iomode == "r")
      {
	file_id_ = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
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
    // // Read a field into data
    // if (has_field(field))
    //   {	
    // 	detail::fileh5::read_static_field(field, data);
    //   }
    // // Throw error "Field not found"
    // else
    //   {
    //   }
  }
  
  
  template <class data_t>
  void FileH5::write(std::string field, data_t const& data, bool force)
  {
    // // Overwrite a field
    // if (has_field(field) && force)
    //   {	
    // 	detail::fileh5::delete_field(field);
    // 	field_types_[field] = detail::fileh5::type_string(data);
    // 	field_extensible_[field] = false;
    // 	detail::fileh5::create_static_field(field, data);
    // 	detail::fileh5::write_static_field(field, data);
    //   }
    // // Throw error "Field already there"
    // else if (has_field(field) && !force)
    //   {
    // 	std::cerr << "Lime Error in FileH5::write: cannot write field \""
    // 		  << field << "\". Field already exists. Use parameter force"
    // 		  << " to overwrite forcefully!\n";
    // 	exit(EXIT_FAILURE);
    //   }
    // // Create new field and write
    // else if (!has_field(field))
    //   {
    // 	fields_.append(field);
    // 	field_types_[field] = detail::fileh5::type_string(data);
    // 	field_extensible_[field] = false;
    // 	detail::fileh5::create_static_field(field, data);
    // 	detail::fileh5::write_static_field(field, data);
    //   }
  }

  template <class data_t>
  void FileH5::append(std::string field, data_t const& data)
  {
    // // append to an extensible field
    // if (has_field(field) && field_extensible(field))
    //   {	
    // 	detail::fileh5::append_extensible_field(field, data);
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
    // 	field_types_[field] = detail::fileh5::type_string(data);
    // 	field_extensible_[field] = true;
    // 	detail::fileh5::create_extensible_field(field, data);
    // 	detail::fileh5::append_extensible_field(field, data);
    //   }
  }

  void FileH5::close()
  {
    if (*this) H5Fclose(file_id_);
    file_id_ = hid_t();
  }
   

  
  
}

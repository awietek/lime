#include "parse_file.h"

#include <string>
#include <lime/file_h5.h>
#include <lime/hdf5/field_type_string.h>
#include <lime/hdf5/types.h>
#include <lime/hdf5/utils.h>

namespace lime { namespace hdf5 {
herr_t parse_file(hid_t loc_id, const char *name, const H5O_info_t *info,
		  void *fileh5)
{
  auto name_str = std::string(name);

  // Parse a dataset
  if (info->type == H5O_TYPE_DATASET)
    {
      hid_t dataset_id = H5Dopen2(loc_id, name, H5P_DEFAULT);

      // Dataset is only considered if standard lime attributes exist
      bool has_field_type = H5Aexists(dataset_id, LIME_FIELD_TYPE_STRING);
      bool has_field_static_extensible =
	H5Aexists(dataset_id, LIME_FIELD_STATIC_EXTENSIBLE_STRING);
      if (has_field_type && has_field_static_extensible)
	{
	  // Append the name
	  static_cast<FileH5*>(fileh5)->fields_.push_back(name_str);
	      
	  // Get the lime field type of the dataset
	  std::string field_type =
	    get_attribute_value(dataset_id, LIME_FIELD_TYPE_STRING);
	      
	  if (std::find(all_lime_field_types.begin(),
			all_lime_field_types.end(), field_type) !=
	      all_lime_field_types.end())
	    {
	      static_cast<FileH5*>(fileh5)->field_types_[name_str] =
		field_type;
	    }
	  else
	    {
	      auto msg = std::string("Lime error: invalid field type in "
				     "dataset.");
	      throw std::runtime_error(msg);
	    }
	      
	  // Find out if field is static or extensible
	  std::string static_extensible =
	    get_attribute_value(dataset_id,
				LIME_FIELD_STATIC_EXTENSIBLE_STRING);
	      
	  if (static_extensible == "Static")
	    {
	      static_cast<FileH5*>(fileh5)->field_extensible_[name_str] =
		false;
	    }
	  else if  (static_extensible == "Extensible")
	    {
	      static_cast<FileH5*>(fileh5)->field_extensible_[name_str] =
		true;
	    }
	  else
	    {
	      auto msg = std::string("Lime error: invalid "
				     "static/entensible "
				     "descriptor in dataset.");
	      throw std::runtime_error(msg);
	    }
	}


    }
  // if (name[0] == '.')         /* Root group */
  //   {
  //     // printf ("  (Group)\n");
  //   }
  // else
  //   {
  // switch (info->type) {
  // case H5O_TYPE_GROUP:
  //   // printf ("%s  (Group)\n", name);
  //   break;
  // case H5O_TYPE_DATASET:
  //   break;
  // case H5O_TYPE_NAMED_DATATYPE:
  //   // printf ("%s  (Datatype)\n", name);
  //   break;
  // default:
  //   ;
  //   // printf ("%s  (Unknown)\n", name);
  return 0;
};

}}

#include "parse_file.h"

#include <string>
#include <lime/file_h5.h>
#include <lime/hdf5/field_type_string.h>

namespace lime { namespace hdf5 {
herr_t parse_file(hid_t loc_id, const char *name, const H5O_info_t *info,
		    void *fileh5)
{
  auto name_str = std::string(name);
  hid_t dataset_id;
  if (name[0] == '.')         /* Root group */
    {
      // printf ("  (Group)\n");
    }
  else
    switch (info->type) {
    case H5O_TYPE_GROUP:
      // printf ("%s  (Group)\n", name);
      break;
    case H5O_TYPE_DATASET:
      dataset_id = H5Dopen2(loc_id, name, H5P_DEFAULT);
      static_cast<FileH5*>(fileh5)->fields_.push_back(name_str);
      static_cast<FileH5*>(fileh5)->field_types_[name_str] =
	field_type_string_from_dataset(dataset_id);
      static_cast<FileH5*>(fileh5)->field_extensible_[name_str] = false;
      // printf ("%s  (Dataset)\n", name);
      break;
    case H5O_TYPE_NAMED_DATATYPE:
      // printf ("%s  (Datatype)\n", name);
      break;
    default:
      ;
      // printf ("%s  (Unknown)\n", name);
    }
  return 0;
};

}}

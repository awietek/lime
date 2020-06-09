#include "field_type_string.h"

#include <complex>
#include <string>
#include <lime/hdf5/types.h>
#include <lime/hdf5/utils.h>


namespace lime { namespace hdf5 {
    
// std::string field_type_string_from_dataset(hid_t dataset_id)
// {
//   using scomplex = std::complex<float>;
//   using complex = std::complex<double>;

//   std::string prefix;
//   std::string postfix;
//   hid_t datatype_id = H5Dget_type(dataset_id);
//   if (H5Tequal(datatype_id, hdf5_datatype<int>()))
//     prefix = "Int";
//   else if (H5Tequal(datatype_id, hdf5_datatype<unsigned int>()))
//     prefix = "Uint";
//   else if (H5Tequal(datatype_id, hdf5_datatype<float>()))
//     prefix = "Float";
//   else if (H5Tequal(datatype_id, hdf5_datatype<double>()))
//     prefix = "Double";
//   else if (H5Tequal(datatype_id, hdf5_datatype<scomplex>()))
//     prefix = "Scomplex";
//   else if (H5Tequal(datatype_id, hdf5_datatype<complex>()))
//     prefix = "Complex";
//   else
//     throw std::runtime_error("Lime Error: Unknown datatype in dataset!");

//   auto dims = dataspace_dims(dataset_id);
//   if (dims.size() == 1)
//     {
//       if (dims[0] == 1) postfix = "Scalar";
//       else postfix = "Vector";
//     }
//   else if (dims.size() == 2) postfix = "Matrix";
//   else
//     throw std::runtime_error("Lime Error: Unknown shape in dataset!");
//   return prefix + postfix;
// }

}}

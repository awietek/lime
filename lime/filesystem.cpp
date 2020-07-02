#include "filesystem.h"

#include <fstream>
#include <hdf5.h>

namespace lime {
  
bool exists(std::string filename) {
  std::ifstream inf(filename);
  return inf.good();
}
bool is_hdf5(std::string filename) { return H5Fis_hdf5(filename.c_str()) > 0; }

} // namespace lime

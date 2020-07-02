#include "file_h5_handler.h"
#include <lila/all.h>

#include <lime/file_h5.h>
#include <lime/types.h>

namespace lime {

FileH5Handler::FileH5Handler(std::string field, FileH5 &fileh5)
    : field_(field), fileh5_(&fileh5) {}

bool FileH5Handler::defined() { return fileh5_->defined(field_); }
std::string FileH5Handler::type() { return fileh5_->type(field_); }
bool FileH5Handler::extensible() { return fileh5_->extensible(field_); }

std::string FileH5Handler::attribute(std::string attribute_name) {
  return fileh5_->attribute(field_, attribute_name);
}

bool FileH5Handler::has_attribute(std::string attribute_name) {
  return fileh5_->has_attribute(field_, attribute_name);
}

void FileH5Handler::set_attribute(std::string attribute_name,
                                  std::string attribute_value) {
  return fileh5_->set_attribute(field_, attribute_name, attribute_value);
}

template <class data_t> void FileH5Handler::read(data_t &data) {
  fileh5_->read(field_, data);
}

template <class data_t> void FileH5Handler::read(std::vector<data_t> &data) {
  fileh5_->read(field_, data);
}

template <class data_t> void FileH5Handler::operator<<(data_t const &data) {
  fileh5_->append(field_, data);
}

template <class data_t> void FileH5Handler::operator=(data_t const &data) {
  fileh5_->write(field_, data);
}

template void FileH5Handler::read(int &);
template void FileH5Handler::read(unsigned &);
template void FileH5Handler::read(long &);
template void FileH5Handler::read(unsigned long &);
template void FileH5Handler::read(long long &);
template void FileH5Handler::read(unsigned long long &);

template void FileH5Handler::read(sscalar &);
template void FileH5Handler::read(dscalar &);
template void FileH5Handler::read(cscalar &);
template void FileH5Handler::read(zscalar &);

template void FileH5Handler::read(svector &);
template void FileH5Handler::read(dvector &);
template void FileH5Handler::read(cvector &);
template void FileH5Handler::read(zvector &);

template void FileH5Handler::read(smatrix &);
template void FileH5Handler::read(dmatrix &);
template void FileH5Handler::read(cmatrix &);
template void FileH5Handler::read(zmatrix &);

template void FileH5Handler::read(std::vector<int> &);
template void FileH5Handler::read(std::vector<unsigned> &);
template void FileH5Handler::read(std::vector<long> &);
template void FileH5Handler::read(std::vector<unsigned long> &);
template void FileH5Handler::read(std::vector<long long> &);
template void FileH5Handler::read(std::vector<unsigned long long> &);

template void FileH5Handler::read(std::vector<sscalar> &);
template void FileH5Handler::read(std::vector<dscalar> &);
template void FileH5Handler::read(std::vector<cscalar> &);
template void FileH5Handler::read(std::vector<zscalar> &);

template void FileH5Handler::read(std::vector<svector> &);
template void FileH5Handler::read(std::vector<dvector> &);
template void FileH5Handler::read(std::vector<cvector> &);
template void FileH5Handler::read(std::vector<zvector> &);

template void FileH5Handler::read(std::vector<smatrix> &);
template void FileH5Handler::read(std::vector<dmatrix> &);
template void FileH5Handler::read(std::vector<cmatrix> &);
template void FileH5Handler::read(std::vector<zmatrix> &);

template void FileH5Handler::operator<<(int const &);
template void FileH5Handler::operator<<(unsigned const &);
template void FileH5Handler::operator<<(long const &);
template void FileH5Handler::operator<<(unsigned long const &);
template void FileH5Handler::operator<<(long long const &);
template void FileH5Handler::operator<<(unsigned long long const &);

template void FileH5Handler::operator<<(sscalar const &);
template void FileH5Handler::operator<<(dscalar const &);
template void FileH5Handler::operator<<(cscalar const &);
template void FileH5Handler::operator<<(zscalar const &);

template void FileH5Handler::operator<<(svector const &);
template void FileH5Handler::operator<<(dvector const &);
template void FileH5Handler::operator<<(cvector const &);
template void FileH5Handler::operator<<(zvector const &);

template void FileH5Handler::operator<<(smatrix const &);
template void FileH5Handler::operator<<(dmatrix const &);
template void FileH5Handler::operator<<(cmatrix const &);
template void FileH5Handler::operator<<(zmatrix const &);

template void FileH5Handler::operator=(int const &);
template void FileH5Handler::operator=(unsigned const &);
template void FileH5Handler::operator=(long const &);
template void FileH5Handler::operator=(unsigned long const &);
template void FileH5Handler::operator=(long long const &);
template void FileH5Handler::operator=(unsigned long long const &);

template void FileH5Handler::operator=(sscalar const &);
template void FileH5Handler::operator=(dscalar const &);
template void FileH5Handler::operator=(cscalar const &);
template void FileH5Handler::operator=(zscalar const &);

template void FileH5Handler::operator=(svector const &);
template void FileH5Handler::operator=(dvector const &);
template void FileH5Handler::operator=(cvector const &);
template void FileH5Handler::operator=(zvector const &);

template void FileH5Handler::operator=(smatrix const &);
template void FileH5Handler::operator=(dmatrix const &);
template void FileH5Handler::operator=(cmatrix const &);
template void FileH5Handler::operator=(zmatrix const &);

} // namespace lime

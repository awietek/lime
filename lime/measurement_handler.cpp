#include "measurement_handler.h"

#include <lime/measurements.h>

namespace lime {

MeasurementHandler::MeasurementHandler(std::string field,
                                       Measurements &measurements)
    : field_(field), measurements_(&measurements) {}

bool MeasurementHandler::defined() { return measurements_->defined(field_); }
std::string MeasurementHandler::type() const {
  return measurements_->type(field_);
}
long MeasurementHandler::previous_dump() const {
  return measurements_->previous_dump(field_);
}
long MeasurementHandler::size() const { return measurements_->size(field_); }

template <class data_t> void MeasurementHandler::get(long idx, data_t &data) {
  measurements_->get(field_, idx, data);
}

template <class data_t>
void MeasurementHandler::operator<<(data_t const &data) {
  measurements_->append(field_, data);
}

template void MeasurementHandler::get(long, int &);
template void MeasurementHandler::get(long, unsigned &);
template void MeasurementHandler::get(long, long &);
template void MeasurementHandler::get(long, unsigned long &);
template void MeasurementHandler::get(long, long long &);
template void MeasurementHandler::get(long, unsigned long long &);

template void MeasurementHandler::get(long, sscalar &);
template void MeasurementHandler::get(long, dscalar &);
template void MeasurementHandler::get(long, cscalar &);
template void MeasurementHandler::get(long, zscalar &);

template void MeasurementHandler::get(long, svector &);
template void MeasurementHandler::get(long, dvector &);
template void MeasurementHandler::get(long, cvector &);
template void MeasurementHandler::get(long, zvector &);

template void MeasurementHandler::get(long, smatrix &);
template void MeasurementHandler::get(long, dmatrix &);
template void MeasurementHandler::get(long, cmatrix &);
template void MeasurementHandler::get(long, zmatrix &);

template void MeasurementHandler::operator<<(int const &);
template void MeasurementHandler::operator<<(unsigned const &);
template void MeasurementHandler::operator<<(long const &);
template void MeasurementHandler::operator<<(unsigned long const &);
template void MeasurementHandler::operator<<(long long const &);
template void MeasurementHandler::operator<<(unsigned long long const &);

template void MeasurementHandler::operator<<(sscalar const &);
template void MeasurementHandler::operator<<(dscalar const &);
template void MeasurementHandler::operator<<(cscalar const &);
template void MeasurementHandler::operator<<(zscalar const &);

template void MeasurementHandler::operator<<(svector const &);
template void MeasurementHandler::operator<<(dvector const &);
template void MeasurementHandler::operator<<(cvector const &);
template void MeasurementHandler::operator<<(zvector const &);

template void MeasurementHandler::operator<<(smatrix const &);
template void MeasurementHandler::operator<<(dmatrix const &);
template void MeasurementHandler::operator<<(cmatrix const &);
template void MeasurementHandler::operator<<(zmatrix const &);

} // namespace lime

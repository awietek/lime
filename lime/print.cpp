#include <iomanip>

#include "print.h"

namespace lime {
  template <class coeff_t>
  std::string print_mean_err(coeff_t const& mean, 
			     complex::real_t<coeff_t> const& err, 
			     int precision)
  {
    std::stringstream ss;
    ss << std::setprecision(precision);
    ss << mean << " +- " << err; 
    return ss.str();
  }


  template <class coeff_t>
  std::string print_mean_err(lila::Vector<coeff_t> const& mean, 
			     lila::Vector<complex::real_t<coeff_t>> const& err, 
			     std::string sep, 
			     int precision)
  {
    assert(mean.size() == err.size());
    std::stringstream ss;
    ss << std::setprecision(precision);
    for (int i=0; i<mean.size(); ++i)
      ss << mean(i) << " +- " << err(i) << sep; 
    return ss.str();
  }

  template <class coeff_t>
  std::string print_mean_err(lila::Matrix<coeff_t> const& mean, 
			     lila::Matrix<complex::real_t<coeff_t>> const& err, 
			     std::string seprow, std::string sepcol,
			     int precision)
  {
    assert(mean.nrows() == err.nrows());
    assert(mean.ncols() == err.ncols());
    std::stringstream ss;
    ss << std::setprecision(precision);
    for (int i=0; i<mean.nrows(); ++i)
      {
	for (int j=0; j<mean.nrows(); ++j)
	  ss << mean(i, j) << " +- " << err(i, j) << sepcol; 
	ss << seprow;
      }
    return ss.str();
  }


  template <class coeff_t>
  std::string print_mean_err_tau(coeff_t const& mean, 
				 complex::real_t<coeff_t> const& err, 
				 complex::real_t<coeff_t> const& tau, 
				 int precision)
  {
    std::stringstream ss;
    ss << std::setprecision(precision);
    ss << mean << " +- " << err << " (tau=" << tau << ")"; 
    return ss.str();
  }


  template <class coeff_t>
  std::string print_mean_err_tau(lila::Vector<coeff_t> const& mean, 
				 lila::Vector<complex::real_t<coeff_t>> const& err, 
				 lila::Vector<complex::real_t<coeff_t>> const& tau, 
				 std::string sep, 
				 int precision)
  {
    assert(mean.size() == err.size());
    std::stringstream ss;
    ss << std::setprecision(precision);
    for (int i=0; i<mean.size(); ++i)
      ss << mean(i) << " +- " << err(i) 
	 << " (tau=" << tau(i) << ")" << sep; 
    return ss.str();
  }

  template <class coeff_t>
  std::string print_mean_err_tau(lila::Matrix<coeff_t> const& mean, 
				 lila::Matrix<complex::real_t<coeff_t>> const& err, 
				 lila::Matrix<complex::real_t<coeff_t>> const& tau, 
				 std::string seprow, std::string sepcol,
				 int precision)
  {
    assert(mean.nrows() == err.nrows());
    assert(mean.ncols() == err.ncols());
    std::stringstream ss;
    ss << std::setprecision(precision);
    for (int i=0; i<mean.nrows(); ++i)
      {
	for (int j=0; j<mean.nrows(); ++j)
	  ss << mean(i, j) << " +- " << err(i, j) 
	     << " (tau=" << tau(i,j) << ")" <<  sepcol; 
	ss << seprow;
      }
    return ss.str();
  }

  template
  std::string print_mean_err<float>
  (float const& mean, float const& err, int precision);
  template
  std::string print_mean_err<double>
  (double const& mean, double const& err, int precision);
  template
  std::string print_mean_err<std::complex<float>>
  (std::complex<float> const& mean, float const& err, int precision);
  template
  std::string print_mean_err<std::complex<double>>
  (std::complex<double> const& mean, double const& err, int precision);

  template
  std::string print_mean_err<float>
  (lila::Vector<float> const& mean, lila::Vector<float> const& err, 
   std::string sep, int precision);
  template
  std::string print_mean_err<double>
  (lila::Vector<double> const& mean, lila::Vector<double> const& err, 
   std::string sep,int precision);
  template
  std::string print_mean_err<std::complex<float>>
  (lila::Vector<std::complex<float>> const& mean,
   lila::Vector<float> const& err, std::string sep, int precision);
  template
  std::string print_mean_err<std::complex<double>>
  (lila::Vector<std::complex<double>> const& mean,
   lila::Vector<double> const& err, std::string sep, int precision);

  template
  std::string print_mean_err<float>
  (lila::Matrix<float> const& mean, lila::Matrix<float> const& err, 
   std::string seprow, std::string sepcol, int precision);
  template
  std::string print_mean_err<double>
  (lila::Matrix<double> const& mean, lila::Matrix<double> const& err, 
   std::string seprow, std::string sepcol, int precision);
  template
  std::string print_mean_err<std::complex<float>>
  (lila::Matrix<std::complex<float>> const& mean,
   lila::Matrix<float> const& err, 
   std::string seprow, std::string sepcol, int precision);
  template
  std::string print_mean_err<std::complex<double>>
  (lila::Matrix<std::complex<double>> const& mean,
   lila::Matrix<double> const& err, 
   std::string seprow, std::string sepcol, int precision);




  template std::string print_mean_err_tau<float>
  (float const& mean, float const& err, float const& tau, int precision);
  template
  std::string print_mean_err_tau<double>
  (double const& mean, double const& err, double const& tau, int precision);
  template
  std::string print_mean_err_tau<std::complex<float>>
  (std::complex<float> const& mean, float const& err, float const& tau, int precision);
  template
  std::string print_mean_err_tau<std::complex<double>>
  (std::complex<double> const& mean, double const& err, double const& tau, int precision);

  template
  std::string print_mean_err_tau<float>
  (lila::Vector<float> const& mean, lila::Vector<float> const& err,
   lila::Vector<float> const& tau, std::string sep, int precision);
  template
  std::string print_mean_err_tau<double>
  (lila::Vector<double> const& mean, lila::Vector<double> const& err,
   lila::Vector<double> const& tau, std::string sep, int precision);
  template
  std::string print_mean_err_tau<std::complex<float>>
  (lila::Vector<std::complex<float>> const& mean,
   lila::Vector<float> const& err, lila::Vector<float> const& tau,
   std::string sep, int precision);
  template
  std::string print_mean_err_tau<std::complex<double>>
  (lila::Vector<std::complex<double>> const& mean,
   lila::Vector<double> const& err, lila::Vector<double> const& tau,
   std::string sep, int precision);

  template
  std::string print_mean_err_tau<float>
  (lila::Matrix<float> const& mean, lila::Matrix<float> const& err,
   lila::Matrix<float> const& tau, 
   std::string seprow, std::string sepcol, int precision);
  template
  std::string print_mean_err_tau<double>
  (lila::Matrix<double> const& mean, lila::Matrix<double> const& err, 
   lila::Matrix<double> const& tau, 
   std::string seprow, std::string sepcol, int precision);
  template
  std::string print_mean_err_tau<std::complex<float>>
  (lila::Matrix<std::complex<float>> const& mean,
   lila::Matrix<float> const& err, lila::Matrix<float> const& tau,
   std::string seprow, std::string sepcol, int precision);
  template
  std::string print_mean_err_tau<std::complex<double>>
  (lila::Matrix<std::complex<double>> const& mean,
   lila::Matrix<double> const& err, lila::Matrix<double> const& tau, 
   std::string seprow, std::string sepcol, int precision);


}

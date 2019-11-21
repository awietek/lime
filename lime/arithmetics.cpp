#include <complex>
#include <algorithm>
#include <limits>

#include "arithmetics.h"

namespace lime {
  namespace arithmetics {
   
    template <class coeff_t>
    coeff_t div(coeff_t const& a, coeff_t const& b) { return a / b ; }

    template <class coeff_t>
    lila::Vector<coeff_t> 
    div(lila::Vector<coeff_t> const& a, lila::Vector<coeff_t> const& b) 
    { 
      assert(a.size()==b.size());
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.size(); ++i)
	w(i) = a(i) / b(i);
      return w;
    }

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    div(lila::Matrix<coeff_t> const& a, lila::Matrix<coeff_t> const& b) 
    { 
      assert(a.nrows()==b.nrows());
      assert(a.ncols()==b.ncols());
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.nrows(); ++i)
	for (int j=0; j<a.ncols(); ++j)
	  w(i,j) = a(i,j) / b(i,j);
      return w;
    }

    template <class coeff_t>
    coeff_t mult(coeff_t const& a, coeff_t const& b) { return a * b ; }

    template <class coeff_t>
    lila::Vector<coeff_t> 
    mult(lila::Vector<coeff_t> const& a, lila::Vector<coeff_t> const& b) 
    { 
      assert(a.size()==b.size());
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.size(); ++i)
	w(i) = a(i) * b(i);
      return w;
    }

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    mult(lila::Matrix<coeff_t> const& a, lila::Matrix<coeff_t> const& b) 
    { 
      assert(a.nrows()==b.nrows());
      assert(a.ncols()==b.ncols());
      auto w = lila::ZerosLike(a);
      
      for (int i=0; i<a.nrows(); ++i)
      	for (int j=0; j<a.ncols(); ++j)
      	  w(i, j) = a(i,j) * b(i,j);

      return w;
    }

    template <class coeff_t>
    coeff_t div_zero_to_one(coeff_t const& a, coeff_t const& b) 
    { return std::norm(b) < 1e-12 ? 1. : a / b ; }

    template <class coeff_t>
    lila::Vector<coeff_t> 
    div_zero_to_one(lila::Vector<coeff_t> const& a, lila::Vector<coeff_t> const& b) 
    { 
      assert(a.size()==b.size());
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.size(); ++i)
	w(i) = std::norm(b(i)) < 1e-12 ? 1. : a(i) / b(i);
      return w;
    }

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    div_zero_to_one(lila::Matrix<coeff_t> const& a, lila::Matrix<coeff_t> const& b) 
    { 
      assert(a.nrows()==b.nrows());
      assert(a.ncols()==b.ncols());
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.nrows(); ++i)
	for (int j=0; j<a.ncols(); ++j)
	  w(i,j) =  std::norm(b(i,j)) < 1e-12 ? 1. : a(i,j) / b(i,j);
      return w;
    }



    template <class coeff_t>
    coeff_t sqrt(coeff_t const& a) { return std::sqrt(a); }

    template <class coeff_t>
    lila::Vector<coeff_t> 
    sqrt(lila::Vector<coeff_t> const& a) 
    { 
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.size(); ++i)
	w(i) = std::sqrt(a(i));
      return w;
    }

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    sqrt(lila::Matrix<coeff_t> const& a) 
    { 
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.nrows(); ++i)
	for (int j=0; j<a.ncols(); ++j)
	  w(i,j) = std::sqrt(a(i,j));
      return w;
    }


    template <class coeff_t>
    coeff_t abs(coeff_t const& a) { return std::abs(a); }

    template <class coeff_t>
    lila::Vector<coeff_t> 
    abs(lila::Vector<coeff_t> const& a) 
    { 
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.size(); ++i)
	w(i) = std::abs(a(i));
      return w;
    }

    template <class coeff_t>
    lila::Matrix<coeff_t> 
    abs(lila::Matrix<coeff_t> const& a) 
    { 
      auto w = lila::ZerosLike(a);
      for (int i=0; i<a.nrows(); ++i)
	for (int j=0; j<a.ncols(); ++j)
	  w(i,j) = std::abs(a(i,j));
      return w;
    }

    template <class coeff_t>
    complex::real_t<coeff_t> norm(coeff_t const& a) { return std::norm(a); }

    template <class coeff_t>
    lila::Vector<complex::real_t<coeff_t>> 
    norm(lila::Vector<coeff_t> const& a) 
    { 
      auto w = lila::Zeros<complex::real_t<coeff_t>>(a.size());
      for (int i=0; i<a.size(); ++i)
	w(i) = std::norm(a(i));
      return w;
    }

    template <class coeff_t>
    lila::Matrix<complex::real_t<coeff_t>> 
    norm(lila::Matrix<coeff_t> const& a) 
    { 
      auto w = lila::Zeros<complex::real_t<coeff_t>>(a.nrows(), a.ncols());
      for (int i=0; i<a.nrows(); ++i)
	for (int j=0; j<a.ncols(); ++j)
	  w(i,j) = std::norm(a(i,j));
      return w;
    }
    
    template <class coeff_t>
    coeff_t accumulate(std::vector<coeff_t> const& vec)
    {
      return std::accumulate(vec.begin(), vec.end(), (coeff_t)0.);
    }

    template <class coeff_t>
    lila::Vector<coeff_t>
    accumulate(std::vector<lila::Vector<coeff_t>> const& vec)
    {
      assert(vec.size()>0);
      auto size = vec.size();
      auto zeros = lila::Zeros<coeff_t>(size);
      return std::accumulate(vec.begin(), vec.end(), zeros);
    }

    template <class coeff_t>
    lila::Matrix<coeff_t>
    accumulate(std::vector<lila::Matrix<coeff_t>> const& vec)
    {
      assert(vec.size()>0);
      auto nrows = vec[0].nrows();
      auto ncols = vec[0].ncols();
      auto zeros = lila::Zeros<coeff_t>(nrows, ncols);
      return std::accumulate(vec.begin(), vec.end(), zeros);
    }

    template <class coeff_t>
    complex::real_t<coeff_t>
    infinity(coeff_t const& vec)
    {
      return std::numeric_limits<complex::real_t<coeff_t>>::infinity();
    }

    template <class coeff_t>
    lila::Vector<complex::real_t<coeff_t>>
    infinity(lila::Vector<coeff_t> const& vec)
    {
      auto w = lila::Vector<complex::real_t<coeff_t>>(vec.size());
      std::fill(w.begin(), w.end(), 
		std::numeric_limits<complex::real_t<coeff_t>>::infinity());
      return w;
    }

    template <class coeff_t>
    lila::Matrix<complex::real_t<coeff_t>>
    infinity(lila::Matrix<coeff_t> const& mat)
    {
      auto w = lila::Matrix<complex::real_t<coeff_t>>(mat.nrows(), mat.ncols());
      std::fill(w.begin(), w.end(), 
		std::numeric_limits<complex::real_t<coeff_t>>::infinity());
      return w;
    }


    template float div(float const& a, float const& b);
    template double div(double const& a, double const& b);
    template std::complex<float> div(std::complex<float> const& a, 
				     std::complex<float> const& b);
    template std::complex<double> div(std::complex<double> const& a, 
				      std::complex<double> const& b);
    template lila::Vector<float> 
    div(lila::Vector<float> const& a, lila::Vector<float> const& b);
    template lila::Vector<double> 
    div(lila::Vector<double> const& a, lila::Vector<double> const& b);
    template lila::Vector<std::complex<float>> 
    div(lila::Vector<std::complex<float>> const& a, 
	lila::Vector<std::complex<float>> const& b);
    template lila::Vector<std::complex<double>> 
    div(lila::Vector<std::complex<double>> const& a, 
	lila::Vector<std::complex<double>> const& b);
    template lila::Matrix<float> 
    div(lila::Matrix<float> const& a, lila::Matrix<float> const& b);
    template lila::Matrix<double> 
    div(lila::Matrix<double> const& a, lila::Matrix<double> const& b);
    template lila::Matrix<std::complex<float>> 
    div(lila::Matrix<std::complex<float>> const& a, 
	lila::Matrix<std::complex<float>> const& b);
    template lila::Matrix<std::complex<double>> 
    div(lila::Matrix<std::complex<double>> const& a, 
	lila::Matrix<std::complex<double>> const& b);


    template float div_zero_to_one(float const& a, float const& b);
    template double div_zero_to_one(double const& a, double const& b);
    template std::complex<float> div_zero_to_one(std::complex<float> const& a, 
				     std::complex<float> const& b);
    template std::complex<double> div_zero_to_one(std::complex<double> const& a, 
				      std::complex<double> const& b);
    template lila::Vector<float> 
    div_zero_to_one(lila::Vector<float> const& a, lila::Vector<float> const& b);
    template lila::Vector<double> 
    div_zero_to_one(lila::Vector<double> const& a, lila::Vector<double> const& b);
    template lila::Vector<std::complex<float>> 
    div_zero_to_one(lila::Vector<std::complex<float>> const& a, 
	lila::Vector<std::complex<float>> const& b);
    template lila::Vector<std::complex<double>> 
    div_zero_to_one(lila::Vector<std::complex<double>> const& a, 
	lila::Vector<std::complex<double>> const& b);
    template lila::Matrix<float> 
    div_zero_to_one(lila::Matrix<float> const& a, lila::Matrix<float> const& b);
    template lila::Matrix<double> 
    div_zero_to_one(lila::Matrix<double> const& a, lila::Matrix<double> const& b);
    template lila::Matrix<std::complex<float>> 
    div_zero_to_one(lila::Matrix<std::complex<float>> const& a, 
	lila::Matrix<std::complex<float>> const& b);
    template lila::Matrix<std::complex<double>> 
    div_zero_to_one(lila::Matrix<std::complex<double>> const& a, 
	lila::Matrix<std::complex<double>> const& b);


    template float mult(float const& a, float const& b);
    template double mult(double const& a, double const& b);
    template std::complex<float> mult(std::complex<float> const& a, 
				     std::complex<float> const& b);
    template std::complex<double> mult(std::complex<double> const& a, 
				      std::complex<double> const& b);
    template lila::Vector<float> 
    mult(lila::Vector<float> const& a, lila::Vector<float> const& b);
    template lila::Vector<double> 
    mult(lila::Vector<double> const& a, lila::Vector<double> const& b);
    template lila::Vector<std::complex<float>> 
    mult(lila::Vector<std::complex<float>> const& a, 
	lila::Vector<std::complex<float>> const& b);
    template lila::Vector<std::complex<double>> 
    mult(lila::Vector<std::complex<double>> const& a, 
	lila::Vector<std::complex<double>> const& b);
    template lila::Matrix<float> 
    mult(lila::Matrix<float> const& a, lila::Matrix<float> const& b);
    template lila::Matrix<double> 
    mult(lila::Matrix<double> const& a, lila::Matrix<double> const& b);
    template lila::Matrix<std::complex<float>> 
    mult(lila::Matrix<std::complex<float>> const& a, 
	lila::Matrix<std::complex<float>> const& b);
    template lila::Matrix<std::complex<double>> 
    mult(lila::Matrix<std::complex<double>> const& a, 
	lila::Matrix<std::complex<double>> const& b);



    template float sqrt(float const& a);
    template double sqrt(double const& a);
    template std::complex<float> sqrt(std::complex<float> const& a);
    template std::complex<double> sqrt(std::complex<double> const& a);
    template lila::Vector<float> 
    sqrt(lila::Vector<float> const& a);
    template lila::Vector<double> 
    sqrt(lila::Vector<double> const& a);
    template lila::Vector<std::complex<float>> 
    sqrt(lila::Vector<std::complex<float>> const& a);
    template lila::Vector<std::complex<double>> 
    sqrt(lila::Vector<std::complex<double>> const& a);
    template lila::Matrix<float> 
    sqrt(lila::Matrix<float> const& a);
    template lila::Matrix<double> 
    sqrt(lila::Matrix<double> const& a);
    template lila::Matrix<std::complex<float>> 
    sqrt(lila::Matrix<std::complex<float>> const& a);
    template lila::Matrix<std::complex<double>> 
    sqrt(lila::Matrix<std::complex<double>> const& a);



    template float abs(float const& a);
    template double abs(double const& a);
    template std::complex<float> abs(std::complex<float> const& a);
    template std::complex<double> abs(std::complex<double> const& a);
    template lila::Vector<float> 
    abs(lila::Vector<float> const& a);
    template lila::Vector<double> 
    abs(lila::Vector<double> const& a);
    template lila::Vector<std::complex<float>> 
    abs(lila::Vector<std::complex<float>> const& a);
    template lila::Vector<std::complex<double>> 
    abs(lila::Vector<std::complex<double>> const& a);
    template lila::Matrix<float> 
    abs(lila::Matrix<float> const& a);
    template lila::Matrix<double> 
    abs(lila::Matrix<double> const& a);
    template lila::Matrix<std::complex<float>> 
    abs(lila::Matrix<std::complex<float>> const& a);
    template lila::Matrix<std::complex<double>> 
    abs(lila::Matrix<std::complex<double>> const& a);


    template float norm(float const& a);
    template double norm(double const& a);
    template float norm(std::complex<float> const& a);
    template double norm(std::complex<double> const& a);
    template lila::Vector<float> 
    norm(lila::Vector<float> const& a);
    template lila::Vector<double> 
    norm(lila::Vector<double> const& a);
    template lila::Vector<float> 
    norm(lila::Vector<std::complex<float>> const& a);
    template lila::Vector<double> 
    norm(lila::Vector<std::complex<double>> const& a);
    template lila::Matrix<float> 
    norm(lila::Matrix<float> const& a);
    template lila::Matrix<double> 
    norm(lila::Matrix<double> const& a);
    template lila::Matrix<float> 
    norm(lila::Matrix<std::complex<float>> const& a);
    template lila::Matrix<double> 
    norm(lila::Matrix<std::complex<double>> const& a);


    template float
    accumulate(std::vector<float> const& vec);
    template double
    accumulate(std::vector<double> const& vec);
    template std::complex<float>
    accumulate(std::vector<std::complex<float>> const& vec);
    template std::complex<double>
    accumulate(std::vector<std::complex<double>> const& vec);
    template lila::Vector<float>
    accumulate(std::vector<lila::Vector<float>> const& vec);
    template lila::Vector<double>
    accumulate(std::vector<lila::Vector<double>> const& vec);
    template lila::Vector<std::complex<float>>
    accumulate(std::vector<lila::Vector<std::complex<float>>> const& vec);
    template lila::Vector<std::complex<double>>
    accumulate(std::vector<lila::Vector<std::complex<double>>> const& vec);
    template lila::Matrix<float>
    accumulate(std::vector<lila::Matrix<float>> const& vec);
    template lila::Matrix<double>
    accumulate(std::vector<lila::Matrix<double>> const& vec);
    template lila::Matrix<std::complex<float>>
    accumulate(std::vector<lila::Matrix<std::complex<float>>> const& vec);
    template lila::Matrix<std::complex<double>>
    accumulate(std::vector<lila::Matrix<std::complex<double>>> const& vec);

    template float infinity(float const& vec);
    template double infinity(double const& vec);
    template float infinity(std::complex<float> const& vec);
    template double infinity(std::complex<double> const& vec);
    template lila::Vector<float>
    infinity(lila::Vector<float> const& vec);
    template lila::Vector<double>
    infinity(lila::Vector<double> const& vec);
    template lila::Vector<float>
    infinity(lila::Vector<std::complex<float>> const& vec);
    template lila::Vector<double>
    infinity(lila::Vector<std::complex<double>> const& vec);
    template lila::Matrix<float>
    infinity(lila::Matrix<float> const& vec);
    template lila::Matrix<double>
    infinity(lila::Matrix<double> const& vec);
    template lila::Matrix<float>
    infinity(lila::Matrix<std::complex<float>> const& vec);
    template lila::Matrix<double>
    infinity(lila::Matrix<std::complex<double>> const& vec);

  }
}

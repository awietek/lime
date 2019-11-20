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


  }
}

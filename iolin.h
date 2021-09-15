#ifndef IOLIN_H
#define IOLIN_H

#include "linsys.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

template<class T>
std::istream &operator>>(std::istream &in, linsys::vector<T> &v)
{
	for (std::size_t i = 0; i < v.dim; ++i)
		in >> v[i];
	return in;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const linsys::vector<T> &v)
{
	for (std::size_t i = 0; i < v.dim; ++i)
		out << v[i] << std::endl;
	return out;
}

template<class T>
std::istream &operator>>(std::istream &in, linsys::matrix<T> &m)
{
	for (std::size_t i = 0; i < m.dim; ++i)
	{
		auto line = m[i];
		for (std::size_t j = 0; j < m.dim; ++j)
			in >> line[j];
	}
	return in;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const linsys::matrix<T> &m)
{
	for (std::size_t i = 0; i < m.dim; ++i)
	{
		auto line = m[i];
		for (std::size_t j = 0; j < m.dim; ++j)
			out << line[j] << " ";
		out << std::endl;
	}
	return out;
}

template<class T> struct formatter
{
	const T &data;
	std::ios::fmtflags fl;
	std::streamsize w, p;
};

template<class T>
formatter<T> make_formatter(const T &data, std::ios::fmtflags fl, std::streamsize w, std::streamsize p)
{
	return { data, fl, w, p };
}

template<class T>
std::ostream &operator<<(std::ostream &out, const formatter<linsys::vector<T>> &form)
{
	auto oldf = out.flags();
	auto oldp = out.precision();
	out.flags(form.fl);
	out.precision(form.p);
	
	const auto d = form.data.dim;
	for (std::size_t i = 0; i < d; ++i)
		out << std::setw(form.w) << form.data[i] << std::endl;
	
	out.flags(oldf);
	out.precision(oldp);
	
	return out;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const formatter<linsys::matrix<T>> &form)
{
	auto oldf = out.flags();
	auto oldp = out.precision();
	out.flags(form.fl);
	out.precision(form.p);
	
	const auto d = form.data.dim;
	for (std::size_t i = 0; i < d; ++i)
	{
		auto line = form.data[i];
		for (std::size_t j = 0; j < d; ++j)
			out << std::setw(form.w) << line[j];
		out << std::endl;
	}
	
	out.flags(oldf);
	out.precision(oldp);
	
	return out;
}

template<class T>
struct augmented
{
	linsys::matrix<T> &matr;
	linsys::vector<T> &vect;
	augmented(linsys::matrix<T> &m, linsys::vector<T> &v) : matr(m), vect(v)
	{
		if (m.dim != v.dim) throw std::invalid_argument("Mismatch of dimentions.");
	}
};

template<class T>
auto make_augmented(linsys::matrix<T> &m, linsys::vector<T> &v)
{
	return augmented<T>(m, v);
}

template<class T>
std::istream &operator>>(std::istream &in, const augmented<T> &augm)
{
	const auto d = augm.matr.dim;
	for (std::size_t i = 0; i < d; ++i)
	{
		auto line = augm.matr[i];
		for (std::size_t j = 0; j < d; ++j)
			in >> line[j];
		in >> augm.vect[i];
	}
	return in;
}

#endif
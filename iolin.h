#ifndef IOLIN_H
#define IOLIN_H

#include "linsys.h"
#include <iostream>
#include <iomanip>

template<std::size_t dim, class elem_type>
std::istream &operator>>(std::istream &in, linsys::vector<dim, elem_type> &v)
{
	for (std::size_t i = 0; i < dim; ++i)
		in >> v[i];
	return in;
}

template<std::size_t dim, class elem_type>
std::ostream &operator<<(std::ostream &out, const linsys::vector<dim, elem_type> &v)
{
	for (std::size_t i = 0; i < dim; ++i)
		out << v[i] << std::endl;
	return out;
}

template<std::size_t dim, class elem_type>
std::istream &operator>>(std::istream &in, linsys::matrix<dim, elem_type> &v)
{
	for (std::size_t i = 0; i < dim; ++i)
	{
		auto line = v[i];
		for (std::size_t j = 0; j < dim; ++j)
			in >> line[j];
	}
	return in;
}

template<std::size_t dim, class elem_type>
std::ostream &operator<<(std::ostream &out, const linsys::matrix<dim, elem_type> &v)
{
	for (std::size_t i = 0; i < dim; ++i)
	{
		auto line = v[i];
		for (std::size_t j = 0; j < dim; ++j)
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

template<std::size_t dim, class elem_type>
std::ostream &operator<<(std::ostream &out, const formatter<linsys::vector<dim, elem_type>> &form)
{
	auto oldf = out.flags();
	auto oldp = out.precision();
	out.flags(form.fl);
	out.precision(form.p);
	
	for (std::size_t i = 0; i < dim; ++i)
		out << std::setw(form.w) << form.data[i] << std::endl;
	
	out.flags(oldf);
	out.precision(oldp);
	
	return out;
}

template<std::size_t dim, class elem_type>
std::ostream &operator<<(std::ostream &out, const formatter<linsys::matrix<dim, elem_type>> &form)
{
	auto oldf = out.flags();
	auto oldp = out.precision();
	out.flags(form.fl);
	out.precision(form.p);
	
	for (std::size_t i = 0; i < dim; ++i)
	{
		auto line = form.data[i];
		for (std::size_t j = 0; j < dim; ++j)
			out << std::setw(form.w) << line[j];
		out << std::endl;
	}
	
	out.flags(oldf);
	out.precision(oldp);
	
	return out;
}

template<std::size_t dim, class elem_type>
struct augmented
{
	linsys::matrix<dim, elem_type> &matr;
	linsys::vector<dim, elem_type> &vect;
};

template<std::size_t dim, class elem_type>
augmented<dim, elem_type> make_augmented(
	linsys::matrix<dim, elem_type> &matr,
	linsys::vector<dim, elem_type> &vect
) {
	return { matr, vect };
}

template<std::size_t dim, class elem_type>
std::istream &operator>>(std::istream &in, const augmented<dim, elem_type> &augm)
{
	for (std::size_t i = 0; i < dim; ++i)
	{
		auto line = augm.matr[i];
		for (std::size_t j = 0; j < dim; ++j)
			in >> line[j];
		in >> augm.vect[i];
	}
	return in;
}

#endif
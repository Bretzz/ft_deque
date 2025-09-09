/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_iterator.tpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:58:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/09 16:39:12 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.hpp"

/* ========================================================================== */
/* ============================ CONSTR & DESTR ============================== */
/* ========================================================================== */

template <typename T, class Allocator>
ft_deque<T, Allocator>::iterator::iterator(void)
{
	_ptr = NULL;
	_base = NULL;
	_size = 0;
}

template <typename T, class Allocator>
ft_deque<T, Allocator>::iterator::iterator(pointer ptr, std::vector<pointer> *base, size_type *size, bool end):
	_ptr(ptr, CHUNK)
{
	_base = base;
	_size = size;
	_end = end;
}

template <typename T, class Allocator>
ft_deque<T, Allocator>::iterator::iterator(const ft_deque<T, Allocator>::iterator& __x):
	_ptr(__x._ptr)
{
	*this = __x;
}

template <typename T, class Allocator>
ft_deque<T, Allocator>::iterator::~iterator(void) {}

/* ========================================================================== */
/* =============================== METHODS =================================== */
/* ========================================================================== */

/* ========================================================================== */
/* ============================== OPERATORS ================================= */
/* ========================================================================== */

template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator&	ft_deque<T, Allocator>::iterator::operator=(const ft_deque<T, Allocator>::iterator& __x)
{
	if (this == &__x)
		return *this;

	_ptr = __x._ptr;
	_base = __x._base;
	_size = __x._size;
	_end = __x._end;
	return *this;
}

template <typename T, class Allocator>
typename ft_deque<T, Allocator>::reference	ft_deque<T, Allocator>::iterator::operator*(void)
{
	if (_end == true)
		throw std::out_of_range("ft_deque::iterator::operator*: end iterator");
	else
		return *_ptr;
}

/* INCR/DECR */

/* The std::find usage desn't invalidate the iterator if a pop_front deletes a cell
but slows things down */
/* pre-increment */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator&	ft_deque<T, Allocator>::iterator::operator++()
{
	if (_end == true)
		throw std::out_of_range("ft_deque::iterator::operator++: out_of_range");

	if (_ptr.pos() != CHUNK - 1)
		++_ptr;
	else
	{
		typename std::vector<pointer>::iterator it = std::find(_base->begin(), _base->end(), _ptr - _ptr.pos());
		if (it == --_base->end())
			_end = true;
		else
			_ptr = *(it + 1);
	}
	return *this;
}

/* post-increment */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::iterator::operator++(int)
{
	ft_deque<T, Allocator>::iterator old = this;

	if (_end == true)
		throw std::out_of_range("ft_deque::iterator::operator++: out_of_range");

	if (_ptr.pos() != CHUNK - 1)
		++_ptr;
	else
	{
		typename std::vector<pointer>::iterator it = std::find(_base->begin(), _base->end(), _ptr - _ptr.pos());
		if (it == --_base->end())
			_end = true;
		else
			_ptr = *(it + 1);
	}
	return old;
}

/* pre-decrement */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator&	ft_deque<T, Allocator>::iterator::operator--()
{
	if (_ptr.pos() != 0)
		--_ptr;
	else
	{
		typename std::vector<pointer>::iterator it = std::find(_base->begin(), _base->end(), _ptr.pos());
		if (it == _base->begin())
			throw std::out_of_range("ft_deque::iterator::operator--: out of range");
		_ptr.assign((*_base)[it - 1][(CHUNK - 1)], (CHUNK - 1));
	}
	return *this;
}

/* post-decrement */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::iterator::operator--(int)
{
	ft_deque<T, Allocator>::iterator old = this;

	if (_ptr.pos() != 0)
		--_ptr;
	else
	{
		typename std::vector<pointer>::iterator it = std::find(_base->begin(), _base->end(), _ptr.pos());
		if (it == _base->begin())
			throw std::out_of_range("ft_deque::iterator::operator--: out of range");
		_ptr.assign((*_base)[it - 1][(CHUNK - 1)], (CHUNK - 1));
	}
	return old;
}

/* COMPARISON */
template <typename T, class Allocator>
bool		ft_deque<T, Allocator>::iterator::operator==(const iterator &__x) const
{
	if (_ptr == __x._ptr && _end == __x._end)
		return true;
	else
		return false;
}

template <typename T, class Allocator>
bool		ft_deque<T, Allocator>::iterator::operator!=(const iterator &__x) const
{
	if (_ptr != __x._ptr || _end != __x._end)
		return true;
	else
		return false;
}

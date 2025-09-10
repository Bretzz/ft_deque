/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_iterator.tpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:58:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/10 02:31:00 by totommi          ###   ########.fr       */
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
ft_deque<T, Allocator>::iterator::iterator(idx_ptr ptr, std::vector<pointer> *base, idx_ptr *front, idx_ptr *back, size_type *size):
	_ptr(ptr)
{
	_base = base;
	_front = front;
	_back = back;
	_size = size;
}

template <typename T, class Allocator>
ft_deque<T, Allocator>::iterator::iterator(pointer ptr, std::vector<pointer> *base, idx_ptr *front, idx_ptr *back, size_type *size):
	_ptr(ptr, CHUNK)
{
	_base = base;
	_front = front;
	_back = back;
	_size = size;
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
	_front = __x._front;
	_back = __x._back;
	_size = __x._size;
	return *this;
}

template <typename T, class Allocator>
typename ft_deque<T, Allocator>::reference	ft_deque<T, Allocator>::iterator::operator*(void)
{
	if (_ptr == *_back)
		throw std::out_of_range("ft_deque::iterator::operator*: end iterator");
	else
		return *_ptr;
}

template <typename T, class Allocator>
typename ft_deque<T, Allocator>::const_reference	ft_deque<T, Allocator>::iterator::operator*(void) const
{
	if (_ptr == *_back)
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
	if (_ptr == *_back)
		throw std::out_of_range("ft_deque::iterator::operator++: out_of_range");

	if (_ptr.idx() != CHUNK - 1)
		++_ptr;	//just proceed
	else
		_ptr = *(std::find(_base->begin(), _base->end(), _ptr - _ptr.idx()) + 1); //jumps

	return *this;
}

/* post-increment */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::iterator::operator++(int)
{
	ft_deque<T, Allocator>::iterator old = *this;

	if (_ptr == *_back)
		throw std::out_of_range("ft_deque::iterator::operator++: out_of_range");

	if (_ptr.idx() != CHUNK - 1)
		++_ptr;	//just proceed
	else
		_ptr = *(std::find(_base->begin(), _base->end(), _ptr - _ptr.idx()) + 1); //jumps

	return old;
}

/* pre-decrement */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator&	ft_deque<T, Allocator>::iterator::operator--()
{
	if (_ptr.idx() != 0)
		--_ptr;
	else
	{
		typename std::vector<pointer>::iterator it = std::find(_base->begin(), _base->end(), _ptr);
		_ptr.assign(*(it - 1) + CHUNK - 1, (CHUNK - 1));
	}
	
	if (_ptr == *_front)
		throw std::out_of_range("ft_deque::iterator::operator--: out_of_range");

	return *this;
}

/* post-decrement */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::iterator::operator--(int)
{
	ft_deque<T, Allocator>::iterator old = *this;

	if (_ptr.idx() != 0)
		--_ptr;
	else
	{
		typename std::vector<pointer>::iterator it = std::find(_base->begin(), _base->end(), _ptr);
		_ptr.assign(*(it - 1) + CHUNK - 1, (CHUNK - 1));
	}
	
	if (_ptr == *_front)
		throw std::out_of_range("ft_deque::iterator::operator--: out_of_range");

	return old;
}

/* COMPARISON */
template <typename T, class Allocator>
bool		ft_deque<T, Allocator>::iterator::operator==(const iterator &__x) const
{
	if (_ptr == __x._ptr)
		return true;
	else
		return false;
}

template <typename T, class Allocator>
bool		ft_deque<T, Allocator>::iterator::operator!=(const iterator &__x) const
{
	if (_ptr != __x._ptr)
		return true;
	else
		return false;
}

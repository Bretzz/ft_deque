/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:56:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/10 02:53:20 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.hpp"
// #include <sys/types.h>
#include <cmath>		// std::abs

#include <iostream> /* REMOVE */
#include <strings.h>	// ::bzero
#include <algorithm>	// std::find

#include <stdexcept> //out_of_range

// static void	bzero(void *ptr, size_type n)
// {
// 	unsigned char *c_ptr = (unsigned char *)ptr;

// 	for (size_type i = 0; i < n; ++i) {
// 		c_ptr = 0;
// 		++c_ptr;
// 	}
// }

/* ==================================== */
/* =========== P R I N T E R ========== */
/* ==================================== */

template <typename T, class Allocator>
void ft_deque<T, Allocator>::print(void) const
{
	long long first = reinterpret_cast<long long>(_base[0]);
	for (size_type i = 0; i < _base.size(); ++i)
	{
		std::cout << "_base[" << i << "] : " << reinterpret_cast<long long>(_base[i]) - first;
		if (i == 0)
		{
			std::cout << " _front : " << _front.toLongLong() - first << std::endl;
			for (int j = 0; j < CHUNK; ++j)
			{
				std::cout << "\tcell[" << j << "] : " << reinterpret_cast<long long>(_base[i] + j) - first << " : ";
				int	f_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _front)) < CHUNK;
				int	b_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _back)) < CHUNK;
				if ((b_in_cell && _base[i] + j < _back && !f_in_cell)
					|| (f_in_cell && _base[i] + j > _front && !b_in_cell)
					|| (b_in_cell && _base[i] + j < _back && f_in_cell && _base[i] + j > _front))
						std::cout << "full" << std::endl;
				else if (_base[i] + j == _back || _base[i] + j == _front)
					std::cout << "- <-" << std::endl;
				else
					std::cout << "-" << std::endl;
			}
		}
		else if (i == _base.size() - 1)
		{
			std::cout << " _back : " << _back.toLongLong() - first << std::endl;
			for (int j = 0; j < CHUNK; ++j)
			{
				std::cout << "\tcell[" << j << "] : " << reinterpret_cast<long long>(_base[i] + j) - first << " : ";
				int	f_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _front)) < CHUNK;
				int	b_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _back)) < CHUNK;
				if ((b_in_cell && _base[i] + j < _back && !f_in_cell)
					|| (f_in_cell && _base[i] + j > _front && !b_in_cell)
					|| (b_in_cell && _base[i] + j < _back && f_in_cell && _base[i] + j > _front))
						std::cout << "full" << std::endl;
				else if (_base[i] + j == _back || _base[i] + j == _front)
					std::cout << "- <-" << std::endl;
				else
					std::cout << "-" << std::endl;
			}
		}
		else
		{
			std::cout << std::endl;
			for (int j = 0; j < CHUNK; ++j)
			{
				std::cout << "\tcell[" << j << "] : " << reinterpret_cast<long long>(_base[i] + j) - first << " : ";
				std::cout << "full" << std::endl;
			}
		}
	}
}

/* ========================================================================== */
/* ============================ CONSTR & DESTR ============================== */
/* ========================================================================== */

template <typename T, class Allocator>
ft_deque<T, Allocator>::ft_deque(void):
	_alloc()
{
	_base.push_back(_alloc.allocate(CHUNK));
	::bzero(_base[0], CHUNK * sizeof(T));
	_base.push_back(_alloc.allocate(CHUNK));
	::bzero(_base[1], CHUNK * sizeof(T));
	_front.assign(_base[0] + (CHUNK - 1), (CHUNK - 1));
	_back.assign(_base[1], 0);
	_size = 0;
}

template <typename T, class Allocator>
ft_deque<T, Allocator>::ft_deque(const ft_deque<T, Allocator> &__x)
{
	*this = __x;
}

/* The idea is to call _alloc.deallocate() on each pointer allocated
with _alloc.allocate(), and call _alloc.destroy() on each element of said
memory before deallocating
#todo destroy elements by order of insertion, regardless if
it was inserted with push_front of push_back */
template <typename T, class Allocator>
ft_deque<T, Allocator>::~ft_deque()
{
	/* destroys all the elements and deallocates
	all the cells but 2 */
	this->clear();

	/* deallocate the last 2 cells */
	_alloc.deallocate(_base[0], CHUNK);
	_alloc.deallocate(_base[1], CHUNK);
	_base.clear();
}

/* ========================================================================== */
/* =============================== METHODS ================================== */
/* ========================================================================== */

template <typename T, class Allocator>
void	ft_deque<T, Allocator>::clear(void)
{
	while (_base.size() > 2)
	{
		for (int i = 0; i < CHUNK; ++i)
		{
			_alloc.destroy(_base[1] + i);
		}
		_alloc.deallocate(_base[1], CHUNK);
		_base.erase(_base.begin() + 1);
	}
	/* clearing cell with _front*/
	{
		for (int j = _front.idx() + 1; j < CHUNK; ++j)
		{
			_alloc.destroy(_base[0] + j);
		}
	}
	/* clearing cell with _back */
	{
		for (int j = 0; j < _back.idx(); ++j)
		{
			_alloc.destroy(_base[1] + j);
		}
	}
	_size = 0;
	_front.assign(_base[0] + (CHUNK - 1), (CHUNK - 1));
	_back.assign(_base[1], 0);
}

template <typename T, class Allocator>
void	ft_deque<T, Allocator>::assign(size_type count, const T& value)
{
	/* clear all data */
	this->clear();
	
	for (size_type i = 0; i < count; ++i)
		this->push_back(value);
}

// template <typename T, class Allocator, class InputIt>
// void ft_deque<T, Allocator>::assign( InputIt first, InputIt last )
// {
// 	/* clear all data */
	// this->clear();

// 	while (first != last)
// 	{
// 		this->push_back(*first);
// 		++first;
// 	}
// }

template <typename T, class Allocator>
T&	ft_deque<T, Allocator>::back(void)
{
	if (_size == 0)
		throw std::out_of_range("ft_deque::back(): empty container");

	if (_back.idx() == 0)
		return *(*(_base.end() - 2) + (CHUNK - 1));
	else
		return *(_back - 1);
}

template <typename T, class Allocator>
T&	ft_deque<T, Allocator>::front(void)
{
	if (_size == 0)
		throw std::out_of_range("ft_deque::front(): empty container");

	if (_front.idx() == CHUNK - 1)
		return **((_base.begin() + 1));
	else
		return *(_front + 1);
}

/* = = = = = = = = = = = = = = = = = = = = */
/* = = = = =  ITERATOR FUNCTIONS = = = = = */
/* = = = = = = = = = = = = = = = = = = = = */

template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::begin(void)
{
	if (_front.idx() == CHUNK - 1)
		return ft_deque<T, Allocator>::iterator(&this->front(), &_base, &_front, &_back, &_size);
	else
		return ft_deque<T, Allocator>::iterator(++idx_ptr(_front), &_base, &_front, &_back, &_size);
}

template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::end(void)
{
	return ft_deque<T, Allocator>::iterator(_back, &_base, &_front, &_back, &_size);
}


/* NOTA: per ora vengono chiamati i distruttori a palla perche' copio
tutto aggiro :DDDDD, mo pero' si dorme, quindi #todo */
template <typename T, class Allocator>
typename ft_deque<T, Allocator>::iterator	ft_deque<T, Allocator>::insert(const_iterator __pos, const_reference __value)
{
	if (__pos == this->end())
	{
		this->push_back(__value);
		return --this->end();
	}
	value_type 							tmp = *__pos;
	value_type 							next;
	ft_deque<T, Allocator>::iterator	it = __pos;

	*it = __value;

	while (++it != this->end())
	{
		next = (*it);
		(*it) = tmp;
		tmp = next;
	}
	this->push_back(tmp);
	return __pos;
}

/* = = = = = = = = = = = = = = = = = = = = */
/* = = = DOUBLE END ACCESS FUNCTIONS = = = */
/* = = = = = = = = = = = = = = = = = = = = */

/* |0,0,0,0| -> |new|-> |1,2,3,4| */
/* _base[0] =  */

/* if back puntava all'inizio di una cella */
/* then alloca some more at the front */
template <typename T, class Allocator>
void	ft_deque<T, Allocator>::push_back(const_reference __x)
{
	/* assign value */
	*_back = __x;

	/* if we are at the end of a cell... */
	if (_back.idx() == CHUNK - 1)
	{
		/* and we are at the end of the deque */
		if (_base.size() > 2 || std::abs(_back - _base[1]) < static_cast<long>(CHUNK))
		{
			/* ...allocate new one */
			T *newcell = _alloc.allocate(CHUNK);
			::bzero(newcell, CHUNK * sizeof(T));
			_base.push_back(newcell);
			_back = newcell;
		}
		else
			_back = _base[1];
	}
	else
		++_back;
	++_size;
}

template <typename T, class Allocator>
void	ft_deque<T, Allocator>::pop_back(void)
{
	if (_size == 0)	/* maybe thorw exception */
		return ;
	
	/* if _back is an element at the front of a cell.. */
	if (_back.idx() == 0)
	{
		const typename std::vector<T *>::iterator	eraser = --_base.end();
		/* ...and there are more than 2 cells, */
		if (_base.size() > 2)
		{
			{
				/* delete the cell */
				_back.assign(*(eraser - 1) + (CHUNK - 1), (CHUNK - 1));
				_alloc.destroy(_back);
				_alloc.deallocate(*eraser, CHUNK);
				_base.erase(eraser);
			}
		}
		else	/* delete the element and jump */
		{
			_back.assign(*(eraser - 1) + (CHUNK - 1), (CHUNK - 1));
			_alloc.destroy(_back);
			::bzero(_back, sizeof(T));
		}
	}
	else	/* just delete the element */
	{
		--_back;
		// std::cout << "destroying " << _back->me() << std::endl;
		_alloc.destroy(_back);
		::bzero(_back, sizeof(T));
	}
	--_size;
}

template <typename T, class Allocator>
void	ft_deque<T, Allocator>::push_front(const_reference __x)
{
	/* assign value */
	*_front = __x;
	
	/* if _front is an element at the 'front' of a cell */
	if (_front.idx() == 0)
	{
		if (_base.size() > 2 || std::abs(_front - _base[0]) < static_cast<long>(CHUNK))
		{
			/* allocate new cell */
			T *newcell = _alloc.allocate(CHUNK);
			::bzero(newcell, CHUNK * sizeof(T));
			_base.insert(_base.begin(), newcell);
			_front.assign(newcell + (CHUNK -1), (CHUNK - 1));
		}
		else
			_front.assign(_base[0] + (CHUNK - 1), (CHUNK - 1));
	}
	else
		--_front;
	++_size;
}

template <typename T, class Allocator>
void	ft_deque<T, Allocator>::pop_front(void)
{
	if (_size == 0)	/* maybe thorw exception */
		return ;
	
	/* if _front is an element at the back of a cell.. */
	if (_front.idx() == CHUNK - 1)
	{
		/* ... and there are more than 2 cells, */
		if (_base.size() > 2)
		{
			{
				/* delete the cell */
				_front = *(_base.begin() + 1);
				// std::cout << "destroying3 " << _front->me() << std::endl;
				_alloc.destroy(_front);
				_alloc.deallocate(*_base.begin(), CHUNK);
				_base.erase(_base.begin());
			}
		}
		else	/* delete the element and jump */
		{
			// std::cout << "2cells jump destroy" << std::endl;
			_front = *(_base.begin() + 1);
			// std::cout << "destroying2 " << _front->me() << std::endl;
			_alloc.destroy(_front);
			::bzero(_front, sizeof(T));
		}
	}
	else	/* just delete the element */
	{
		++_front;
		// std::cout << "destroying " << _front->me() << std::endl;
		_alloc.destroy(_front);
		::bzero(_front, sizeof(T));
	}
	--_size;
}

/* ========================================================================== */
/* ============================== OPERATORS ================================= */
/* ========================================================================== */

/* the idea is that you just calculate the index with a sum,
then check if you passed some chunk, if so, jump and repeat */
/* ! ! ! IMPOROVABLE ! ! !
too mucch cheks */
template <typename T, class Allocator>
T&			ft_deque<T, Allocator>::operator[](int __idx)
{
	if (__idx < 0)
		throw std::out_of_range("ft_deque::operator[]: negative index");

	if (static_cast<size_type>(__idx) >= _size)
		throw std::out_of_range("ft_deque::operator[]: out of range");
	
	long	offset;
	if (_base.size() == 2 && std::abs(reinterpret_cast<long>(_back - _front)) < CHUNK)
		return *(_front + __idx + 1);
	else
		offset = _front.idx() + 1;

	return *(_base[(__idx + offset) / CHUNK] + (__idx + offset) % CHUNK);		/* SGRAVOOOO */
}

template <typename T, class Allocator>
const T&	ft_deque<T, Allocator>::operator[](int __idx) const
{
	if (__idx < 0)
		throw std::out_of_range("ft_deque::operator[]: negative index");

	if (static_cast<size_type>(__idx) >= _size)
		throw std::out_of_range("ft_deque::operator[]: out of range");
	
	long	offset;
	if (_base.size() == 2 && std::abs(reinterpret_cast<long>(_back - _front)) < CHUNK)
		return *(_front + __idx + 1);
	else
		offset = _front.idx() + 1;

	return *(_base[(__idx + offset) / CHUNK] + (__idx + offset) % CHUNK);
}

template <typename T, class Allocator>
ft_deque<T, Allocator>& ft_deque<T, Allocator>::operator=(const ft_deque<T, Allocator> &__x)
{
	if (this == &__x)
		return *this;

	/* clear all data */
	this->clear();

	for (size_type i = 0; i < __x.size(); ++i)
		this->push_back(__x[i]);

	return *this;
}

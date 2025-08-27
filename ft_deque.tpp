/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:56:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/27 12:48:05 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.hpp"
#include <sys/types.h>
#include <cmath>

#include <iostream> /* REMOVE */

// static void	bzero(void *ptr, size_type n)
// {
// 	unsigned char *c_ptr = (unsigned char *)ptr;

// 	for (size_type i = 0; i < n; ++i) {
// 		c_ptr = 0;
// 		++c_ptr;
// 	}
// }

template <typename T, class Allocator>
void ft_deque<T, Allocator>::print(void) const
{
	long long first = reinterpret_cast<long long>(_base[0]);
	for (size_type i = 0; i < _base.size(); ++i)
	{
		std::cout << "_base[" << i << "] : " << reinterpret_cast<long long>(_base[i]) - first;
		if (i == 0)
		{
			std::cout << " _front : " << reinterpret_cast<long long>(_front) - first << std::endl;
			for (int j = 0; j < CHUNK; ++j)
			{
				std::cout << "\tcell[" << j << "] : " << reinterpret_cast<long long>(_base[i] + j) - first << " : ";
				int	f_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _front)) < static_cast<long>(CHUNK * sizeof(T));
				int	b_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _back)) < static_cast<long>(CHUNK * sizeof(T));
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
			std::cout << " _back : " << reinterpret_cast<long long>(_back) - first << std::endl;
			for (int j = 0; j < CHUNK; ++j)
			{
				std::cout << "\tcell[" << j << "] : " << reinterpret_cast<long long>(_base[i] + j) - first << " : ";
				int	f_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _front)) < static_cast<long>(CHUNK * sizeof(T));
				int	b_in_cell = std::abs(reinterpret_cast<long>(_base[i] - _back)) < static_cast<long>(CHUNK * sizeof(T));
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
	_front = _base[0] + (CHUNK - 1);
	_back = _base[1];
	_size = 0;
}

template <typename T, class Allocator>
ft_deque<T, Allocator>::ft_deque(const ft_deque<T, Allocator> &__x)
{
	*this = __x;
}

/* The idea is to call _alloc.deallocate() on each pointer allocated
with _alloc.allocate(), and call _alloc.destroy() on each element of said
memory before deallocating */
template <typename T, class Allocator>
ft_deque<T, Allocator>::~ft_deque()
{
	if (_base.size() == 2)
	{
		T	*eraser;
		/* _front e _back nella stessa cella */
		if (std::abs(reinterpret_cast<long long>(_front) - reinterpret_cast<long long>(_back)) < static_cast<long long>(CHUNK * sizeof(T)))
		{
			eraser = _front + 1;
			while (eraser < _back)
			{
				_alloc.destroy(eraser);
				++eraser;
			}
		}
		else
		{
			eraser = _front + 1;
			while (eraser <= _base[0] + (CHUNK - 1))
			{
				_alloc.destroy(eraser);
				++eraser;
			}
			eraser = _back - 1;
			while (eraser >= _base[1])
			{
				_alloc.destroy(eraser);
				--eraser;
			}
		}
		/* deallocate the first 2 elements */
		_alloc.deallocate(_base[0], CHUNK);
		_alloc.deallocate(_base[1], CHUNK);
		_base.clear();
	}
	else
	{
		for (size_type i = 0; i < _base.size(); ++i)
		{
			/* destroys cell with _front */
			if (i == 0)
			{
				for (int j = 0; j < CHUNK; ++j)
				{
					if (_base[i] + j > _front)
						_alloc.destroy(_base[i] + j);
				}
			}
			/* destroys cell with _back */
			else if (i == _base.size() - 1)
			{
				for (int j = 0; j < CHUNK; ++j)
				{
					if (_base[i] + j < _back)
						_alloc.destroy(_base[i] + j);
				}
			}
			else
			{
				for (int j = 0; j < CHUNK; ++j)
				{
					_alloc.destroy(_base[i] + j);
				}
			}
			
			// for (int j = 0; j < CHUNK; ++j)
			// {
			// 	if ((_front < _base[i] + j && reinterpret_cast<uintptr_t>(_base[i] + j) - reinterpret_cast<uintptr_t>(_front) < CHUNK * sizeof(T))
			// 		|| (_back > _base[i] + j && reinterpret_cast<uintptr_t>(_back) - reinterpret_cast<uintptr_t>(_base[i] + j) < CHUNK * sizeof(T))
			// 		|| (_front > _base[i] + j && reinterpret_cast<uintptr_t>(_front) - reinterpret_cast<uintptr_t>(_base[i] + j) > CHUNK * sizeof(T))
			// 		|| (_back < _base[i] + j &&  reinterpret_cast<uintptr_t>(_base[i] + j) - reinterpret_cast<uintptr_t>(_back)> CHUNK * sizeof(T)))
			// 		_alloc.destroy(_base[i] + j);	/* calls the destructor of the element */
			// }

			/* deallocate the memory of element */
			_alloc.deallocate(_base[i], CHUNK);
		}
		_base.clear();
	}
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
		for (int j = 0; j < CHUNK; ++j)
		{
			if (_base[0] + j > _front)
				_alloc.destroy(_base[0] + j);
		}
	}
	/* clearing cell with _back */
	{
		for (int j = 0; j < CHUNK; ++j)
		{
			if (_base[1] + j < _back)
				_alloc.destroy(_base[1] + j);
		}
	}
	_size = 0;
	_front = _base[0] + (CHUNK - 1);
	_back = _base[1];
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

#include <stdexcept>

template <typename T, class Allocator>
T&	ft_deque<T, Allocator>::back(void)
{
	if (_size == 0)
		throw std::out_of_range("ft_deque::back(): empty container");

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _back);
	
	if (it != _base.end())
		return *(*(it - 1) + (CHUNK - 1));
	else
		return *(_back - 1);
}

template <typename T, class Allocator>
T&	ft_deque<T, Allocator>::front(void)
{
	if (_size == 0)
		throw std::out_of_range("ft_deque::front(): empty container");

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _front - (CHUNK - 1));
	
	if (it != _base.end())
		return **(it + 1);
	else
		return *(_front + 1);
}

/* = = = = = = = = = = = = = = = = = = = = */
/* = = = DOUBLE END ACCESS FUNCTIONS = = = */
/* = = = = = = = = = = = = = = = = = = = = */

#include <algorithm>

/* |0,0,0,0| -> |new|-> |1,2,3,4| */
/* _base[0] =  */

/* if back puntava all'inizio di una cella */
/* then alloca some more at the front */
template <typename T, class Allocator>
void	ft_deque<T, Allocator>::push_back(const T &__x)
{
	/* assign value */
	*_back = __x;

	/* if we are at the end of a cell... */
	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _back - (CHUNK - 1));

	/* ...allocate new one */
	if (it != _base.end())
	{
		T *newcell = _alloc.allocate(CHUNK);
		::bzero(newcell, CHUNK * sizeof(T));
		_base.insert(it + 1, newcell);
		_back = newcell;
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

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _back);
	
	/* if _back is an element at the front of a cell.. */
	if (it != _base.end())
	{
		/* ...and there are more than 2 cells, */
		if (_base.size() > 2)
		{
			{
				/* delete the cell */
				_back = *(it - 1) + (CHUNK - 1);
				_alloc.destroy(_back);
				_alloc.deallocate(*it, CHUNK);
				_base.erase(it);
			}
		}
		else	/* delete the element and jump */
		{
			_back = *(it - 1) + (CHUNK - 1);
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
void	ft_deque<T, Allocator>::push_front(const T &__x)
{
	/* assign value */
	*_front = __x;

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _front);
	
	/* if _front is an element at the 'front' of a cell */
	if (it != _base.end())
	{
		/* allocate new cell */
		T *newcell = _alloc.allocate(CHUNK);
		::bzero(newcell, CHUNK * sizeof(T));
		_base.insert(it, newcell);
		_front = newcell + (CHUNK -1);
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

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _front - (CHUNK - 1));
	
	/* if _front is an element at the back of a cell.. */
	if (it != _base.end())
	{
		/* ... and there are more than 2 cells, */
		if (_base.size() > 2)
		{
			{
				/* delete the cell */
				_front = *(it + 1);
				// std::cout << "destroying3 " << _front->me() << std::endl;
				_alloc.destroy(_front);
				_alloc.deallocate(*it, CHUNK);
				_base.erase(it);
			}
		}
		else	/* delete the element and jump */
		{
			std::cout << "2cells jump destroy" << std::endl;
			_front = *(it + 1);
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
	if (_base.size() == 2 && std::abs(offset = reinterpret_cast<long>(_front - _base[1])) < static_cast<long>(CHUNK * sizeof(T)))
		offset = CHUNK + offset + 1;
	else
		offset = reinterpret_cast<long>(_front - _base[0]) + 1;

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
	if (_base.size() == 2 && std::abs(offset = reinterpret_cast<long>(_front - _base[1])) < static_cast<long>(CHUNK * sizeof(T)))
		offset = CHUNK + offset + 1;
	else
		offset = reinterpret_cast<long>(_front - _base[0]) + 1;

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

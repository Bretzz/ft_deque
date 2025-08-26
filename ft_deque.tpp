/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:56:35 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/26 23:13:48 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.hpp"
#include <sys/types.h>
#include <cmath>

#include <iostream> /* REMOVE */

static void	bzero(void *ptr, size_t n)
{
	unsigned char *c_ptr = (unsigned char *)ptr;

	for (size_t i = 0; i < n; ++i) {
		c_ptr = 0;
		++c_ptr;
	}
}

/* ========================================================================== */
/* ============================ CONSTR & DESTR ============================== */
/* ========================================================================== */

template <typename T, class _Allocator>
ft_deque<T, _Allocator>::ft_deque(void):
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

// template <typename T, class _Allocator>
// ft_deque<T, _Allocator>::ft_deque(const ft_deque<T, _Allocator> &__x)
// {
// 	/* #todo */
// }

// template <typename T, class _Allocator>
// ft_deque<T, _Allocator>& ft_deque<T, _Allocator>::operator=(const ft_deque<T, _Allocator>&)
// {
// 	/* #todo */
// }

template <typename T, class _Allocator>
ft_deque<T, _Allocator>::~ft_deque()
{
	if (_base.size() == 2)
	{
		T	*rullocompressore;
		/* _front e _back nella stessa cella */
		if (std::abs(reinterpret_cast<long long>(_front) - reinterpret_cast<long long>(_back)) < static_cast<long long>(CHUNK * sizeof(T)))
		{
			rullocompressore = _front + 1;
			while (rullocompressore < _back)
			{
				_alloc.destroy(rullocompressore);
				++rullocompressore;
			}
		}
		else
		{
			rullocompressore = _front + 1;
			while (rullocompressore <= _base[0] + (CHUNK - 1))
			{
				_alloc.destroy(rullocompressore);
				++rullocompressore;
			}
			rullocompressore = _back - 1;
			while (rullocompressore >= _base[1])
			{
				_alloc.destroy(rullocompressore);
				--rullocompressore;
			}
		}
		/* deallocate the first 2 elements */
		_alloc.deallocate(_base[0], CHUNK);
		_alloc.deallocate(_base[1], CHUNK);
	}
	else
	{
		for (size_t i = 0; i < _base.size(); ++i)
		{
			for (int j = 0; j < CHUNK; ++j)
			{
				if ((_front < _base[i] + j && reinterpret_cast<uintptr_t>(_base[i] + j) - reinterpret_cast<uintptr_t>(_front) < CHUNK * sizeof(T))
					|| (_back > _base[i] + j && reinterpret_cast<uintptr_t>(_back) - reinterpret_cast<uintptr_t>(_base[i] + j) < CHUNK * sizeof(T))
					|| (_front > _base[i] + j && reinterpret_cast<uintptr_t>(_front) - reinterpret_cast<uintptr_t>(_base[i] + j) > CHUNK * sizeof(T))
					|| (_back < _base[i] + j &&  reinterpret_cast<uintptr_t>(_base[i] + j) - reinterpret_cast<uintptr_t>(_back)> CHUNK * sizeof(T)))
					_alloc.destroy(_base[i] + j);	/* calls the destructor of the element */
			}
			_alloc.deallocate(_base[i], CHUNK);		/* deallocate the memory of element */
		}
	}
}

/* ========================================================================== */
/* =============================== METHODS =================================== */
/* ========================================================================== */
template <typename T, class _Allocator>
size_t	ft_deque<T, _Allocator>::size(void) const {return _size;}

#include <algorithm>

/* |0,0,0,0| -> |new|-> |1,2,3,4| */
/* _base[0] =  */

/* if back puntava all'inizio di una cella */
/* then alloca some more at the front */
template <typename T, class _Allocator>
void	ft_deque<T, _Allocator>::push_back(const T &__x)
{
	/* assign value */
	*_back = __x;

	/* allocate new cell */
	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _back - (CHUNK - 1));

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

template <typename T, class _Allocator>
void	ft_deque<T, _Allocator>::pop_back(void)
{
	if (_size == 0)	/* maybe thorw exception */
		return ;

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _back);
	
	/* if _back is an element at the front of a cell.. */
	if (it != _base.end())
	{
		if (_base.size() > 2)
		{
			/* ... and not the first cell, */
			if (it != _base.begin() + 1)
			{
				/* delete the cell */
				_back = *(it - 1) + (CHUNK - 1);
				_alloc.destroy(_back);
				_alloc.deallocate(*it, CHUNK);
				_base.erase(it);
			}
		}
		else
		{
			_back = *(it - 1) + (CHUNK - 1);
			_alloc.destroy(_back);
			::bzero(_back, sizeof(T));
		}
	}
	else
	{
		--_back;
		// std::cout << "destroying " << _back->me() << std::endl;
		_alloc.destroy(_back);
		::bzero(_back, sizeof(T));
	}
	--_size;
}

template <typename T, class _Allocator>
void	ft_deque<T, _Allocator>::push_front(const T &__x)
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

template <typename T, class _Allocator>
void	ft_deque<T, _Allocator>::pop_front(void)
{
	if (_size == 0)	/* maybe thorw exception */
		return ;

	const typename std::vector<T *>::iterator it = std::find(_base.begin(), _base.end(), _front - (CHUNK - 1));
	
	/* if _front is an element at the back of a cell.. */
	if (it != _base.end())
	{
		/* ... and not the first cell, */
		if (_base.size() > 2)
		{
			std::cout << "multiple cells " << _base.size() << std::endl;
			// if (it != _base.begin())
			{
				/* delete the cell */
				_front = *(it + 1);
				std::cout << "destroying3 " << _front->me() << std::endl;
				_alloc.destroy(_front);
				_alloc.deallocate(*it, CHUNK);
				_base.erase(it);
			}
		}
		else
		{
			_front = *(it + 1);
			std::cout << "destroying2 " << _front->me() << std::endl;
			_alloc.destroy(_front);
			::bzero(_front, sizeof(T));
		}
	}
	else
	{
		++_front;
		std::cout << "destroying " << _front->me() << std::endl;
		_alloc.destroy(_front);
		::bzero(_front, sizeof(T));
	}
	--_size;
}

/* ========================================================================== */
/* ============================== OPERATORS ================================= */
/* ========================================================================== */
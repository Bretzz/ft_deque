/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:14:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/27 02:45:31 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE
# define FT_DEQUE

# include <sys/types.h>
# include <vector>

# define CHUNK 4

typedef unsigned long uintptr_t;

template <typename T, class Allocator = std::allocator<T> >
class ft_deque
{
	public:
		/* MEMBER TYPES */
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef std::size_t								size_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
	
	private:
		allocator_type		_alloc;
		T*					_back;
		T*					_front;

	protected:
		std::vector<T *>	_base;
		size_t				_size;

	public:
		ft_deque();
		ft_deque(const ft_deque<T, Allocator>&);
		~ft_deque();

		/* === METHODS === */
		void					assign(size_type, const T&);
		// void					assign(InputIt, InputIt);
		ft_deque<T, Allocator>&	operator=(const ft_deque<T, Allocator>&);
		allocator_type			get_allocator() const {return _alloc;}

		/* MEMORY ADDRESS DEBUG */
		void	print(void) const;

		/* Element access */
		const T&	at(int __idx) const {return (*this)[__idx];}
		T&			back(void);
		T&			front(void);

		/* Capacity */
		bool		empty(void) const {return __size != 0 ? true : false;}
		size_type	size(void) const {return _size;}

		/* Modifiers */
		void		clear(void);
		// iterator insert( const_iterator pos, const T& value );
		// iterator erase( iterator pos );
		void		push_back(const T&);
		void		pop_back(void);
		void		push_front(const T&);
		void		pop_front(void);

		/* === OPERATORS === */
		T&			operator[](int);
		const T&	operator[](int) const;
	
		/* === ITERATOR === */
		// class iterator
		// {
		// 	private:
		// 		T					*_ptr;
		// 		std::vector<T*>		*_base;

		// 	public:

		// 	/* RAW */
		// 	T*	base(void) const;

		// 	/* CONSTRUCTOR */
		// 	iterator();
		// 	iterator(const iterator&);
		// 	~iterator();
		// 	// iterator(const typename std::deque<T, Allocator>::iterator&);
		// 	// iterator(T*, std::map<T*, T*>*, std::map<T*, T*>*);

		// 	/* ASSIGN */
		// 	iterator&	operator=(const iterator&);
		// 	// iterator&	operator+=(int);
		// 	// iterator&	operator-=(int);

		// 	/* DEREFERENCE */
		// 	T&	operator*(void);

		// 	/* INCR/DECR */
		// 	iterator&	operator++();		// pre-increment
		// 	iterator	operator++(int);	// post-incremet
		// 	iterator&	operator--();		// pre-decrement
		// 	iterator	operator--(int);	// post-decrement

		// 	/* COMPARISON */
		// 	bool		operator==(const iterator&) const;
		// 	bool		operator!=(const iterator&) const;

		// };

		// iterator	begin(void);
		// iterator	end(void);
};

# include "ft_deque.tpp"

#endif
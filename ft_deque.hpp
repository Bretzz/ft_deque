/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:14:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/08 20:56:14 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE
# define FT_DEQUE

# include <sys/types.h>
# include <vector>

# define CHUNK 4	/* number of elements in each cell */

typedef unsigned long uintptr_t;

/* A standard container which offers fixed time access to individual elements in any order.

Template Parameters:
@param T Type of element.
@param Alloc Allocator type, defaults to allocator<T>.

You already know what a deque is man, this is my implementation, wich is still
incomplete, but im doing my best :D

#todo

 - check the 'standard container' requierements
 
 - instead of pointers just store (cell,position) of the next slot to insert*/
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
		/* object used to allocate(), destroy() and deallocate() memory. */
		allocator_type		_alloc;
		/* pointer to the next free memory slot at the back of the deque */
		T*					_back;
		/* pointer to the next free memory slot at the front of the deque */
		T*					_front;

	protected:
		/* vector of pointers to the single cells of the deque */
		std::vector<T *>	_base;
		/* number of elements added to the deque, different from
		the number of elements allocated. */
		size_type			_size;

	public:
		/* Constructs the allocator and allocates two empty cells of 4 elements each,
		then ::bzero()s them and store them in _base.
		@note the deque will always have at least 2 cells allocated. */
		ft_deque();
		ft_deque(const ft_deque<T, Allocator>&);
		~ft_deque();

		/* === METHODS === */

		/* @param size number of elements
		@param elem reference to the element

		Description: clear the deque and push_back() size numbers of elem */
		void					assign(size_type, const T&);
		// void					assign(InputIt, InputIt);
		ft_deque<T, Allocator>&	operator=(const ft_deque<T, Allocator>&);
		allocator_type			get_allocator() const {return _alloc;}

		/* MEMORY ADDRESS DEBUG */
		void		print(void) const;

		/* Element access */

		/* @param __idx index of the element

		It's just a wrapper for the [] operator actually... */
		const T&	at(int __idx) const {return (*this)[__idx];}
		/* @return a reference to the last element of the deque.
		@throw out_or_range if the deque is empty. */
		T&			back(void);
		/* @return a reference to the first element of the deque.
		@throw out_or_range if the deque is empty. */
		T&			front(void);

		/* Capacity */

		/* @return TRUE: the deque has no elements yet, FALSE: at least one
		element as been added */
		bool		empty(void) const {return _size != 0 ? true : false;}
		/* @return the number of elements added so far */
		size_type	size(void) const {return _size;}

		/* Modifiers */

		/* destroys all elements added and deallocates all the cells but
		the first two, leaving front/back at the end/beginning
		of the first/second cell*/
		void		clear(void);
		// iterator insert( const_iterator pos, const T& value );	#todo
		// iterator erase( iterator pos );							#todo
		/* @param __x value to add

		Adds an element at the end of the deque, allocating
		a new cell if the element just filled one.  */
		void		push_back(const T&);
		/* destroys the last element of the deque, deallocating
		the cell if it's empty and the cell count is more than two */
		void		pop_back(void);
		/* @param __x value to add

		Adds an element at the front of the deque, allocating
		a new cell if the element just filled one. */
		void		push_front(const T&);
		/* destroys the first element of the deque, deallocating
		the cell if it's empty and the cell count is more than two */
		void		pop_front(void);

		/* === OPERATORS === */

		/* @param __idx index of the element

		@return a reference to the element at the index passed,
		@throw out_or_range if __idx is grather than the size of the deque */
		T&			operator[](int);
		/* @param __idx index of the element

		@return a reference to the element at the index passed,
		@throw out_or_range if __idx is grather than the size of the deque */
		const T&	operator[](int) const;
	
		/* === ITERATOR === */

		class iterator
		{
			private:
				T				*_ptr;
				std::vector<T*>	*_base;
				size_type		*_size;
			
			protected:
				iterator(std::vector<T*> *base, size_type size);

			public:

			/* RAW */

			T*	base(void) const;

			/* CONSTRUCTOR */

			iterator();
			iterator(const iterator&);
			~iterator();
			// iterator(const typename std::deque<T, Allocator>::iterator&);
			// iterator(T*, std::map<T*, T*>*, std::map<T*, T*>*);

			/* ASSIGN */
			iterator&	operator=(const iterator&);
			// iterator&	operator+=(int);
			// iterator&	operator-=(int);

			/* DEREFERENCE */

			T&	operator*(void);

			/* INCR/DECR */
			iterator&	operator++();		// pre-increment
			iterator	operator++(int);	// post-incremet
			iterator&	operator--();		// pre-decrement
			iterator	operator--(int);	// post-decrement

			/* COMPARISON */

			bool		operator==(const iterator&) const;
			bool		operator!=(const iterator&) const;

		};

		iterator	begin(void);
		iterator	end(void);
};

# include "ft_deque.tpp"

#endif
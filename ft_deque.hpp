/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:14:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/10 02:32:31 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE
# define FT_DEQUE

# include <sys/types.h>
# include <stddef.h>
# include <vector>

# define CHUNK 4	/* number of elements in each cell */

typedef unsigned long uintptr_t;

/* === INDEXD POINTER === */

/* just a ptr that knows how many times it has been incremented
@param T the type of element we are pointing to*/
template <typename T>
class iptr
{
	private:
		T*			_ptr;
		int			_idx;

	public:
		iptr(): _ptr(NULL), _idx(0) {}
		iptr(T* __ptr): _ptr(__ptr), _idx(0) {}
		iptr(T* __ptr, int __idx): _ptr(__ptr), _idx(__idx) {}
	
		/* IMPLICIT CONVERTION */
		operator T*() const {return _ptr;}

		/* DEREFERENCE */
		T&	operator*() {return *_ptr;}
		T*	operator->() const { return _ptr; }

		/* ASSIGNMENT */
		iptr&	operator=(T* __x) {_ptr = __x; _idx = 0; return *this;}
		iptr&	operator=(const iptr &__x) {_ptr = __x._ptr; _idx = __x._idx; return *this;}
		iptr&	assign(T* __x, int idx) {_ptr = __x; _idx = idx; return *this;}

		/* OPERATIONS */
		iptr&		operator++() {++_ptr; ++_idx; return *this;}
		iptr&		operator--() {--_ptr; --_idx; return *this;}
		iptr		operator+(int __idx) {return iptr<T>(_ptr + __idx, _idx + __idx);}
		iptr		operator-(int __idx) {return iptr<T>(_ptr - __idx, _idx - __idx);}

		int			idx(void) const {return _idx;}
		long long	toLongLong() const {return reinterpret_cast<long long>(_ptr);}
};

/* A standard container which offers fixed time access to individual elements in any order.

Template Parameters:
@param T Type of element.
@param Alloc Allocator type, defaults to allocator<T>.

You already know what a deque is man, this is my implementation, wich is still
incomplete, but im doing my best :D

#todo

 - check the 'standard container' requierements
 
 - _front/_back: instead of pointers just store (cell,position) of the next slot to insert*/
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
		typedef iptr<T>									idx_ptr;
	
	private:
		/* object used to allocate(), destroy() and deallocate() memory. */
		allocator_type		_alloc;
		/* pointer to the next free memory slot at the back of the deque */
		idx_ptr				_back;
		/* pointer to the next free memory slot at the front of the deque */
		idx_ptr				_front;

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
		void					assign(size_type, const_reference);
		// void					assign(InputIt, InputIt);				#todo
		ft_deque<T, Allocator>&	operator=(const ft_deque<T, Allocator>&);
		allocator_type			get_allocator() const {return _alloc;}

		/* MEMORY ADDRESS DEBUG */
		void		print(void) const;

		/* Element access */

		/* @param __idx index of the element

		It's just a wrapper for the [] operator actually... */
		const_reference	at(int __idx) const {return (*this)[__idx];}
		/* @return a reference to the last element of the deque.
		@throw out_or_range if the deque is empty. */
		reference		back(void);
		/* @return a reference to the first element of the deque.
		@throw out_or_range if the deque is empty. */
		reference		front(void);

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
		/* @param __x value to add

		Adds an element at the end of the deque, allocating
		a new cell if the element just filled one.  */
		void		push_back(const_reference);
		/* destroys the last element of the deque, deallocating
		the cell if it's empty and the cell count is more than two */
		void		pop_back(void);
		/* @param __x value to add

		Adds an element at the front of the deque, allocating
		a new cell if the element just filled one. */
		void		push_front(const_reference);
		/* destroys the first element of the deque, deallocating
		the cell if it's empty and the cell count is more than two */
		void		pop_front(void);

		/* === OPERATORS === */

		/* @param __idx index of the element

		@return a reference to the element at the index passed,
		@throw out_or_range if __idx is grather than the size of the deque */
		reference			operator[](int);
		/* @param __idx index of the element

		@return a reference to the element at the index passed,
		@throw out_or_range if __idx is grather than the size of the deque */
		const_reference	operator[](int) const;
	
		/* === ITERATOR === */

		class iterator
		{
			/* ALLOWING ACCES TO iterator 'private:' AND 'protected:' */
			public:
				friend class ft_deque<T, Allocator>;

			private:
				idx_ptr					_ptr;
				std::vector<pointer>	*_base;
				size_type				*_size;
				idx_ptr					*_front;
				idx_ptr					*_back;
			
			protected:
				iterator(idx_ptr, std::vector<pointer>*, idx_ptr*, idx_ptr*, size_type*);
				iterator(pointer, std::vector<pointer>*, idx_ptr*, idx_ptr*, size_type*);

			public:

				/* RAW */

				pointer	base(void) const {return _ptr;};

				/* CONSTRUCTOR */

				iterator();
				iterator(const iterator&);
				~iterator();
				// iterator(const typename std::deque<T, Allocator>::iterator&);

				/* ASSIGNMENT */

				iterator&	operator=(const iterator&);
				// iterator&	operator+=(int);
				// iterator&	operator-=(int);

				/* DEREFERENCE */

				reference		operator*(void);
				const_reference	operator*(void) const;	//cannot modify the content if it's a const iterator

				/* INCR/DECR */
				iterator&	operator++();		// pre-increment
				iterator	operator++(int);	// post-incremet
				iterator&	operator--();		// pre-decrement
				iterator	operator--(int);	// post-decrement

				/* COMPARISON */

				bool		operator==(const iterator&) const;
				bool		operator!=(const iterator&) const;
		};

		/* ITERATOR FUNCTIONS */

		typedef const iterator	const_iterator;

		iterator	begin(void);
		iterator	end(void);

		iterator	insert(const_iterator, const_reference);	// #todo
		// iterator erase( iterator pos );						// #todo
};

# include "ft_deque.tpp"
# include "ft_deque_iterator.tpp"

#endif
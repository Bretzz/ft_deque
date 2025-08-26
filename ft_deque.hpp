/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:14:41 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/26 21:11:25 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE
# define FT_DEQUE

# include <sys/types.h>
# include <vector>

# define CHUNK 4

typedef unsigned long uintptr_t;

template <typename T, class _Allocator = std::allocator<T> >
class ft_deque
{
	// # define TULL reinterpret_cast<T*>(0)

	private:
		_Allocator			_alloc;
		T*					_back;
		T*					_front;	

	protected:
		// T*					_base;
		std::vector<T *>	_base;
		size_t				_size;

	public:
		ft_deque();
		ft_deque(const ft_deque<T, _Allocator>&);
		// ft_deque(const std::stack<T, std::deque<T, _Allocator> >&);
		ft_deque<T, _Allocator>& operator=(const ft_deque<T, _Allocator>&);
		~ft_deque();

		/* METHODS */
		size_t	size(void) const;
		void	push_back(const T&);
		void	pop_back(void);
		void	push_front(const T&);
		void	pop_front(void);

		/* OVERLOADS */
		T&			operator[](int);
		const T&	operator[](int) const;
	
		/* ITERATOR */
		// class iterator
		// {
		// 	private:
		// 		T*					_ptr;
		// 		std::vector<T*>		_base;

		// 	public:

		// 	/* RAW */
		// 	T*					base(void) const;
		// 	std::map<T*, T*>*	getJumps(void);
		// 	std::map<T*, T*>*	getrJumps(void);

		// 	/* CONSTRUCTOR */
		// 	iterator();
		// 	iterator(const iterator&);
		// 	~iterator();
		// 	// iterator(const typename std::deque<T, _Allocator>::iterator&);
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
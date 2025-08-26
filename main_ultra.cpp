/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:17:17 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/26 20:36:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.h"
#include <stack>
#include <deque>
#include <list>
#include <iostream>

typedef unsigned long uintptr_t;

// template <typename T>
// static void	dequeScanner(std::deque<T> deque)
// {
// 	typename std::deque<T>::iterator it = deque.begin();
// 	typename std::deque<T>::iterator last1 = deque.end();
// 	uintptr_t	firstAddr = reinterpret_cast<uintptr_t>(deque.begin()._M_cur);

// 	std::cout << "HEAD: " << firstAddr << std::endl;

// 	while (it != last1)
// 	{
// 		std::cout << *it << ": " << reinterpret_cast<uintptr_t>(it._M_cur) << ", diff: " << (reinterpret_cast<uintptr_t>(it._M_cur) - firstAddr) / sizeof(T) << std::endl;
// 		it++;
// 	}
// }

int	main(void)
{
	ft_deque<int> test;

	for (int i = 0; i < 25000; i++) {
		test.push(i);
	}

	std::cout << "top is: " << test.top() << std::endl;
	
	test.pop();

	std::cout << "top is: " << test.top() << std::endl;

	ft_deque<int>::iterator it = test.begin();
	std::cout << "it: " << *it << "; it++; "; it ++; std::cout << "it: " << *it << std::endl;

	std::cout << "/* INCREMENT */" << std::endl;
	while (it != test.end())
	{
		std::cout << "it: " << *it << std::endl;
		++it;
	}
	std::cout << "last1: " << *(--it) << std::endl;	// went too far with the last one

	std::cout << "/* DECREMENT */" << std::endl;
	while (it != test.begin())
	{
		std::cout << "it: " << *it << std::endl;
		--it;
	}
	std::cout << "first1: " << *it << std::endl;
	
	/* ME BEING CURIOUS AND PRECAUTIONS :D */
	{
		std::cout << "/* DEQUE TEST */" << std::endl;
		std::deque<int> deq;
		
		for (int i = 0; i < 20000; i++) {
			deq.push_back(i);
		}

		std::cout << "// dequeScanner(deq) <-- uncomment" << std::endl;
		// dequeScanner(deq);
	}
	
	/* SUBJECT BEING NEEDY */
	{
		std::cout << "/* SUBJECT TEST */" << std::endl;
		ft_deque<int> fdeque;

		fdeque.push(5);
		fdeque.push(17);

		std::cout << fdeque.top() << std::endl;

		fdeque.pop();	// remove from jump tabs

		std::cout << fdeque.size() << std::endl;

		fdeque.push(3);
		fdeque.push(5);
		fdeque.push(737);
		//[...]
		fdeque.push(0);

		ft_deque<int>::iterator it = fdeque.begin();
		ft_deque<int>::iterator ite = fdeque.end();

		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		std::stack<int> s(fdeque);
	}

	{
		std::cout << "/* SUBJECT TEST */" << std::endl;
		std::list<int> list;

		list.push_back(5);
		list.push_back(17);

		std::cout << *(--list.end()) << std::endl;	// top() in a stack gets the last element inserted, so it'll be the last one of the list

		list.pop_back();

		std::cout << list.size() << std::endl;

		list.push_back(3);
		list.push_back(5);
		list.push_back(737);
		//[...]
		list.push_back(0);

		std::list<int>::iterator it = list.begin();
		std::list<int>::iterator ite = list.end();

		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		// std::stack<int> s(list);
	}

	#include <deque>

	std::deque<int> d;

	d.push_back()
	

	return 0;
}
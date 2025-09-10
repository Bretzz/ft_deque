/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:02:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/09 22:17:30 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.hpp"
#include "myClass.hpp"

// template <typename T>
// static void	dequeScanner(std::ft_deque<T> deque)
// {
// 	typename std::ft_deque<T>::iterator it = deque.begin();
// 	typename std::ft_deque<T>::iterator last1 = deque.end();
// 	uintptr_t	firstAddr = reinterpret_cast<uintptr_t>(deque.begin()._M_cur);

// 	std::cout << "HEAD: " << firstAddr << std::endl;

// 	while (it != last1)
// 	{
// 		std::cout << *it << ": " << reinterpret_cast<uintptr_t>(it._M_cur) << ", diff: " << (reinterpret_cast<uintptr_t>(it._M_cur) - firstAddr) / sizeof(T) << std::endl;
// 		it++;
// 	}
// }

#include <iostream>

int	main(void)
{
	ft_deque<int>	f;

	f.push_back(1);
	f.push_back(2);
	f.push_back(3);
	// f.push_back(4);
	// f.push_back(5);

	try
	{
		f.print();
		for (size_t i = 0; i < f.size(); ++i)
		{
			std::cout << f[i] << " ";
		}
		std::cout << std::endl;
		// f[-1] = -2;
	}catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	// f.push_back(5);
	f.pop_front();

	try
	{
		f.print();
		for (size_t i = 0; i < f.size(); ++i)
		{
			std::cout << f[i] << " ";
		}
		std::cout << std::endl;
		// f[-1] = -2;
	}catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "front : " << f.front() << ", back : " << f.back() << std::endl;

	f.assign(10, -1);

	std::cout << "at(5) : " << f.at(5) << std::endl;

	f.clear();
	for (int i = 0; i < 11; ++i)
	{
		if (i % 2 == 0)
			f.push_back(i);
		else
			f.push_front(i);
	}

	/* iterators */
	std::cout << "/* ITERATORS */" << std::endl;
	f.print();

	std::cout << "forward" << std::endl;
	ft_deque<int>::iterator it = f.begin();
	while (it != f.end())
	{
		std::cout << *it << std::endl;
		++it;
	}

	std::cout << "backward" << std::endl;
	do
	{
		it--;
		std::cout << *it << std::endl;
	}
	while (it != f.begin());

	std::cout << "expected " << f.size() << " destructors" << std::endl;
	return 0;
}

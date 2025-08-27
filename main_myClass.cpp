/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:02:02 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/27 01:50:10 by totommi          ###   ########.fr       */
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
	ft_deque<myClass>	f;
	myClass				c(1);
	myClass				d(2);

	f.print();
	std::cout << std::endl;

	f.push_back(c);
	f.push_back(d);
	f.push_back(c);
	f.push_back(d);

	f.print();

	std::cout << f.size() << std::endl;

	f.push_back(c);
	
	std::cout << f.size() << std::endl;
	
	f.pop_back();
	
	std::cout << f.size() << std::endl;
	
	f.pop_front();

	f.print();

	std::cout << std::endl << "=== 2x push front ===" << std::endl;

	f.push_front(c);
	f.push_front(d);

	f.print();

	std::cout << std::endl << "=== pop back ===" << std::endl;

	// f.pop_back();

	// f.print();
	
	for (size_t i = 0; i < f.size(); ++i)
	{
		std::cout << f[(int)i].me() << std::endl;
	}

	{
		std::cout << "copy" << std::endl;
		ft_deque<myClass> g(f);
	
		g.print();

		for (size_t i = 0; i < g.size(); ++i)
		{
			std::cout << g[(int)i].me() << std::endl;
		}
		std::cout << "at(0)" << g.at(0).me() << std::endl;
	}



	std::cout << "expected " << f.size() + 2 << " destructors" << std::endl;
	return 0;
}

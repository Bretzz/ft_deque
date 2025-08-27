/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:53:52 by totommi           #+#    #+#             */
/*   Updated: 2025/08/27 12:10:51 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myClass.hpp"
#include "ft_deque.hpp"
#include <deque>

int	main(void)
{
	myClass				c(0);
	std::deque<myClass> d;
	ft_deque<myClass>	f;

	/* PUSH BACK */
	for (size_t i = 0; i < 12; ++i)
	{
		d.push_back(c);
		f.push_back(c);
		++c;
		if (d.back() != f.back())
			std::cout << "different back() : " << d.back() << " != " << f.back() << std::endl;
		if (d.front() != f.front())
			std::cout << "different front() : " << d.front() << " != " << f.front() << std::endl;
	}

	/* whole content check */
	for (size_t i = 0; i < d.size(); ++i)
	{
		if (d[i] != f[i])
			std::cout << "different operator[] at " << i << ", d[" << i << "] = " << d[i] << ", f[" << i << "] = " << f[i] << std::endl;
	}

	/* PUSH FRONT */
	for (size_t i = 0; i < 12; ++i)
	{
		d.push_front(c);
		f.push_front(c);
		++c;
		if (d.back() != f.back())
			std::cout << "different back() : " << d.back() << " != " << f.back() << std::endl;
		if (d.front() != f.front())
			std::cout << "different front() : " << d.front() << " != " << f.front() << std::endl;
	}

	/* whole content check */
	for (size_t i = 0; i < d.size(); ++i)
	{
		if (d[i] != f[i])
			std::cout << "different operator[] at " << i << ", d[" << i << "] = " << d[i] << ", f[" << i << "] = " << f[i] << std::endl;
	}

	f.print();

	/* POP BACK */
	for (size_t i = 0; i < 12; ++i)
	{
		d.pop_back();
		f.pop_back();
		if (d.back() != f.back())
			std::cout << "different back() : " << d.back() << " != " << f.back() << std::endl;
		if (d.front() != f.front())
			std::cout << "different front() : " << d.front() << " != " << f.front() << std::endl;
	}

	/* whole content check */
	for (size_t i = 0; i < d.size(); ++i)
	{
		if (d[i] != f[i])
			std::cout << "different operator[] at " << i << ", d[" << i << "] = " << d[i] << ", f[" << i << "] = " << f[i] << std::endl;
	}

	/* POP FRONT */
	for (size_t i = 0; i < 12 - 1; ++i)
	{
		d.pop_front();
		f.pop_front();
		if (d.back() != f.back())
			std::cout << "different back() : " << d.back() << " != " << f.back() << std::endl;
		if (d.front() != f.front())
			std::cout << "different front() : " << d.front() << " != " << f.front() << std::endl;
	}

	/* whole content check */
	for (size_t i = 0; i < d.size(); ++i)
	{
		if (d[i] != f[i])
			std::cout << "different operator[] at " << i << ", d[" << i << "] = " << d[i] << ", f[" << i << "] = " << f[i] << std::endl;
	}

	f.print();
	std::cout << "- main obj : " << c << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:53:52 by totommi           #+#    #+#             */
/*   Updated: 2025/08/27 14:33:48 by topiana-         ###   ########.fr       */
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

	d.push_back(c);
	f.push_back(c); ++c;
	d.push_back(c);
	f.push_back(c); ++c;

	d.pop_front();
	d.pop_front();
	f.pop_front();
	f.pop_front();

	f.print();

	/* whole content check */
	for (size_t i = 0; i < d.size(); ++i)
	{
		if (d[i] != f[i])
			std::cout << "different operator[] at " << i << ", d[" << i << "] = " << d[i] << ", f[" << i << "] = " << f[i] << std::endl;
	}

	std::cout << "=== double up ===" << std::endl;

	for (int i = 0; i < 4; ++i)
	{
		f.push_front(c);
		d.push_front(c);
		++c;
	}

	f.print();

	/* whole content check */
	for (size_t i = 0; i < d.size(); ++i)
	{
		if (d[i] != f[i])
			std::cout << "different operator[] at " << i << ", d[" << i << "] = " << d[i] << ", f[" << i << "] = " << f[i] << std::endl;
	}

	std::cout << "- main obj : " << c << std::endl;
}

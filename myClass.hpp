/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myClass.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:31:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/26 22:26:05 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYCLASS_HPP
# define MYCLASS_HPP

# include <iostream>

class myClass
{
	private:
		int	_n;
	
	public:
		myClass() {_n = 0;}
		myClass(int __n) {_n = __n;}
		~myClass() {std::cout << "aaaaaaaa!!!!" << _n << std::endl;}
		int me(void) const {return _n;}
};

#endif
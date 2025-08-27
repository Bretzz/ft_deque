/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myClass.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:31:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/08/27 12:02:06 by totommi          ###   ########.fr       */
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
		~myClass() {std::cout << "aaaaaaaa!!!! " << _n << std::endl;}
		int me(void) const {return _n;}

		myClass&	operator++() {++_n; return *this;}
		bool		operator!=(const myClass &__x) {return _n != __x.me();}
};

std::ostream&	operator<<(std::ostream& os, const myClass &__x)
{
	os << __x.me();
	return os;
}

#endif
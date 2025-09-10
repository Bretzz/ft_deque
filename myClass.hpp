/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myClass.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:31:56 by topiana-          #+#    #+#             */
/*   Updated: 2025/09/10 02:27:59 by totommi          ###   ########.fr       */
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

		myClass&	operator=(int __n) {_n = __n; return *this;}
		myClass&	operator=(const myClass &__x) {_n = __x._n; return *this;}
		myClass&	operator++() {++_n; return *this;}
		bool		operator!=(const myClass &__x) {return _n != __x.me();}
};

std::ostream&	operator<<(std::ostream& os, const myClass &__x)
{
	os << __x.me();
	return os;
}

#endif
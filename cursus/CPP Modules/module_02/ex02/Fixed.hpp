/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:11:17 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/16 18:17:57 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
# define FIXED_H

# include <iostream>
# include <cmath>

class	Fixed
{
	private:
		int					raw_bits;
		static const int	frac_pos = 8;
	
	public:
		Fixed(void);
		Fixed(const Fixed &);
		Fixed(const int);
		Fixed(const float);
		~Fixed(void);

		Fixed				&operator=(const Fixed &);
		bool				operator>(const Fixed &) const;
		bool				operator<(const Fixed &) const;
		bool				operator>=(const Fixed &) const;
		bool				operator<=(const Fixed &) const;
		bool				operator==(const Fixed &) const;
		bool				operator!=(const Fixed &) const;
		Fixed				operator+(const Fixed &) const;
		Fixed				operator-(const Fixed &) const;
		Fixed				operator*(const Fixed &) const;
		Fixed				operator/(const Fixed &) const;
		Fixed				&operator++(void);
		Fixed				operator++(int);
		Fixed				&operator--(void);
		Fixed				operator--(int);
		int					getRawBits(void) const;
		void				setRawBits(int const);
		float				toFloat(void) const;
		int					toInt(void) const;

		static Fixed		&min(Fixed &, Fixed &);
		static const Fixed	&min(const Fixed &, const Fixed &);
		static Fixed		&max(Fixed &, Fixed &);
		static const Fixed	&max(const Fixed &, const Fixed &);
};

std::ostream	&operator<<(std::ostream &, const Fixed &);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:11:07 by tcakmako          #+#    #+#             */
/*   Updated: 2022/12/02 17:59:59 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
	raw_bits = 0;
}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed::Fixed(const int num)
{
	raw_bits = num << frac_pos;
}

Fixed::Fixed(const float single)
{
	raw_bits = roundf(single * (1 << frac_pos));
}

Fixed::~Fixed(void)
{
}

Fixed	&Fixed::operator=(const Fixed &other)
{
	if (this != &other)
		raw_bits = other.getRawBits();
	return (*this);
}

bool	Fixed::operator>(const Fixed &other) const
{
	if (raw_bits > other.raw_bits)
		return (1);
	return (0);
}

bool	Fixed::operator<(const Fixed &other) const
{
	if (raw_bits < other.raw_bits)
		return (1);
	return (0);
}

bool	Fixed::operator>=(const Fixed &other) const
{
	if (raw_bits > other.raw_bits || raw_bits == other.raw_bits)
		return (1);
	return (0);
}

bool	Fixed::operator<=(const Fixed &other) const
{
	if (raw_bits < other.raw_bits || raw_bits == other.raw_bits)
		return (1);
	return (0);
}

bool	Fixed::operator==(const Fixed &other) const
{
	if (raw_bits == other.raw_bits)
		return (1);
	return (0);
}

bool	Fixed::operator!=(const Fixed &other) const
{
	if (raw_bits != other.raw_bits)
		return (1);
	return (0);
}

Fixed	Fixed::operator+(const Fixed &other) const
{
	Fixed	tmp;
	
	tmp.setRawBits(raw_bits + other.raw_bits);
	return (tmp);
}

Fixed	Fixed::operator-(const Fixed &other) const
{
	Fixed	tmp;

	tmp.setRawBits(raw_bits - other.raw_bits);
	return (tmp);
}

Fixed	Fixed::operator*(const Fixed &other) const
{
	Fixed	tmp;
	
	tmp.setRawBits((raw_bits * other.raw_bits) >> (frac_pos));
	return (tmp);
}

Fixed	Fixed::operator/(const Fixed &other) const
{
	Fixed	tmp;

	tmp.setRawBits(((raw_bits << frac_pos) / other.raw_bits));
	return (tmp);
}

Fixed	&Fixed::operator++(void)
{
	raw_bits++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	tmp(*this);

	raw_bits++;
	return (tmp);
}

Fixed	&Fixed::operator--(void)
{
	raw_bits--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	tmp(*this);

	raw_bits--;
	return (tmp);
}

int	Fixed::getRawBits(void) const
{
	return (raw_bits);
}

void	Fixed::setRawBits(int const raw)
{
	raw_bits = raw;
}

float	Fixed::toFloat(void) const
{
	return ((float) raw_bits / (1 << frac_pos));
}

int		Fixed::toInt(void) const
{
	return (raw_bits >> frac_pos);
}

Fixed	&Fixed::min(Fixed &obj1, Fixed &obj2)
{
	if (obj1 < obj2)
		return (obj1);
	return (obj2);
}

const Fixed	&Fixed::min(const Fixed &obj1, const Fixed &obj2)
{
	if (obj1 < obj2)
		return (obj1);
	return (obj2);
}

Fixed	&Fixed::max(Fixed &obj1, Fixed &obj2)
{
	if (obj1 > obj2)
		return (obj1);
	return (obj2);
}

const Fixed	&Fixed::max(const Fixed &obj1, const Fixed &obj2)
{
	if (obj1 > obj2)
		return (obj1);
	return (obj2);
}

std::ostream	&operator<<(std::ostream &out, const Fixed &obj)
{
	out << obj.toFloat();
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:11:17 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/16 17:04:48 by tcakmako         ###   ########.fr       */
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

		Fixed			&operator=(const Fixed &);
		int				getRawBits(void) const;
		void			setRawBits(int const);
		float			toFloat(void) const;
		int				toInt(void) const;
};

std::ostream	&operator<<(std::ostream &, const Fixed &);

#endif

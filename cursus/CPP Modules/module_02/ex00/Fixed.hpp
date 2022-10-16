/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:11:17 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/15 22:11:17 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
# define FIXED_H

# include <iostream>

class	Fixed
{
	private:
		int					raw_bits;
		static const int	frac_bits = 8;
	
	public:
		Fixed(void);
		Fixed(const Fixed &);
		~Fixed(void);

		Fixed	&operator=(const Fixed &);
		int		getRawBits(void) const;
		void	setRawBits(int const);
};

#endif

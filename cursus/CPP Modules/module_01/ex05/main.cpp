/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:05:03 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/15 12:05:04 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(void)
{
	Harl	h1;

	h1.complain("INFO");
	h1.complain("ERROR");
	h1.complain("WARNING");
	h1.complain("DEBUG");
	return (0);
}

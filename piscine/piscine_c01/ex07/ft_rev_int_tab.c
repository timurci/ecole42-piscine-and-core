/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:50:04 by tcakmako          #+#    #+#             */
/*   Updated: 2021/11/28 13:50:05 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_rev_int_tab(int *tab, int size)
{
	int	temp;
	int	index;

	index = 0;
	while (index < size / 2)
	{
		temp = tab[index];
		tab[index] = tab[size - (index + 1)];
		tab[size - (index + 1)] = temp;
		index++;
	}
}

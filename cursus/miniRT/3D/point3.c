/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:52:47 by tcakmako          #+#    #+#             */
/*   Updated: 2023/04/15 13:52:47 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "point3.h"

t_point3	point3_set(const float x, const float y, const float z)
{
	return (vector3_set(x, y, z));
}

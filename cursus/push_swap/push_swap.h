/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:51:14 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/03 15:35:31 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"

# define STEP_CONSTANT 500

typedef struct s_ints
{
	int		*arr;
	size_t	inv;
	size_t	max;
}			t_ints;

int		parse_int(t_ints *list, size_t itr, unsigned char addition, char *sign);
t_ints	*parse_args(int argc, char **argv);
char	is_sorted(t_ints *list);
size_t	fill_array_with_args(t_ints *list, char **argv);
size_t	fill_array(t_ints *list, char *str);
void	rev_array(t_ints *list);

t_ints	*dup_ints(t_ints *a);
void	delete_ints(t_ints *list);

void	push(t_ints *a, t_ints *b, char *mode);
void	swap(t_ints *l, char *mode);
void	rot(t_ints *l, char *mode);
void	rrot(t_ints *l, char *mode);

void	tiny_sort(t_ints *a);
void	huge_sort(t_ints *a);

void	mvclosest_to_top(t_ints *l, int min, int max, char *mode);
void	rotate_to_top(t_ints *list, int n, char stack_name);
size_t	locate_closest_element(t_ints *l, int min, int max, char mode);
size_t	locate_prev(t_ints *list, int n);
size_t	locate_next(t_ints *list, int n);

int		max_element(t_ints *list);
int		min_element(t_ints *list);

void	parsing_errors(char mode, void *param);

void	print_array(t_ints *list, char *name);

#endif

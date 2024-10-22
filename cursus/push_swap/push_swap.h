/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:51:14 by tcakmako          #+#    #+#             */
/*   Updated: 2022/08/13 16:48:33 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"

typedef struct s_ints
{
	int		*arr;
	size_t	inv;
	size_t	max;
}			t_ints;

int		parse_int(t_ints *list, size_t itr, unsigned char addition, char *sign);
t_ints	*parse_args(int argc, char **argv);
char	is_shift_sorted(t_ints *list);
char	is_sorted(t_ints *list);
size_t	fill_array_with_args(t_ints *list, char **argv);
size_t	fill_array(t_ints *list, char *str);
void	rev_array(t_ints *list);

void	*ft_calloc(size_t count, size_t size);
t_ints	*dup_ints(t_ints *a);
void	delete_ints(t_ints *list);

void	push(t_ints *a, t_ints *b, char *mode);
void	swap(t_ints *l, char *mode);
void	rot(t_ints *l, char *mode);
void	rrot(t_ints *l, char *mode);

void	tiny_sort(t_ints *a);
void	huge_sort(t_ints *a);

void	mutual_rotation(t_ints *l1, t_ints *l2, int n1, int n2);
void	mvclosest_to_top(t_ints *l, int min, int max, char *mode);
void	rotate_to_top(t_ints *list, int n, char stack_name);

t_ints	*form_index(t_ints *l);
size_t	locate_closest_element(t_ints *l, int min, int max, char mode);
size_t	locate_index(t_ints *l, int n);

int		find_prev(t_ints *list, int n);
int		find_next(t_ints *list, int n);

int		max_element(t_ints *list);
int		min_element(t_ints *list);

void	parsing_errors(char mode, void *param);

void	print_array(t_ints *list, char *name);

#endif

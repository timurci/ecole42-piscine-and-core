#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //remove later

typedef struct s_ints
{
	int		*arr;
	size_t	inv;
	size_t	max;
}			t_ints;

t_ints	*parse_args(char *str);
char	is_sorted(t_ints *list);

t_ints	*dup_ints(t_ints *a);
void	delete_ints(t_ints *list);

void	push(t_ints *a, t_ints *b, char *mode);
void	swap(t_ints *l, char *mode);
void	rot(t_ints *l, char *mode);
void	rrot(t_ints *l, char *mode);

void	tiny_sort(t_ints *a);

void	rotate_to_top(t_ints *list, int n, char stack_name);
int		locate_prev(t_ints *list, int n);
int		locate_next(t_ints *list, int n);

int		max_element(t_ints *list);
int		min_element(t_ints *list);

void	parsing_errors(char mode, void *param);

void	print_array(t_ints *list, char *name);

#endif

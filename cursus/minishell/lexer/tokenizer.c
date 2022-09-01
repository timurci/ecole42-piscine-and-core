#include "lexer.h"

static size_t	count_strs(char **cmds)
{
	size_t	size;

	size = 0;
	while (cmds[size])
		size++;
	return (size);
}

t_token	*tokenize(char **cmds)
{
	size_t	str_count;
	size_t	itr;
	t_token	*tokens;

	str_count = count_strs(cmds);
	tokens = (t_token *) malloc(sizeof(*tokens) * (str_count + 1));
	tokens[str_count].type = -100;
	itr = 0;
	while (cmds[itr])
	{
		tokens[itr].value = cmds[itr];
		tokens[itr].type = -1;
		itr++;
	}
	free(cmds);
	return (tokens);
}

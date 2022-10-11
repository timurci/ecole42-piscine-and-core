#include <iostream>

static char	*convert_to_upper(char *str)
{
	char	*scan;

	scan = str;
	while (*scan)
	{
		*scan = toupper(*scan);
		scan++;
	}
	return (str);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
		for (int i = 1; i < argc; i++)
			std::cout << convert_to_upper(argv[i]) << (i + 1 < argc ? " " : "");
	std::cout << std::endl;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakmako <tcakmako@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:13:01 by tcakmako          #+#    #+#             */
/*   Updated: 2022/10/14 23:13:01 by tcakmako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

void	print_file_error(std::string fname)
{
	std::cout << "Cannot open file: " << fname << std::endl;
}

void	replace_string(std::string &line, std::string &s1, std::string &s2)
{
	size_t		pos = 0;

	while (1)
	{
		pos = line.find(s1, pos);
		if (pos == std::string::npos)
			break ;
		line.erase(pos, s1.size());
		line.insert(pos, s2);
		pos += s2.size();
	}
}

int	create_replace(std::string &fname, std::string &s1, std::string &s2)
{
	std::ifstream	src;
	std::ofstream	dst;

	src.open(fname.c_str());
	if (!src.is_open()) {print_file_error(fname); return (1);}
	dst.open((fname + ".replace").c_str(), std::ios::out | std::ios::trunc);
	if (!dst.is_open()) {print_file_error((fname + ".replace")); return (1);}

	std::string	line;

	while (std::getline(src, line))
	{
		replace_string(line, s1, s2);
		dst << line << std::endl;
	}
	src.close();
	dst.close();
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Invalid number of arguments." << std::endl;
		return (1);
	}

	std::string	filename;
	std::string	s1, s2;

	filename = argv[1];
	s1 = argv[2];
	s2 = argv[3];
	if (create_replace(filename, s1, s2))
		return (1);
	return (0);
}

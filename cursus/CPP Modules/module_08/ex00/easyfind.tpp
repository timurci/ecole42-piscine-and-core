#include "easyfind.hpp"

template <class T>
int	&easyfind(T &obj, int target)
{
	typename T::iterator	iter = obj.begin();
	typename T::iterator	end = obj.end();

	for(; iter != end; iter++)
	{
		if (*iter == target)
			return (*iter);
	}
	throw std::out_of_range("Value not found.");
	//typename T::iterator	iter = std::find(obj.begin(), obj.end(), target);
	return (*iter);
}

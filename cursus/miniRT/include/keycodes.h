#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __linux__
#  define KEY_1 49
#  define KEY_2 KEY_1 + 1
#  define KEY_ESC 65307
# else
#  define KEY_1 18
#  define KEY_2 KEY_1 + 1
#  define KEY_ESC 53
# endif

#endif

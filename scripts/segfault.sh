#!/bin/bash
make re CFLAGS='-Wall -Wextra -g3 -fsanitize=address' > /dev/null && ./minishell $@
make clean > /dev/null
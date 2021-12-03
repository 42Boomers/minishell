#!/bin/bash
if [[ "$OSTYPE" == "darwin"* ]]; then
	make all > /dev/null && leaks -atExit -- ./minishell $@
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
	make all > /dev/null && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell $@
else
	echo "Unknown OS $OSTYPE"
	make all > /dev/null && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell $@
fi
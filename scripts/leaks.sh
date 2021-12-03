#!/bin/bash
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	make all > /dev/null && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./minishell $@
elif [[ "$OSTYPE" == "darwin"* ]]; then
	make all > /dev/null && leaks -atExit -- ./minishell $@
else
	echo "Unknown OS $OSTYPE"
fi
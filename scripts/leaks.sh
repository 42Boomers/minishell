#!/bin/bash
make all > /dev/null && leaks -atExit -- ./minishell $@


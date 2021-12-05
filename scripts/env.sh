#!/bin/zsh
make
./minishell > ft_env.txt
env > env.txt

diff ft_env.txt env.txt

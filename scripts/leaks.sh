#!/bin/bash

case "$OSTYPE" in
  solaris*) echo "OS Detected : SOLARIS" ;;
  darwin*)  echo "OS Detected : OSX" ;; 
  linux*)   echo "OS Detected : LINUX" ;;
  bsd*)     echo "OS Detected : BSD" ;;
  msys*)    echo "OS Detected : WINDOWS" ;;
  cygwin*)  echo "OS Detected : ALSO WINDOWS" ;;
  *)        echo "OS unknown : $OSTYPE" ;;
esac

make all > /dev/null

if [[ "$OSTYPE" == "darwin"* ]] ; then
	leaks -atExit -- ./minishell $@
elif [[ "$OSTYPE" == "linux-gnu"* ]] ; then
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell $@
elif [[ "$OSTYPE" == "msys"* ]] ; then
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell $@
else
	echo "Unknown OS $OSTYPE"
fi

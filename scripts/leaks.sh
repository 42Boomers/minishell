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
	valgrind --leak-check=full --track-origins=yes --errors-for-leak-kinds=all --error-exitcode=1 ./minishell $@
elif [[ "$OSTYPE" == "msys"* ]] ; then
	valgrind --leak-check=full --track-origins=yes --errors-for-leak-kinds=all --error-exitcode=1 ./minishell $@
else
	echo "Unknown OS $OSTYPE"
fi

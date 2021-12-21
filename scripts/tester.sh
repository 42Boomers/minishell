#!/bin/bash
TESTER_DIR=minishell_tester

git submodule update --init
cd $TESTER_DIR && bash test.sh all

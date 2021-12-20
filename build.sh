#!/bin/zsh

set -xe

CC=gcc
BIN=gf
PROG=get_flags.c

$CC -o $BIN -pedantic --std=c11 -Werror -Wall $PROG

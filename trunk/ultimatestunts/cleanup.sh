#!/bin/sh

#Shell script for cleaning up the tree before
#committing it to CVS. Makes it easier to check
#the CVS output for errors

#Author: CJP

make clean
rm -f Makefile */Makefile
rm -rf */.deps

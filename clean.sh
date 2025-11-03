#!/bin/bash
for dir in $(find . -name build); do
  echo "Removing $dir ..."
  rm -rf $dir
done

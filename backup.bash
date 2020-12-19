#!/bin/bash
echo "Enter name of backup directory.":  
read filename
if [ -d ~/$filename ];
then
      echo $filename "directory already exists."
else
      mkdir -p ~/filename || \
      rsync -r --include="*.txt" --exclude="*" "$PWD"/ ~/$filename/
fi
echo "Backed up all *.txt files"


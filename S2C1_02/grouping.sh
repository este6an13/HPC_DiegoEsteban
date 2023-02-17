#!/bin/bash

# This script will organize files in a directory by extension
# Each extension will be grouped together in a subdirectory named after the extension

if [ -z "$1" ]; then
  echo "Please provide a path to the directory you want to organize"
  exit 1
fi

if [ ! -d "$1" ]; then
  echo "The provided path does not exist or is not a directory"
  exit 1
fi

cd "$1"

for file in *; do
  # Check that this is a file and not a directory
  if [ -f "$file" ]; then
    # Get the file extension (everything after the last period)
    extension="${file##*.}"
    # Create the subdirectory if it doesn't already exist
    if [ ! -d "$(basename "$PWD")_$extension/" ]; then
      mkdir "$(basename "$PWD")_$extension/"
    fi
    # Move the file into the appropriate subdirectory
    mv "$file" "$(basename "$PWD")_$extension/"
  fi
done


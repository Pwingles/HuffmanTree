#!/bin/bash


src="/home/faculty/kooshesh/cs315_fall2025/project3/part2/input_files"
dst="./input_output"

# Check if source directory exists
## if [ ! -d "$src" ]; then
##   echo "Error: Source directory '$src' does not exist."
##   exit 1
## fi

# Check if destination directory exists
if [ ! -d "$dst" ]; then
  echo "Error: Destination directory '$dst' does not exist."
  exit 1
fi

# Copy files from source to destination
# -a preserves attributes, -v is verbose
cp -av "$src"/*.txt "$dst"/

echo "Files copied from '$src' to '$dst'."

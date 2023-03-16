#!/bin/bash

# Check if input argument is valid
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file_path>"
    exit 1
fi

file_path="$1"

# Enable Address Sanitizer (ASan)
echo "Compiling with Address Sanitizer (ASan)..."
g++ -fsanitize=address -g "$file_path" -o "${file_path%.*}"_asan
echo "ASan build completed."

# Enable Leak Sanitizer (LSan)
echo "Compiling with Leak Sanitizer (LSan)..."
g++ -fsanitize=leak -g "$file_path" -o "${file_path%.*}"_lsan
echo "LSan build completed."

# Enable Undefined Behavior Sanitizer (UBSan)
echo "Compiling with Undefined Behavior Sanitizer (UBSan)..."
g++ -fsanitize=undefined -g "$file_path" -o "${file_path%.*}"_ubsan
echo "UBSan build completed."

# Enable Thread Sanitizer (TSan)
echo "Compiling with Thread Sanitizer (TSan)..."
g++ -fsanitize=thread -g "$file_path" -o "${file_path%.*}"_tsan
echo "TSan build completed."

echo "All sanitizers enabled and compiled successfully!"


#!/usr/bin/env bash
# run_all.sh
# Compile, run on every input_output/*.txt, and diff outputs against a reference dir.

set -Eeuo pipefail

# ---- Configuration (overridable via env vars) -------------------------------
CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=c++20 -Wall}
TARGET=${TARGET:-p3_complete.x}

# Positional args:
#   $1 = directory containing the expected .tokens/.freq files (the "somePath")
#   $2 = input directory (defaults to input_output, with a fallback to input_putput)
EXPECTED_DIR=${1:-/home/faculty/kooshesh/cs315_fall2025/project3/final_version}
INPUT_DIR=${2:-input_output}

# Move to the directory containing this script (so relative paths work)
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"

# ---- Compile ----------------------------------------------------------------
shopt -s nullglob
sources=( *.cpp )
if (( ${#sources[@]} == 0 )); then
  echo "Error: no .cpp files found in $(pwd)." >&2
  exit 1
fi

echo "Compiling: $CXX $CXXFLAGS ${sources[*]} -o $TARGET"
"$CXX" $CXXFLAGS "${sources[@]}" -o "$TARGET"

# ---- Locate input dir (accept common typo 'input_putput') --------------------
if [[ ! -d "$INPUT_DIR" ]]; then
  if [[ -d "input_putput" ]]; then
    echo "Warning: '$INPUT_DIR' not found; using 'input_putput' instead."
    INPUT_DIR="input_putput"
  else
    echo "Error: input directory '$INPUT_DIR' not found." >&2
    exit 1
  fi
fi

# ---- Check expected dir ------------------------------------------------------
if [[ ! -d "$EXPECTED_DIR" ]]; then
  echo "Error: expected outputs directory '$EXPECTED_DIR' not found." >&2
  echo "Pass it as the first argument, e.g.:  $0 /path/to/somePath" >&2
  exit 1
fi

# ---- Run program on every .txt and diff results ------------------------------
echo "Scanning for inputs in: $INPUT_DIR"
pass=0
fail=0
found_any=0

# Use find -print0 for safe handling of spaces/newlines in filenames
while IFS= read -r -d '' txt; do
  found_any=1
  basefile=$(basename "$txt")        # e.g., nameOf.txt
  base="${basefile%.txt}"            # e.g., nameOf

  echo -e "\n==> Running: $TARGET on $basefile"

  "./$TARGET" "$basefile"


  # Now compare the two expected outputs
  for ext in tokens freq code hdr; do

    actual="$INPUT_DIR/$base.$ext"
    expected="$EXPECTED_DIR/$ext/$base.$ext"
    echo "Comparing: $actual  and  $expected"
    if diff -u "$expected" "$actual" >/dev/null 2>&1; then
      echo "$ext matches"
      (( pass += 1 ))
    else
      echo "$ext differs"
      # Show the unified diff to help debugging
      diff -u "$expected" "$actual" || true
      (( fail += 1 ))
    fi

  done
done < <(find "$INPUT_DIR" -maxdepth 1 -type f -name '*.txt' -print0)

if (( found_any == 0 )); then
  echo "No .txt files found in '$INPUT_DIR'."
  exit 0
fi

echo -e "\nSummary: ${pass} match(es), ${fail} diff(s)."
# Exit nonzero if any diffs were found (useful for CI/automation)
exit $(( fail > 0 ))

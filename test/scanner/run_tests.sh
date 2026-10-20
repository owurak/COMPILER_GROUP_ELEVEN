#!/bin/sh
# Usage: ./run_tests.sh path/to/lexer-binary
# valid/*   -> lexer must exit 0 (no INVALID tokens)
# invalid/* -> lexer must exit 2 (at least one INVALID token)

BIN="${1:-./compiler}"
DIR="$(cd "$(dirname "$0")" && pwd)"
pass=0; fail=0
for f in "$DIR"/valid/*.txt; do
    "$BIN" "$f" >/dev/null 2>&1; rc=$?
    if [ $rc -eq 0 ]; then pass=$((pass+1)); else fail=$((fail+1)); echo "FAIL (valid, exit $rc): $f"; fi
done
for f in "$DIR"/invalid/*.txt; do
    "$BIN" "$f" >/dev/null 2>&1; rc=$?
    if [ $rc -eq 2 ]; then pass=$((pass+1)); else fail=$((fail+1)); echo "FAIL (invalid, exit $rc): $f"; fi
done
echo "passed $pass, failed $fail"
[ $fail -eq 0 ]

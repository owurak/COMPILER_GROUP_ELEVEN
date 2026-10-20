# Lexer bug report (Member 2)

Run: `ctest --test-dir build --output-on-failure` -> scanner tests: **19 passed, 1 failed**

## BUG-1: unterminated block comment accepted silently
- Test: `invalid/invalid07.txt` (comment opens on line 3, never closes)
- Expected: an INVALID token at the comment start (3:1), exit code 2
- Actual: comment swallows the rest of the file, no INVALID token, exit code 0
- Where: `lexer.cpp`, `skipWhitespaceAndComments()`, block-comment branch (the loop ends at EOF with no error)
- Suggested fix: add a `bool unterminatedComment` plus its line/col as members in `lexer.h`; set them in that branch; at the top of `getNextToken()` return `{TokenType::INVALID, "/*", line, col}` when set.

## BUG-2 (minor): non-ASCII input is split into single bytes
- Test: `invalid/invalid09.txt` (`int café = 1;`)
- Expected: one INVALID token for `é`
- Actual: two INVALID tokens, each one raw byte (0xC3, 0xA9), so stdout contains invalid UTF-8
- Where: `lexer.cpp`, last lines of `getNextToken()` (unknown character branch)
- Suggested fix: when the byte is >= 0x80, also consume following continuation bytes (`(b & 0xC0) == 0x80`) into one lexeme.

## Spec decisions to confirm (not bugs)
- `.5` lexes as `.` `5`; `1.` as `1` `.`; `5..3` as `5` `.` `.` `3`.
- Keyword list and the two-character operator list are guesses (see docs/token-spec.md).

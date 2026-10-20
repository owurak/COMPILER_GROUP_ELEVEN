# Token Spec

Branch later: tests/scanner (test files live in `tests/scanner/`)

> **DRAFT.** Written from what Member 1's lexer currently implements because the
> lecturer spec was not available. Every row marked **(confirm)** must be checked
> against the lecturer spec before the 25 Oct deadline.

## 1. Keywords (confirm)

`if else while for do return break continue int float double char bool void string true false class struct const static`

Keywords are case-sensitive. `If` is an identifier.

## 2. Identifiers

Start with a letter or `_`, followed by any number of letters, digits or `_`.
Regex: `[A-Za-z_][A-Za-z0-9_]*`. If the lexeme is in the keyword list it is a KEYWORD.

## 3. Numbers

- INTEGER: `[0-9]+` (no sign; `-5` is OPERATOR `-` then INTEGER `5`).
- FLOAT: digits `.` digits, optional exponent (`3.14`, `1.5e3`, `2E-2`), or digits with exponent (`1e5`).
- Not accepted as one token (confirm): `.5` and `1.` (lexed as `.` + `5`, and `1` + `.`).
- A number immediately followed by letters/underscore (`9bad`, `1.5abc`) is one INVALID token.

## 4. Operators and symbols

- OPERATOR (two chars): `== != <= >= && || ++ -- += -= *= /= %= ->`
- OPERATOR (one char): `+ - * / % = < > ! & | ^ ~`
- PUNCTUATION: `( ) { } [ ] ; , . : ?`
- STRING: `"..."` on one line, backslash escapes the next char. Lexeme includes the quotes.
- Longest match wins (`>=` is one token, not `>` `=`).

## 5. Comments and whitespace

- Whitespace (space, tab, newline, CR) is skipped. Newline increments the line number and resets column to 1.
- `// ...` runs to end of line. `/* ... */` may span lines (no nesting).
- Comments produce no tokens.

## 6. Invalid cases

Each produces an INVALID token (the lexer keeps going):

- illegal character: `@ $ # ` + "`" + ` \ ' ` and any non-ASCII byte
- number glued to letters: `9bad`, `1.5abc`
- unterminated string (no closing `"` before end of line)
- unterminated block comment (**expected INVALID, see docs/lexer-bug-report.md BUG-1**)
- char literals `'a'` are not supported (confirm)

## 7. Output format

One token per line: `TYPE(lexeme) line:col`, lines and columns start at 1.
End of input prints `END_OF_FILE line:col` (no lexeme). The summary
(`Total tokens: N, invalid: M`) goes to stderr, so stdout is only tokens.
Exit code: 0 = no INVALID tokens, 2 = at least one INVALID, 1 = usage / file error.

Example (`int x = 5;`):

```
KEYWORD(int) 1:1
IDENTIFIER(x) 1:5
OPERATOR(=) 1:7
INTEGER(5) 1:9
PUNCTUATION(;) 1:10
END_OF_FILE 1:11
```

## 8. Test files

Valid (`tests/scanner/valid/valid01..10.txt`, lexer must exit 0):

| File | Covers |
|---|---|
| valid01 | declaration, `if`, arithmetic |
| valid02 | floats, exponents |
| valid03 | `while` loop |
| valid04 | strings and escapes |
| valid05 | comparison / logical operators |
| valid06 | compound assignment, `++`/`--` |
| valid07 | function definition |
| valid08 | block and line comments |
| valid09 | `for` loop |
| valid10 | `_` and digits in identifiers, `true`/`false` |

Invalid (`tests/scanner/invalid/invalid01..10.txt`, lexer must exit 2):

| File | Covers |
|---|---|
| invalid01 | `@` and `$` |
| invalid02 | `9bad` |
| invalid03 | unterminated string |
| invalid04 | `#` |
| invalid05 | backtick |
| invalid06 | char literal `'a'` |
| invalid07 | unterminated block comment |
| invalid08 | `1.5abc` |
| invalid09 | non-ASCII `é` |
| invalid10 | stray backslash |

Run: `ctest --test-dir build --output-on-failure`

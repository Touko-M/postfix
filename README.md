# Postfix Calculator

A stack-based postfix (Reverse Polish) calculator in C++.
Built as a course assignment for Data Structures and Algorithms.

## Compilation
```bash
g++ main.cpp -o erkki
```

## Usage

### DC mode
Run the program and type a postfix expression directly:
```bash
./erkki
1 3 + 7.5 -
-3.5
```

### Prompt mode
Run with `-p` flag for an INTERACTIVE MENU-DRIVEN INTERFACE(wow):
```bash
./erkki -p
```

## Commands

### Arithmetic
| Command | Description |
|---------|-------------|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |
| `%` | Modulo |
| `^` | Exponentiation |
| `v` | Square root |

### Stack operations
| Command | Description |
|---------|-------------|
| `x` | Exchange top two elements |
| `s` | Sum all elements |
| `a` | Average of all elements |

### Prompt mode only
| Command | Description |
|---------|-------------|
| `?` | Push a number onto the stack |
| `=` | Print top of stack |
| `q` | Quit |

## Examples
```bash
# 2 raised to the exponent 8
./erkki
2 8 ^
256

# Average of 1 through 5
./erkki
1 2 3 4 5 a
3

# Swap and subtract (2 - 1 instead of 1 - 2)
./erkki
1 2 x -
1
```

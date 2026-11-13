# password-generator

# Password Generator

A simple command-line password generator written in C++.

## Features

- Generates a random password from letters (upper and lower case), digits, and symbols
- Fixed length, set by the `length` constant in the source (default: 20)
- Uses `uniform_int_distribution`, so every character is equally likely

## Build and run

Requires a C++ compiler such as `g++`.

```bash
g++ -o password main.cpp
./password
```

Example output:

```
aG7!kQ2x-Lm9Pz4#wR8e
```

## Known limitations

- **Not cryptographically secure.** Passwords are generated with `mt19937` seeded from the system clock, so the output is predictable if the seed is guessed. Do not use this for real accounts yet.
- The length and character set are fixed in the source.
- There is no guarantee that a password contains at least one digit or symbol.

## Roadmap

- [ ] Replace `mt19937` with a cryptographically secure source (OpenSSL `RAND_bytes`)
- [ ] Let the user choose the password length
- [ ] Return the password from `Password()` instead of printing it, so other code can reuse it
- [ ] Guarantee at least one character from each class (lowercase, uppercase, digit, symbol)

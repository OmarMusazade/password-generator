# Password Generator

A simple command-line password generator written in C++, being developed step by step into a small encrypted password manager.

## Features

- Generates a random password from letters (upper and lower case), digits, and symbols
- Uses OpenSSL `RAND_bytes` (a cryptographically secure random source)
- Rejection sampling, so every character is equally likely (no modulo bias)
- Fixed length, set by the `length` constant in the source (default: 20)

## Build and run

Requires a C++ compiler and the OpenSSL development headers (`sudo dnf install openssl-devel` on RHEL/Fedora).

```bash
clang++ -std=c++20 pass_gen.cpp -o password -lcrypto
./password
```

## Known limitations

- The length and character set are fixed in the source.
- There is no guarantee that a password contains at least one digit or symbol.
- Passwords are only printed to the terminal, not stored.

## Roadmap

**Generator**
- [x] Replace `mt19937` with a cryptographically secure source (OpenSSL `RAND_bytes`)
- [ ] Let the user choose the password length
- [ ] Return the password from `Password()` instead of printing it, so other code can reuse it
- [ ] Guarantee at least one character from each class (lowercase, uppercase, digit, symbol)

**Password manager**
- [ ] Split the code into modules (generator, crypto, storage)
- [ ] Save generated passwords to an encrypted file (AES-256-GCM, key derived from a master password with PBKDF2)
- [ ] Add commands to add, list, and retrieve entries

## License

See [LICENSE](LICENSE).

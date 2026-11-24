# Password Generator

A command-line password generator written in C++, being developed step by step into a small encrypted password manager.

## Features

- Generates a random password from lowercase and uppercase letters, digits, and symbols (76 characters in total)
- Password length is read from standard input (4 to 128)
- Every password contains at least one lowercase letter, one uppercase letter, one digit, and one symbol, each chosen with its own random value
- The characters are shuffled with a Fisher-Yates shuffle, so the guaranteed characters do not always appear first
- Uses OpenSSL `RAND_bytes`, a cryptographically secure random source
- Rejection sampling: random bytes that are not valid indexes are discarded instead of being folded in with `%`, so every character is equally likely (no modulo bias)
- If the random generator fails, the program prints an error to stderr and exits with code 1 instead of producing a password

## Build and run

Requires a C++ compiler and the OpenSSL development headers (`sudo dnf install openssl-devel` on RHEL/Fedora).

```bash
clang++ -std=c++20 -Wall -Wextra pass_gen.cpp -o password -lcrypto
./password
```

Example session:

```
Enter the length of the password (between 4-128)
20
aG7!kQ2x-Lm9Pz4#wR8e
```

## How it works

1. `RAND_bytes` fills a buffer with random bytes (0 to 255).
2. For each of the four character classes, the first byte that is a valid index into that class selects one character. Bytes that are too large are discarded.
3. The rest of the password is filled from the full alphabet in the same way, until it reaches the requested length.
4. The result is shuffled with Fisher-Yates: a random character is repeatedly removed from the remaining ones and appended to the new password.

## Known limitations

- Passwords are limited to 128 characters, because the shuffle selects positions with a single random byte.
- The character set is fixed in the source.
- Passwords are only printed to the terminal, not stored, and they are not wiped from memory after use.

## Roadmap

**Generator**
- [x] Replace `mt19937` with a cryptographically secure source (OpenSSL `RAND_bytes`)
- [x] Return the password from `Password()` instead of printing it, so other code can reuse it
- [x] Guarantee at least one character from each class (lowercase, uppercase, digit, symbol)
- [x] Choose each guaranteed character with its own random value
- [x] Let the user choose the password length

**Password manager**
- [ ] Split the code into modules (generator, crypto, storage)
- [ ] Save generated passwords to an encrypted file (AES-256-GCM, key derived from a master password with PBKDF2)
- [ ] Add commands to add, list, and retrieve entries

## License

See MIT [LICENSE](LICENSE).

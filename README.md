# Password Generator

A command-line password generator written in C++, being developed step by step into a small encrypted password manager.

## Features

- Generates a random password from lowercase and uppercase letters, digits, and symbols (76 characters in total)
- Uses OpenSSL `RAND_bytes`, a cryptographically secure random source
- Rejection sampling: random bytes outside the valid index range are discarded, so every character is equally likely (no modulo bias)
- Password length is set by the `length` constant in the source (default: 20)
- If the random generator fails, the program prints an error to stderr and exits with code 1 instead of producing a password

## Build and run

Requires a C++ compiler and the OpenSSL development headers (`sudo dnf install openssl-devel` on RHEL/Fedora).

```bash
clang++ -std=c++20 pass_gen.cpp -o password -lcrypto
./password
```

Example output:

```
aG7!kQ2x-Lm9Pz4#wR8e
```

## How it works

1. `RAND_bytes` fills a buffer with random bytes (0 to 255).
2. Bytes that are valid indexes into the alphabet are used to pick a character. All other bytes are discarded, which avoids the bias that `byte % alphabet.length()` would introduce.
3. This repeats until the password reaches the requested length.

## Known limitations

- The length and character set are fixed in the source.
- There is no guarantee that a password contains at least one lowercase letter, uppercase letter, digit, and symbol, so some passwords may lack a symbol.
- Passwords are only printed to the terminal, not stored.

## Roadmap

**Generator**
- [x] Replace `mt19937` with a cryptographically secure source (OpenSSL `RAND_bytes`)
- [x] Return the password from `Password()` instead of printing it, so other code can reuse it
- [ ] Guarantee at least one character from each class (lowercase, uppercase, digit, symbol)
- [ ] Let the user choose the password length

**Password manager**
- [ ] Split the code into modules (generator, crypto, storage)
- [ ] Save generated passwords to an encrypted file (AES-256-GCM, key derived from a master password with PBKDF2)
- [ ] Add commands to add, list, and retrieve entries

## License

See [LICENSE](MIT).

# Password Generator

A command-line password generator written in C++, being developed step by step into a small encrypted password manager.

## Features

- Generates a random password from lowercase and uppercase letters, digits, and symbols (76 characters in total)
- Every password contains at least one lowercase letter, one uppercase letter, one digit, and one symbol; the characters are shuffled afterwards so their positions are not predictable
- Uses OpenSSL `RAND_bytes`, a cryptographically secure random source
- Rejection sampling: random bytes that are not valid indexes are discarded, so every character is equally likely (no modulo bias)
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
2. The generator picks one character from each class, using bytes that are valid indexes.
3. The rest of the password is filled from the full alphabet, again discarding bytes that are not valid indexes, until the password reaches the requested length.
4. The result is shuffled by repeatedly removing a randomly chosen character and appending it to a new string.

## Known limitations

- The length and character set are fixed in the source.
- The four guaranteed characters are chosen using a single random value, so they carry less randomness than the rest of the password.
- Passwords are only printed to the terminal, not stored.

## Roadmap

**Generator**
- [x] Replace `mt19937` with a cryptographically secure source (OpenSSL `RAND_bytes`)
- [x] Return the password from `Password()` instead of printing it, so other code can reuse it
- [x] Guarantee at least one character from each class (lowercase, uppercase, digit, symbol)
- [ ] Choose each guaranteed character with its own random value
- [ ] Let the user choose the password length

**Password manager**
- [ ] Split the code into modules (generator, crypto, storage)
- [ ] Save generated passwords to an encrypted file (AES-256-GCM, key derived from a master password with PBKDF2)
- [ ] Add commands to add, list, and retrieve entries

## License

See [LICENSE](MIT).

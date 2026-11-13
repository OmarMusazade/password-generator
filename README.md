# Password Generator

A simple command-line password generator written in C++, being developed step by step into a small encrypted password manager.

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
- Passwords are only printed, not stored.

## Roadmap

**Generator**
- [ ] Replace `mt19937` with a cryptographically secure source (OpenSSL `RAND_bytes`)
- [ ] Let the user choose the password length
- [ ] Return the password from `Password()` instead of printing it, so other code can reuse it
- [ ] Guarantee at least one character from each class (lowercase, uppercase, digit, symbol)

**Password manager**
- [ ] Split the code into modules (generator, crypto, storage)
- [ ] Save generated passwords to an encrypted file (AES-256-GCM, key derived from a master password with PBKDF2)
- [ ] Add commands to add, list, and retrieve entries
- [ ] Evolve into a small encrypted password manager

## Security notes

Planned design for the encrypted storage:

- The key is derived from a master password using PBKDF2 with a random salt
- Each encryption uses a fresh random IV/nonce
- The master password and the key are never written to disk
- The password file is excluded from version control via `.gitignore`

## License

To be added.

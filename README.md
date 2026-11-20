Enigma Machine Simulation in C

About the Project

This project is a C language simulation of the historical Enigma Machine used during World War II.

It allows users to encrypt and decrypt messages using rotor-based encryption.

Features

- Encrypt text messages
- Decrypt encrypted messages
- Three rotor simulation
- Reflector system
- Plugboard configuration
- Custom rotor starting positions
- Supports spaces and basic punctuation

Requirements

- Windows / Linux
- GCC compiler
- Terminal or Command Prompt

How to Compile

Open the terminal in the project folder and run:

gcc enigma.c -o enigma

How to Run

On Windows:

.\enigma.exe

On Linux:

./enigma

How to Encrypt a Message

1. Run the program.
2. Select option "1" for Encryption.
3. Enter rotor starting positions, for example "AAA".
4. Enter plugboard pairs or "-" for no plugboard connections.
5. Enter your message.
6. Copy the encrypted output.

How to Decrypt a Message

1. Run the program again.
2. Select option "2" for Decryption.
3. Enter the same rotor starting positions used during encryption.
4. Enter the same plugboard configuration.
5. Paste the encrypted message.
6. The original message will be displayed.

Important

The receiver must use exactly the same rotor starting positions and plugboard settings to decrypt the message correctly.

Example

Original Message:

HELLO WORLD

Starting Position:

AAA

Plugboard:

-

The program generates an encrypted message. Use that exact output for decryption.

Learning Outcomes

- C programming
- Functions and arrays
- String handling
- Character manipulation
- Basic encryption and decryption concepts
- Understanding rotor-based cipher systems

Disclaimer

This is an educational simulation inspired by the historical Enigma Machine. It is not suitable
for protecting real or sensitive information.

CREATED BY :~~ OM GHUGE

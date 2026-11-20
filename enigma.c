#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26
#define MAX 1000

// Historical Enigma I Rotor Wiring
const char rotorI[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char rotorII[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char rotorIII[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";

// Historical Reflector B
const char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

// Rotor notch positions
#define NOTCH_I 16
#define NOTCH_II 4
#define NOTCH_III 21

int pos[3] = {0, 0, 0};

// Plugboard
char plugboard[SIZE];

// Initialize plugboard
void initPlugboard()
{
    for (int i = 0; i < SIZE; i++)
    {
        plugboard[i] = 'A' + i;
    }
}

// Configure plugboard
int configurePlugboard(char input[])
{
    int used[SIZE] = {0};
    int count = 0;
    char first = 0;

    initPlugboard();

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)input[i]))
        {
            char c = toupper((unsigned char)input[i]);
            int index = c - 'A';

            if (used[index])
                return 0;

            used[index] = 1;

            if (first == 0)
            {
                first = c;
            }
            else
            {
                plugboard[first - 'A'] = c;
                plugboard[index] = first;

                first = 0;
                count++;
            }
        }
        else if (!isspace((unsigned char)input[i]) &&
                 input[i] != '-')
        {
            return 0;
        }
    }

    if (first != 0 || count > 10)
        return 0;

    return 1;
}

// Plugboard conversion
int plug(int c)
{
    return plugboard[c] - 'A';
}

// Forward rotor conversion
int forwardRotor(const char wiring[], int c, int position)
{
    int shifted = (c + position) % SIZE;
    int output = wiring[shifted] - 'A';

    return (output - position + SIZE) % SIZE;
}

// Reverse rotor conversion
int reverseRotor(const char wiring[], int c, int position)
{
    int shifted = (c + position) % SIZE;
    int output = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (wiring[i] - 'A' == shifted)
        {
            output = i;
            break;
        }
    }

    return (output - position + SIZE) % SIZE;
}

// Rotor rotation
void rotateRotors()
{
    if (pos[1] == NOTCH_II)
    {
        pos[0] = (pos[0] + 1) % SIZE;
        pos[1] = (pos[1] + 1) % SIZE;
    }
    else if (pos[2] == NOTCH_III)
    {
        pos[1] = (pos[1] + 1) % SIZE;
    }

    pos[2] = (pos[2] + 1) % SIZE;
}

// Process one character
char processLetter(char letter)
{
    if (!isalpha((unsigned char)letter))
        return letter;

    int c = toupper((unsigned char)letter) - 'A';

    // Rotate rotors
    rotateRotors();

    // Plugboard
    c = plug(c);

    // Forward path
    c = forwardRotor(rotorIII, c, pos[2]);
    c = forwardRotor(rotorII, c, pos[1]);
    c = forwardRotor(rotorI, c, pos[0]);

    // Reflector
    c = reflector[c] - 'A';

    // Reverse path
    c = reverseRotor(rotorI, c, pos[0]);
    c = reverseRotor(rotorII, c, pos[1]);
    c = reverseRotor(rotorIII, c, pos[2]);

    // Plugboard again
    c = plug(c);

    return 'A' + c;
}

// Display rotor positions
void showPositions()
{
    printf("\nFinal Rotor Positions: %c %c %c\n",
           'A' + pos[0],
           'A' + pos[1],
           'A' + pos[2]);
}

// Main function
int main()
{
    char message[MAX];
    char start[100];
    char plugInput[100];
    int choice;

    printf("\n====================================");
    printf("\n       ENIGMA MACHINE SIMULATOR");
    printf("\n====================================");

    printf("\n\n1. Encrypt Message");
    printf("\n2. Decrypt Message");

    printf("\n\nEnter your choice: ");

    if (scanf("%d", &choice) != 1 ||
        (choice != 1 && choice != 2))
    {
        printf("\nInvalid choice!\n");
        return 1;
    }

    getchar();

    // Rotor starting positions
    printf("\nEnter 3 Rotor Starting Letters (Example: AAA): ");

    if (fgets(start, sizeof(start), stdin) == NULL ||
        strlen(start) < 3 ||
        !isalpha((unsigned char)start[0]) ||
        !isalpha((unsigned char)start[1]) ||
        !isalpha((unsigned char)start[2]))
    {
        printf("\nInvalid rotor positions!\n");
        return 1;
    }

    pos[0] = toupper((unsigned char)start[0]) - 'A';
    pos[1] = toupper((unsigned char)start[1]) - 'A';
    pos[2] = toupper((unsigned char)start[2]) - 'A';

    // Plugboard configuration
    printf("\nEnter Plugboard Pairs (Example: AB CD EF)");
    printf("\nEnter - for no pairs: ");

    if (fgets(plugInput, sizeof(plugInput), stdin) == NULL ||
        !configurePlugboard(plugInput))
    {
        printf("\nInvalid plugboard configuration!\n");
        return 1;
    }

    // Message input
    printf("\nEnter your message: ");

    if (fgets(message, sizeof(message), stdin) == NULL)
    {
        printf("\nInput error!\n");
        return 1;
    }

    // Output
    printf("\n====================================");

    if (choice == 1)
        printf("\nEncrypted Message: ");
    else
        printf("\nDecrypted Message: ");

    for (int i = 0; message[i] != '\0'; i++)
    {
        putchar(processLetter(message[i]));
    }

    showPositions();

    printf("\n====================================");
    printf("\nOperation Completed Successfully!\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 2000;

char *encoder(char *input_string)
{
    // The character set for base64 encoding scheme
    char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int len = strlen(input_string); // Length of the given string as input.
    int padding = 0;                // Used to find the number of '=' to be appended at the end of encoded string.
    int value = 0;                  // Used to store the temporary binary form while encoding.
    int index = 0;                  // Used to keep the track of number of characters in the encoded string.
    int bits_count = 0;             // Used to keep track of number of bits of the variable value.

    // Allocation of memory for the encoded string
    char *encoded_string = (char *)malloc(SIZE * sizeof(char));

    // Here we take 3 characters of the input string at a time
    // and store their value in variable value.

    for (int i = 0; i < len; i += 3)
    {
        value = 0;
        bits_count = 0;

        // Loop to take chunks of 3 characters starting at position i
        for (int j = i; j <= i + 2 && j < len; j++)
        {
            value = value << 8;              // Shift value by 8 bits as each character in the input string takes up 8 bits in binary form.
            value = value | input_string[j]; // Set the appropriate bits of the variable value.
            bits_count += 8;                 // Increment the bits_count by 8.
        }

        if (bits_count == 8)
        {
            // Append 4 zeros in the binary representation of value
            value = value << 4;
            bits_count += 4;
            padding = 2;
        }
        else if (bits_count == 16)
        {
            // Append 2 zeros in the binary representation of value
            value = value << 2;
            bits_count += 2;
            padding = 1;
        }

        for (int j = 6; j <= bits_count; j += 6)
        {
            // Convert the chunks of 24 bits into 4 base64 chars.

            int temp = value >> (bits_count - j);      // Consider the first j bits.
            int six_bits = temp % 64;                  // Of the above numbers consider the 6 Lowest significant bits
            char ch = base64[six_bits];                // Find appropriate character for the 6 bit code in base64 system.
            encoded_string[index++] = ch;              // Assign the character in the encoded string.
        }
    }

    for (int j = 0; j < padding; j++)
    {
        encoded_string[index++] = '=';
    }
    encoded_string[index] = '\0';

    return encoded_string;
}

int main()
{
    char input_str[] = "Tejas";
    int len_str;

    // calculates length of string
    len_str = sizeof(input_str) / sizeof(input_str[0]);

    // to exclude '\0' character
    len_str -= 1;

    printf("Input string is : %s\n", input_str);
    printf("Encoded string is : %s\n", encoder(input_str));
    return 0;
}
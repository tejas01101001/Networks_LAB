#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 2000;

char *decoder(char *encoded_string)
{
    int len = strlen(encoded_string); // Length of the given encoded string as input.
    int padding = 0;                  // The padding in the encoded decoded_string
    int value = 0;                    // Used to store the temporary binary form while decoding.
    int index = 0;                    // Used to keep the track of number of characters in the decoded string.
    int bits_count = 0;               // Used to keep track of number of bits of the variable value.

    // Allocation of memory for the decoded string
    char *decoded_string = (char *)malloc(SIZE * sizeof(char));

    // Here we take 4 characters of the encoded string at a time
    // and store their value in variable value.

    for (int i = 0; i < len; i += 4)
    {
        value = 0;
        bits_count = 24;
        padding = 0;

        for (int j = i; j <= i + 3 && j < len; j++)
        {
            int temp_index;
            if (encoded_string[j] >= 'A' && encoded_string[j] <= 'Z')
                temp_index = encoded_string[j] - 'A';
            else if (encoded_string[j] >= 'a' && encoded_string[j] <= 'z')
                temp_index = encoded_string[j] - 'a' + 26;
            else if (encoded_string[j] >= '0' && encoded_string[j] <= '9')
                temp_index = encoded_string[j] - '0' + 52;
            else if (encoded_string[j] == '+')
                temp_index = 62;
            else if (encoded_string[j] == '/')
                temp_index = 63;
            else if (encoded_string[j] == '=')
            {
                count++;
                continue;
            }
            value = value << 6;
            value = value | temp_index;
        }

        if (padding == 2)
        {
            value = value >> 4;
            bits_count = 8;
        }
        else if (padding == 1)
        {
            value = value >> 2;
            bits_count = 16;
        }

        for (int j = 8; j <= bits_count; j += 8)
        {
            int temp = value >> (bits_count - j);
            int ind = temp % 256;
            decoded_string[index++] = (char)ind;
        }
    }
    decoded_string[index] = '\0';
    return decoded_string;
}

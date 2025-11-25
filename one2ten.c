#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For usleep
#include <ctype.h>  // For isdigit

typedef struct s_data {
    char    *letters;   // The string of 10 chars (e.g., "asdfghjk")
    char    *digits;    // The string of numbers (e.g., "24381")
    int     speed;      // Speed of animation in microseconds
} t_data;

void info()
{
    printf("Usage: ./a.out <letters> <digits>\n");
    printf("Example: ./a.out asdfghjkl 012345\n");
}

/* * Validates that the digits string only contains numbers
 * and that the numbers don't ask for an index larger than the string length.
 */
int validate_input(t_data *d)
{
    int len_chars = strlen(d->letters);
    int len_digits = strlen(d->digits);

    for (int i = 0; i < len_digits; i++)
    {
        if (!isdigit(d->digits[i]))
        {
            printf("Error: Second argument must contain only digits (0-9).\n");
            return (0);
        }
        
        // Convert char '3' to int 3 using ASCII subtraction
        int index = d->digits[i] - '0'; 

        if (index >= len_chars)
        {
            printf("Error: Digit '%d' is too high for a string of length %d.\n", index, len_chars);
            return (0);
        }
    }
    return (1);
}

/*
 * Prints N spaces, then the character
 */
void print_at_position(char c, int pos)
{
    // Print 'pos' number of spaces
    for (int i = 0; i < pos; i++)
    {
        write(1, " ", 1);
    }
    // Print the character and a newline
    printf("%c\n", c);
}

int main(int ac, char* av[])
{
    t_data d;

    if (ac != 3)
    {
        info();
        return (1);
    }

    // Assign arguments to struct
    d.letters = av[1];
    d.digits = av[2];
    d.speed = 300000; // 0.3 seconds

    // Validate
    if (!validate_input(&d))
        return (1);

    printf("Displaying sequence...\n");
    printf("----------------------\n");

    // Loop through every number in the digits string
    int i = 0;
    while (d.digits[i] != '\0')
    {
        // 1. Get the numeric value (e.g., '3' becomes 3)
        int index = d.digits[i] - '0';

        // 2. Get the character at that index from the letters string
        char char_to_show = d.letters[index];

        // 3. Print it with padding
        print_at_position(char_to_show, index);

        // 4. Wait for visual effect
        fflush(stdout); // Ensure text appears before sleeping
        usleep(d.speed);
        
        i++;
    }

    printf("----------------------\n");
    printf("Finished.\n");
    return (0);
}
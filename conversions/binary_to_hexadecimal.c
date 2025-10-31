#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    char binary[65];   // up to 64 bits
    long decimal = 0;
    int i, len;

    printf("Enter a binary number: ");
    scanf("%64s", binary);  // read as string (safer)

    len = strlen(binary);

    // Validate and convert binary → decimal
    for (i = 0; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            printf("Invalid binary number!\n");
            return 1;
        }
        decimal = decimal * 2 + (binary[i] - '0');
    }

    // Print as hexadecimal
    printf("Equivalent hexadecimal value: %lX\n", decimal);

    return 0;
}

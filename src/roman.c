#include "roman.h"
#include <stdio.h>
#include <stdlib.h>

// Function to calculate string length (instead of using strlen)
int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to concatenate two strings (instead of using strcat)
void stringConcat(char* destination, const char* source) {
    int destLength = stringLength(destination);
    int i = 0;
    while (source[i] != '\0') {
        destination[destLength + i] = source[i];
        i++;
    }
    destination[destLength + i] = '\0'; // Null-terminate the result
}

// Function to convert an integer to a Roman numeral
char* toRoman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;  // Invalid input for Roman numerals
    }

    static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const char* symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    // Allocate memory for the result string (enough for a maximum of 15 characters for 3999)
    char* result = (char*)malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;  // Memory allocation failed
    }

    result[0] = '\0';  // Initialize result to an empty string

    // Loop through each Roman numeral and subtract the values
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            stringConcat(result, symbols[i]);
            num -= values[i];
        }
    }

    return result;  // Return dynamically allocated result
}

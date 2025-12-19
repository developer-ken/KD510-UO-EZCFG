#include <Arduino.h>

uint8_t char2index(char c)
{
    switch (c)
    {
    case '1':
        return 0;
    case '2':
        return 1;
    case '3':
        return 2;
    case '4':
        return 3;
    case '5':
        return 4;
    case '6':
        return 5;
    case '7':
        return 6;
    case '8':
        return 7;
    case '9':
        return 8;
    case '0':
        return 9;
    case 'A':
        return 10;
    case 'b':
        return 11;
    case 'C':
        return 12;
    case 'd':
        return 13;
    case 'E':
        return 14;
    case 'F':
        return 15;
    case 't':
        return 16;
    case 'H':
        return 17;
    case 'P':
        return 18;
    case 'q':
        return 19;
    case 'c':
        return 20;
    default:
        return 21;
    }
}

uint8_t digitsA[22] = {
    0b00010100, // 1
    0b11001110, // 2
    0b10011110, // 3
    0b00011101, // 4
    0b10011011, // 5
    0b11011011, // 6
    0b00010110, // 7
    0b11011111, // 8
    0b10011111, // 9
    0b11010111, // 0
    0b01011111, // A
    0b11011001, // b
    0b11000011, // C
    0b11011100, // d
    0b11001011, // E
    0b01001011, // F
    0b11001001, // t
    0b01011101, // H
    0b01001111, // P
    0b00011111, // q
    0b11001000, // c
    0b00001000  // -
};

uint8_t digitsB[22] = {
    0b00010010, // 1
    0b11001011, // 2
    0b10011011, // 3
    0b00011110, // 4
    0b10011101, // 5
    0b11011101, // 6
    0b00010011, // 7
    0b11011111, // 8
    0b10011111, // 9
    0b11010111, // 0
    0b01011111, // A
    0b11011100, // b
    0b11000101, // C
    0b11011010, // d
    0b11001101, // E
    0b01001101, // F
    0b11001100, // t
    0b01011110, // H
    0b01001111, // P
    0b00011111, // q
    0b11001000, // c
    0b00001000  // -
};
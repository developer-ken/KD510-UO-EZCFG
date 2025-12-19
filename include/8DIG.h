#ifndef _8DIG_H_
#define _8DIG_H_

#include <stdint.h>
extern uint8_t digitsA[22];
extern uint8_t digitsB[22];

#define DOTED(X) (X|0b00100000)

uint8_t char2index(char c);

#endif
#ifndef CARDS_H
#define CARDS_H

#include <stdint.h>

/* constants for the IDs of non-numeral cards, and their stored values
   aces have a stored value of -1 b/c aces can be either 1 or 11 */

#define ACE_TYPE 1
#define ACE_VALUE -1

#define JACK 11
#define QUEEN 12
#define KING 13
#define FACE_VALUE 10

// constants to define suits 

#define SPADES 0
#define CLUBS 1
#define HEARTS 2
#define DIAMONDS 3


typedef struct card_t
{
    int8_t suit;
    int8_t type;
    int8_t value;
} Card;

Card * Create_Card(int8_t seed);

void Card_Str(Card * card_obj, char * card_str, int buffersize);


#endif
#include "cards.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h> // for debugging

Card * Create_Card(int8_t seed)
{
    Card * temp = (Card *)malloc(sizeof(Card));

    temp->suit = seed % 4;
    temp->type = (seed / 4) + 1;

    if (temp->type == ACE_TYPE)
    {
        temp->value = ACE_VALUE;
    }
    else if (temp->type >= JACK) // includes `JACK`, `QUEEN`, and `KING`
    {
        temp->value = FACE_VALUE;
    }
    else
    {
        temp->value = temp->type;
    }

    return temp;
}

// arrays that contain all possible labels for a playing card 
const char *VALUE_LABELS[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
const char *SUIT_LABELS[] = {"Spades", "Clubs", "Hearts", "Diamonds"};

void Card_Str(Card * card_obj, char * card_str, int buffersize)
{
    // maximum size for a card's string is 18 
    // (5 for the type, 4 for "of", 8 for suit, 1 for 0 byte)
    // formatted like: 
    // {type} of {suit}\0

    // if string size is less than 18, return, just to be safe :)
    if (buffersize < 18)
    {
        printf("buffersize < 18, cannot safely copy string");
        strcpy(card_str, "");
        return;
    }
    else if (card_obj->type - 1 > 12 || card_obj->suit > 3)
    {
        printf("type = %d; suit = %d; value = %d\n", card_obj->type, card_obj->suit, card_obj->value);
        strcpy(card_str, "ERROR");
        return;
    }

    strcpy(card_str, VALUE_LABELS[card_obj->type - 1]);
    strcat(card_str, " of ");
    strcat(card_str, SUIT_LABELS[card_obj->suit]);

    return;
}
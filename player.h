#ifndef PLAYER_H
#define PLAYER_H

#include "cards.h"
#include "linked_list.h"

#include <stdbool.h>

typedef struct player_s
{
    /* `hand` stores `Card` objects
     *
     * `hand_val` stores the value of the player's hand
     * 
     * `busted` stores whether or not the player busted (that's what she said)
     */
    linked_list_t * hand;
    uint8_t hand_val;

    bool busted;
} Player;


Player Create_Player();
void calculate_hand_val(Player * player);
void print_hand(Player * player);

#endif
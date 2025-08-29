#include "player.h"

#include <stdio.h>
#include <stdlib.h>

Player Create_Player()
{
    Player temp;

    temp.hand = create_linked_list(sizeof(Card));
    temp.hand_val = 0;
    temp.busted = false;

    return temp;
}

void calculate_hand_val(Player * player)
{
    uint8_t hand_val = 0;
    uint8_t num_aces = 0;

    Card * temp_card = NULL;

    // iterate through the list 
    // count up the number of aces
    // add all non-ace cards to the hand value
    for (int32_t i = 0; i < player->hand->list_size; ++i)
    {
        temp_card = (Card *)get_element(player->hand, i);

        if (temp_card->value != ACE_VALUE)
        {
            hand_val += temp_card->value;
        }
        else
        {
            num_aces++;
        }
    }

    // printf("\nnum aces = %d\n", num_aces);

    // choose if each ace is worth 11 points or 1 point
    for (uint8_t i = 0; i < num_aces; ++i)
    {
        if (hand_val <= 10)
        {
            hand_val += 11;
        }
        else
        {
            hand_val++;
        }
    }

    player->hand_val = hand_val;

    return;
}

void print_hand(Player * player)
{
    char buff[20];

    for (int32_t i = 0; i < player->hand->list_size; ++i)
    {
        Card_Str((Card *)get_element(player->hand, i), buff, 20);

        printf("%s\n", buff);
    }
}
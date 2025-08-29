#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "cards.h"
#include "linked_list.h"
#include "player.h"

#define PLAYER_IDX 0
#define AI_IDX     1

#define DELAY 250

// generates a random number from floor to ceil (inclusive for both)
int rand_bounded(int floor, int ceil)
{
    int temp = rand() % (ceil - floor  + 1) + floor;
    return temp;
}

// timed delay
void delay(uint32_t num_millisecs)
{
    clock_t start_time = clock();

    while (clock() < start_time + num_millisecs);
}

int main(int argc, char ** argv)
{
    // print welcome message 
    printf("Welcome to Blackjack in C!\n\n");

    bool playing = true;

    while (playing)
    {
        printf("\n--------------------\n\n");

        // initialize deck
        linked_list_t * deck = create_linked_list(sizeof(linked_list_t));

        srand(time(0));

        // // string buffer used for storing/printing out card names (only needed for testing)
        // char buff[20];

        // populate deck with cards 
        for (int8_t seed = 0; seed < 52; ++seed)
        {
            Card * temp = Create_Card(seed);
            add_element(deck, (void *)temp);
        }
        
        // // print deck for testing purposes
        // for (int32_t i = 0; i < deck->list_size; ++i)
        // {
        //     Card_Str((Card *)get_element(deck, i), buff, 20);

        //     printf("%d: %s\n", i, buff);
        // }


        Player player_array[2];

        // initiailize the player 
        player_array[PLAYER_IDX] = Create_Player();
        // initialize the ai player
        player_array[AI_IDX] = Create_Player();

        for (uint8_t i = 0; i < 2; ++i)
        {

            for (uint8_t j = 0; j < 2; ++j)
            {
                int32_t idx = rand_bounded(0, deck->list_size - 1);
                // printf("idx = %d; len = %d\n", idx, deck->list_size);

                // add a card to the player's hand and then remove it from the deck
                // this action was originally stored in a `pop` function, but uhhhhh
                // took me like 2 hours to debug why aces weren't working and for some reason it was the pop function
                // so i'm going to write both of these functions instead
                add_element(player_array[i].hand, get_element(deck, idx));
                remove_element(deck, idx);
            }

            calculate_hand_val(&player_array[i]);

            // printf("Player %d Hand Value: %d\n", i, player_array[i].hand_val);
            // print_hand(&player_array[i]);
        }

        // --START OF PLAYER'S TURN-- //

        printf("Your turn!\n\n");

        bool is_hitting = true;
        char input_char = 0;

        // pointer to the first item in the player array
        // useful so i don't have to keep retyping the array
        Player * user_player = &player_array[PLAYER_IDX];

        while (is_hitting)
        {
            printf("Your hand:\n");
            print_hand(user_player);
            printf("\nYour hand value: %d\n", user_player->hand_val);
            printf("\nHit or stand?\n");

            // gather user input until they submit something that actually works
            while (input_char != 'h' && input_char != 'H' && input_char != 's' && input_char != 'S')
            {
                input_char = (char)getchar();
                
                // clears the input buffer
                // https://www.geeksforgeeks.org/cpp/clearing-the-input-buffer-in-cc/
                while (getchar() != '\n');
            }

            // hit! 
            if (input_char == 'h' || input_char == 'H')
            {
                int32_t idx = rand_bounded(0, deck->list_size - 1);
                add_element(user_player->hand, get_element(deck, idx));
                remove_element(deck, idx);

                calculate_hand_val(user_player);

                // handle if the player busted
                if (user_player->hand_val > 21)
                {
                    printf("\nBust!\n\nYour hand:\n");
                    print_hand(user_player);
                    printf("\nYour hand value: %d\n", user_player->hand_val);

                    user_player->busted = true;
                    is_hitting = false;
                }
                else
                {
                    printf("\n");
                }
            }
            // stand!
            else if (input_char == 's' || input_char == 'S')
            {
                is_hitting = false;
            }

            input_char = 0;
        }

        // --END OF PLAYER'S TURN-- //

        // --START OF THE AI'S TURN-- //

        is_hitting = true;

        Player * ai_player = &player_array[AI_IDX];

        printf("\n\nAI's turn!\n");

        while (is_hitting)
        {
            /* if hand value is greater than or equal to 17:
            * stand
            * else:
            * hit and check for bust
            */

            delay(DELAY);

            // stand!
            if (ai_player->hand_val >= 17)
            {
                printf("\nStand!\n");
                is_hitting = false;
            }
            // hit!
            else
            {
                printf("\nHit!\n");

                int32_t idx = rand_bounded(0, deck->list_size - 1);
                add_element(ai_player->hand, get_element(deck, idx));
                remove_element(deck, idx);

                calculate_hand_val(ai_player);

                // bust!
                if (ai_player->hand_val > 21)
                {
                    printf("\nBust!\n");

                    ai_player->busted = true;
                    is_hitting = false;
                }
            }
        }

        delay(DELAY * 2);

        printf("\nAI's hand:\n");
        print_hand(ai_player);
        printf("\nAI's hand value: %d\n", ai_player->hand_val);

        delay(DELAY * 2);

        // win conditions
        // please ignore these boolean expressions, i know they're not pretty
        // but idgaf
        if ((user_player->hand_val > ai_player->hand_val && user_player->busted == false) || (ai_player->busted == true && user_player->busted == false))
        {
            printf("\nYou win!\n");
        }
        else if ((user_player->hand_val < ai_player->hand_val && ai_player->busted == false) || (user_player->busted == true && ai_player->busted == false))
        {
            printf("\nYou lose!\n");
        }
        // tie condition, don't need a conditional here
        else
        {
            printf("\nTie!\n");
        }


        free_list(user_player->hand);
        free_list(ai_player->hand);
        free_list(deck);

        printf("\nDo you want to play again? (y/n)\n");

        // gather user input until they submit something that actually works
        while (input_char != 'y' && input_char != 'Y' && input_char != 'n' && input_char != 'N')
        {
            input_char = (char)getchar();
            
            // clears the input buffer
            // https://www.geeksforgeeks.org/cpp/clearing-the-input-buffer-in-cc/
            while (getchar() != '\n');
        }

        if (input_char == 'n' || input_char == 'N')
        {
            playing = false;
        }
        // i don't need to check if the answer is yes here, since it won't change any variable states
        
    }

    printf("\nThank you for playing!\n\n");

    return 0;
}
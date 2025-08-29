/* Rosa Knowles
 * 8/10/2025
 * 
 * Function definitions for `linked_list.h`
 */

#include "linked_list.h"

// malloc :-)
#include <stdlib.h>
// for memcpy
#include <string.h>
#include <stdio.h>

node_t * create_node()
{
    // creates a `node_t` struct with null elements and returns it

    node_t * temp = (node_t *)malloc(sizeof(node_t));

    temp->data = NULL;
    temp->next = NULL;

    return temp;
}


linked_list_t * create_linked_list(size_t data_size_i)
{
    // creates a `linked_list_t` struct and returns it
    // the returned struct will essentially be an empty list

    linked_list_t * temp = (linked_list_t *)malloc(sizeof(linked_list_t));

    temp->head = NULL;
    
    temp->list_size = 0;
    temp->data_size = data_size_i;

    return temp;
}


void add_element(linked_list_t * list, void * data_i)
{
    /* Creates a new node, and stores it at the beginning of the list
     * it's faster to do it this way rather than putting it in the back, 
     * since iterating to the back of the list is an O(n) operation, while
     * inserting the element at the beginning of the list is an O(1) operation
     */

    node_t * new_node = create_node();

    new_node->data = malloc(list->data_size);
    new_node->next = list->head;

    list->head = new_node;

    // copy `data_i` into `new_node->data`
    memcpy(new_node->data, data_i, list->data_size);

    list->list_size += 1;

    return;
}


int remove_element(linked_list_t * list, int32_t index)
{
    // index out of bounds error
    if (index > list->list_size -1 || index < 0)
    {
        return ERROR_CODE;
    }
    else if (index == 0)
    {
        node_t * goner_node = list->head;

        list->head = goner_node->next;

        free(goner_node->data);
        free(goner_node);
    }
    else
    {
        /* Finds the element before the element you wish to delete
         * changes around pointers and frees memory! it's like it was never there...
         */
        node_t * before_node = list->head;

        for (int32_t i = 0; i < index - 1; ++i)
        {
            before_node = before_node->next;
        }

        node_t * goner_node = before_node->next;
        before_node->next = goner_node->next;

        free(goner_node->data);
        free(goner_node);
    }


    list->list_size -= 1;
    return SUCCESS_CODE;
}


void * get_element(linked_list_t * list, int32_t index)
{
    // index out of bounds error
    if (index > list->list_size -1 || index < 0)
    {
        return NULL;
    }

    // iterates through the list and returns the data at the specific index

    node_t * node_at_idx = list->head;

    for (int32_t i = 0; i < index; ++i)
    {
        node_at_idx = node_at_idx->next;
        // printf("%d\n", *(int *)node_at_idx->data);
        // printf("%d\n",node_at_idx);
    }

    return node_at_idx->data;
}

void free_list(linked_list_t * list)
{
    // remove each of the individual elements from the list
    // deletes the first element of the list while the list's size is greater than 0
    while (list->list_size > 0)
    {
        remove_element(list, 0);
    }

    // free the list and set the list to a null pointer
    free(list);
    list = NULL;
}

void debug_list(const linked_list_t * list)
{
    printf("List size: %d nodes\nData size: %d bytes\n", list->list_size, list->data_size);
    return;
}
/* Rosa Knowles
 * 8/10/2025
 * 
 * Header file for linked lists that use *gulp* void pointers
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define ERROR_CODE   1
#define SUCCESS_CODE 0

#include <stdint.h>

typedef struct node_s
{
    /* `data` stores the data of the node as a void pointer
     * needs to be casted before dereferenced 
     * 
     * `next` stores a pointer to the next node in the linked list
     */

    void * data;
    struct node_s * next;
} node_t;

typedef struct linked_list_s
{
    /* `head` stores the first entry in the linked list
     * will be reassigned as the list gets new entries
     * 
     * `list_size` stores the number of nodes in the list
     * 
     * `data_size` stores the size of the data the list stores
     * used for memory allocation when adding a new item to the list
     */

    node_t * head;

    int32_t list_size;
    size_t data_size;
} linked_list_t;

// --- FUNCTION DECLARATIONS --- //

// struct initializer functions
node_t * create_node();
linked_list_t * create_linked_list(size_t data_size_i);

// function to add an element to the linked list
void add_element(linked_list_t * list, void * data_i);
// function to remove an element from the linked list
int remove_element(linked_list_t * list, int32_t index);
// function to retrieve an element from the linked list
// returns `NULL` if the element is out of the bounds of the linked list
void * get_element(linked_list_t * list, int32_t index);
// used to destroy a linked list and all of its contents
void free_list(linked_list_t * list);

// print list size and data size
void debug_list(const linked_list_t * list);

#endif
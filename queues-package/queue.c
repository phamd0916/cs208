/*
Doug Pham
queue.c
 * Starter file for CS 208 assignment: Queues in C
 * Adapted by Aaron Bauer and then Jeff Ondich
 * from a lab developed at CMU by R. E. Bryant, 2017-2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    // TODO check if malloc returned NULL (this means space could not be allocated)
    if(q == NULL){
      return NULL;
    }
    //Instantiates variables of q
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *new_node;

    // What if q is NULL?
    if(q == NULL){
      return;
    }
    // TODO free the queue nodes
    while(q->head != NULL){
      new_node = q->head->next;
      free(q->head->value);
      free(q->head);
      q->head = new_node;

      // loop through until next pointer points to null and then begin to
      // assign new node to point to same as tail and free both
    }

    /* You'll want to loop through the list nodes until the next pointer is NULL,
     * starting at the head, freeing each node and its value. 
     * Account for an empty list (head is NULL). */

    // Freeing queue structure itself
    // free(new_node);
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *new_node;
    // TODO check if q is NULL; what should you do if so?
    if(q == NULL) {
      return false;
    }
    // TODO Create a new node, copy the string s into its value.
    new_node = malloc(sizeof(list_ele_t)); // allocates space on a the heap for the new node
    // TODO check if malloc returned NULL
    if(new_node == NULL){
      return false;
    }
    // TODO use malloc to allocate space for the value and copy s to value
    new_node->value = malloc(strlen(s) * (sizeof(s) + 1));
    // If this second malloc call returns NULL, you need to free new_node before returning
    if(new_node->value == NULL){
      free(new_node);
      return false;
    }
    
    strcpy(new_node->value, s);
    // TODO Hey wait a second. Aren't we also gonna do q_insert_tail? Should
    // we maybe write a utility function to allocate and return a new node so
    // we can reuse it there?
    
    // Connect the new node to the front of the queue and increment size
    new_node->next = q->head;
    q->head = new_node;
    q->size++;
    // TODO if the list was empty, the tail might also need updating, however it
    // is you're implementing the notion of tail.
    if(q->tail == NULL){
      q->tail = new_node;
      new_node->next = NULL;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *new_node;
    // TODO check if q is NULL; what should you do if so?
    if(q == NULL) {
      return false;
    }

    // TODO Create a new node, copy the string s into its value.
    new_node = malloc(sizeof(list_ele_t)); // allocates space on a the heap for the new node

    // TODO check if malloc returned NULL
    if(new_node == NULL){
      return false;
    }

    new_node->value = malloc(strlen(s) * sizeof(s));
    // If this second malloc call returns NULL, you need to free new_node before returning
    if(new_node->value == NULL){
      free(new_node);
      return false;
    }
    strcpy(new_node->value, s);
    new_node->next = NULL;
    // if first item into queue
    if(q->tail == NULL){
      q->tail = new_node;
    }
    else{
      q->tail->next = new_node;
      q->tail = new_node;
    }

    // TODO implement in similar fashion to q_insert_head
    // You'll certainly want to add a field to queue_t so we can access
    // the tail efficiently.
    // TODO If the list was empty, the head might also need updating
    q->size++;
    if(q->head == NULL){
      q->head = new_node;
    }
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *pointer;
    // TODO check if q is NULL or empty
    if(q == NULL || q->head == NULL){
      return false;
    }
    // TODO if sp is not NULL, copy value at the head to sp
    if (sp == NULL){
      return false;
    }
    // Use strncpy (http://www.cplusplus.com/reference/cstring/strncpy/)

    if (strlen(q->head->value) > bufsize){
      strncpy(sp, q->head->value, bufsize);
      sp[bufsize - 1] = '\0';
    } else if (bufsize == 0){
      sp[0] = '\0';
    } else {
      strncpy(sp, q->head->value, bufsize);
    }

    // bufsize is the number of characters already allocated for sp
    // Think about:
    //    - what should happen if q->head->value is longer than bufsize?
    //    - what should happen if bufsize == 0?
    //    - under what conditions will strncpy copy the \0 character
    //        into sp, and when will it fail to do so (so you'll have
    //        to insert a \0 manually)?

    // TODO update q->head to remove the current head from the queue
    pointer = q->head;
    q->head = q->head->next;
    q->size--;
    // TODO if the last list element was removed, the tail might need updating
    if (q->head == NULL){
      q->tail = NULL;
    }
    // TODO hey, did you forget to free the removed list element?
    free(pointer->value);
    free(pointer);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    // TODO implement this function. If you add a field to queue_t
    // to keep track of the number of nodes in the queue, then this
    // function is fast-running and easy to write. But it also means
    // you have to be very careful about keeping track of the number
    // of nodes elsewhere in your code.

    // TODO what if q == NULL or q->head == NULL?
    if(q == NULL || q->head == NULL){
      return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *prev;
    list_ele_t *curr;
    list_ele_t *next;
    list_ele_t *temp;
    // TODO good luck! this is fun when it works
    // Check if queue or head is null
    if (q == NULL || q->head == NULL){
      return;
    }
    // Set our variables
    prev = NULL;
    curr = q->head;
    // Keep track of tail
    temp = q->tail;

    // Loop through queue reversing nodes to point to previous nodes
    while (curr != NULL){
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    // Reseting our head and tail
    q->tail = q->head;
    q->head = temp;
}

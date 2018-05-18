
#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

/**
 * @brief This module defines an implementation for an "obtrusive" doubly linked list.
 *
 * This module defines a generic list structure and several methods to manipulate
 * that structure as a list.  The implementation gives fast access to the head
 * and the tail of the list.
 *
 * The initial ListNode structure is a "sentinal" node and should be used as the
 * value passed to any of the methods that require the sentinal node in their definition.
 *
 * The implementation uses the sentinal node for access to the head and the tail of the list.
 * The next member is the head of the list, while the prev member is the tail of the list
 *
 */ 

/**
 * This macro simplifies obtaining a pointer to the owning member of the list member *
 **/
#define list_entry(ptr, type, member) ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

 /**
 * @brief Structure defintion for a list node.
 */
typedef struct ListNode_tag
{
   /**
    * The next node in the list, or if the sentinel node
    * the head of the list.
    */
   struct ListNode_tag* next;

   /**
    * The previous node in the list, or if the sentinel node
    * the tail of the list.
    */
   struct ListNode_tag* prev;

} ListNode;

/**
 * This function initializes a ListNode structure.
 *
 * @param sentinelNode [in] The ListNode struct to initialize as the list node.  This node
 * will be the sentinel node for the list.
 *
 * @pre none
 * @post none
 *
 * @return none
 */
void List_init( ListNode* sentinelNode );

/**
 * This function checks of the list is empty.
 *
 * @param sentinelNode [in] The sentinel node of the list.
 *
 * @pre none
 * @post none
 *
 * @return 0 is the list is NOT empty, nonzero otherwise.
 */
int32_t List_isEmpty( const ListNode* sentinelNode );

/**
 * This function returns the head node of the list.
 *
 * @param sentinelNode [in] The sentinel node of the list.
 * 
 * @pre The list must not be empty.
 * @post none
 *
 * @return The head ListNode structure of the list.
 */
ListNode* List_getHead( const ListNode* sentinelNode );

/**
 * This function returns the tail node of the list.
 *
 * @param sentinelNode [in] The sentinel node of the list.
 *
 * @pre The list must not be empty.
 * @post none
 *
 * @return The tail ListNode structure of the list.
 */
ListNode* List_getTail( const ListNode* sentinelNode );

/**
 * This function returns the head node of the list and removes the head node.  The next
 * node (if any) becomes the head of the list.
 *
 * @param sentinelNode [in] The sentinel node of the list.
 *
 * @pre The list must not be empty.
 * @post none
 *
 * @return The head ListNode structure of the list.
 */
ListNode* List_removeHead( ListNode* sentinelNode );

/**
 * This function returns the tail node of the list and removes the tail node.  The previosu
 * node before the tail (if any) becomes the tail of the list.
 *
 * @param sentinelNode [in] The sentinel node of the list.
 *
 * @pre The list must not be empty.
 * @post none
 *
 * @return The tail ListNode structure of the list.
 */
ListNode* List_removeTail( ListNode* sentinelNode );

/**
 * This function adds a node to the head of the list
 *
 * @param sentinelNode [in] The sentinel node of the list.
 * @param nodeToAdd [in] The new node to add to the head.
 *
 * @pre none
 * @post none
 *
 * @return none
 */
void List_addHead( ListNode* sentinelNode, ListNode* nodeToAdd );

/**
 * This function adds a node to the tail of the list
 *
 * @param sentinelNode [in] The sentinel node of the list.
 * @param nodeToAdd [in] The new node to add to the tail.
 *
 * @pre none
 * @post none
 *
 * @return none
 */
void List_addTail( ListNode* sentinelNode, ListNode* nodeToAdd );

/** 
 * This function returns a ListNode structure to start
 * forward iteration of the list.
 *
 * @param sentinelNode [in] The sentinel node of the list.
 *
 * @pre The list must not be empty.
 * @post none
 * 
 * @return A pointer to the first node for iteration.
 */
ListNode* List_iteratorStart( const ListNode* sentinelNode );

/**
 * This function checks if this is the last node for forward iteration
 * over the list.  
 * 
 * @param sentinelNode [in] The sentinel node of the list.
 * @param currentNode [in] The current node of the iteration.
 *
 * @pre none
 * @post none
 *
 * @return 0 if this is NOT the last node, nonzero otherwise.
 */
int32_t List_isIteratorEnd( const ListNode* sentinelNode, ListNode* currentNode );

/**
 * This function gets the next node for forward iteration of the list.
 *
 * @param currentNode [in] The current node of the iteration.
 *
 *
 * @pre none
 * @post none
 *
 * @return The next node in the iteration.  The listIsIteratorEnd function should
 * be used to check that the end of iteration has not been reached before using
 * this return value.
 */
ListNode* List_iteratorNext( const ListNode* currentNode );

#ifdef INCLUDE_LIST_TEST

/**
 * This method performs a test on the functions of the list.  If no assertion failures
 * occur, then the list test passes.
 */
void testList();

#endif
 
#ifdef __cplusplus

} // extern "C"

#endif // #ifdef __cplusplus

#endif // LIST_H_

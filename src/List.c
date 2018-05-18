//////////////////////////////////////////////////////////////////////////////
//                     Copyright 2015 All rights reserved.                  
//                              Rockwell Collins                            
//                          Proprietary Information                         
//////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <assert.h>
#include "List.h"

void List_init( ListNode* sentinelNode )
{
   assert( sentinelNode );

   sentinelNode->next = sentinelNode;
   sentinelNode->prev = sentinelNode;
}

int32_t List_isEmpty( const ListNode* sentinelNode )
{
   assert( sentinelNode );
   return ( sentinelNode->next == sentinelNode );
}

ListNode* List_getHead( const ListNode* sentinelNode )
{
  assert( sentinelNode );
  assert( !List_isEmpty( sentinelNode ) );

   return sentinelNode->next;
}

ListNode* List_getTail( const ListNode* sentinelNode )
{
   assert( sentinelNode );
   assert( !List_isEmpty( sentinelNode ) );

   return sentinelNode->prev;
}

static void List_removeNode( ListNode* node )
{
   assert( node );

   node->prev->next = node->next;
   node->next->prev = node->prev;

   node->next = NULL;
   node->prev = NULL;
}

ListNode* List_removeHead( ListNode* sentinelNode )
{
   ListNode* result;
   assert( !List_isEmpty( sentinelNode ) );

   result = sentinelNode->next;

   List_removeNode( result );

   return result;
}

ListNode* List_removeTail( ListNode* sentinelNode )
{
   ListNode* result;
   
   assert( !List_isEmpty( sentinelNode ) );
   result = sentinelNode->prev;
   
   List_removeNode( result );

   return result;
}

static void List_insert( ListNode* newNode, ListNode* previous, ListNode* next )
{
   assert( newNode );
   assert( previous );
   assert( next );

   previous->next = newNode;
   newNode->prev = previous;
   newNode->next = next;
   next->prev = newNode;
}

void List_addHead( ListNode* sentinelNode, ListNode* nodeToAdd )
{
   List_insert( nodeToAdd, sentinelNode, sentinelNode->next );
}

void List_addTail( ListNode* sentinelNode, ListNode* nodeToAdd )
{
   List_insert( nodeToAdd, sentinelNode->prev, sentinelNode );
}

ListNode* List_iteratorStart( const ListNode* sentinelNode )
{
   assert( sentinelNode );

   return sentinelNode->next;
}

int32_t List_isIteratorEnd( const ListNode* sentinelNode, ListNode* currentNode )
{
   assert( sentinelNode );
   assert( currentNode );

   return ( sentinelNode == currentNode ); 
}

ListNode* List_iteratorNext( const ListNode* currentNode )
{
   assert( currentNode );

   return currentNode->next;
}

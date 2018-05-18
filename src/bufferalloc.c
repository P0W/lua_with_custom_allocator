

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "bufferalloc.h"


typedef struct ListItem
{
   char* buffer;
   ListNode listNode;
}ListItem;

static uint32_t bufferSize = 0;
static ListNode freeList; 

void luaCreateBufferAllocator( uint32_t bufSize, uint32_t bufferCount )
{
   uint32_t index = 0 ;
   bufferSize =  bufSize ;
   List_init( &freeList );

   // Create "bufferCount" buffers of size "bufferSize".  Each buffer is allocated large enough
   // such that the bytes in front of each buffer are large enough to hold a pointer to a ListEntry struct.
   // This is used to get a reference to the ListEntry struct that manages the buffer

   for ( ; index < bufferCount; ++index )
   {
      char* buffer = (char *)malloc(sizeof( ListItem ) + bufferSize );

      ListItem* listItem = (ListItem*) buffer;
      listItem->buffer = buffer + sizeof( ListItem );

      List_addTail( &freeList, &listItem->listNode );
   }
}

void luaReleaseBufferAllocator( void )
{
   while ( !List_isEmpty( &freeList ) )
   {
      ListItem* listItem = list_entry( List_removeHead( &freeList ), ListItem, listNode );
      free((char*) listItem);
   }
}

void luaRelease( void* buffer )
{
   // Get a pointer to the list item
   ListItem* listItem = (ListItem*) ( ( (char*) buffer ) - sizeof( ListItem ) );
   List_addTail( &freeList, &listItem->listNode );
}

void* luaAllocate( uint32_t size )
{
   void* result = NULL;
   assert( size <= bufferSize );

   if ( !List_isEmpty( &freeList ) )
   {
      result = list_entry( List_removeHead( &freeList ), ListItem, listNode )->buffer;
   }

   return result;
}


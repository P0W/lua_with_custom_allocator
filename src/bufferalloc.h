#ifndef BUFFER_ALLOC_H_
#define BUFFER_ALLOC_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

   void luaCreateBufferAllocator( uint32_t bufferSize, uint32_t bufferCount ) ;
   void luaReleaseBufferAllocator( void );

   void luaRelease( void* buffer );
   void* luaAllocate( uint32_t size );

#ifdef __cplusplus
}
#endif

#endif //!BUFFER_ALLOC_H_
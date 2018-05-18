#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#ifdef __cplusplus
class CMemPool
{
private:
   struct _Unit                            //The type of the node of linkedlist.
   {
      struct _Unit *pPrev, *pNext;
   };

   void*           m_pMemBlock;            //The address of memory pool.

   //Manage all unit with two linkedlist.
   struct _Unit*   m_pAllocatedMemBlock;   //Head pointer to Allocated linkedlist.
   struct _Unit*   m_pFreeMemBlock;        //Head pointer to Free linkedlist.

   unsigned long   m_ulUnitSize;           //Memory unit size. There are much unit in memory pool.
   unsigned long   m_ulBlockSize;          //Memory pool size. Memory pool is make of memory unit.

public:
   CMemPool(unsigned long lUnitNum = 50, unsigned long lUnitSize = 1024);
   ~CMemPool();

   void*           Alloc(unsigned long ulSize, bool bUseMemPool = true);   //Allocate memory unit
   void            Free( void* p );                                        //Free memory unit
};
#endif

#ifdef __cplusplus
extern "C" 
{
#endif

   void luaCreateMem( unsigned int uiSize,  unsigned int unitSize );

   void luaReleaseMem( void* p );

   void luaDestroyMem( void );

   void *luaReallocMem(void * ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif //__MEMPOOL_H__
#ifndef DBGMEM_H
#define DBGMEM_H

#include <stdlib.h>

/* Redefines memory operator if NDEBUG not defined, so it works a bit like assert */
#ifndef NDEBUG
#define DEBUG_MEMORY
#endif

#ifdef DEBUG_MEMORY

#define calloc(n,s) dbgmem_calloc (n,s, __FILE__, __LINE__);
#define malloc(s) dbgmem_malloc (s, __FILE__, __LINE__);
#define realloc(p,s) dbgmem_realloc (p, s, __FILE__, __LINE__);
#define free(p) dbgmem_free(p, __FILE__, __LINE__);

#endif

/* Declarations */

static int no_dbgmem = 0; /* set to one to dynamically cancel memory operator redefinition */

void * dbgmem_calloc( size_t num, size_t size , const char* filename, int line);
void * dbgmem_malloc( size_t size, const char* filename, int line);
void * dbgmem_realloc( void *ptr, size_t size, const char* filename, int line);
void   dbgmem_free( void *ptr, const char* filename, int line);

void dbgmem_debug_heap_init(void);
void dbgmem_debug_heap_fini(void);
int dbgmem_dump_blocks();

#endif /* DBGMEM_H*/

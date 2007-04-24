#include "dbgmem.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef DEBUG_MEMORY /* so se dont infinitely loop on dbg_* calls */

#undef calloc
#undef malloc
#undef realloc
#undef free

#endif

/* To define a C way of logging */
#define DBGMEM_LOGMESSAGE_MAXLENGTH 256

void dbgmem_log(const char * str, const char * file,int line,...)
{
	char logstr[DBGMEM_LOGMESSAGE_MAXLENGTH];

	va_list argptr;             
	va_start( argptr, line );          

	
	sprintf(logstr, "%s:%d: ",file,line);
	strncat(logstr,str,strlen(str));
	vprintf(logstr,argptr);
	
	va_end(argptr);
}

/* Definition of the structure describing memory */

/* Double chained circular list manipulation macros */
typedef struct dbgmem_list_entry_s {
    struct dbgmem_list_entry_s * next;
    struct dbgmem_list_entry_s * prev;
} dbgmem_list_entry_t;
#define dbgmem_list_init( entry ) \
    (entry)->prev = (entry)->next = (entry)
#define dbgmem_list_isempty( list ) \
    ((list)->next == (list))
#define dbgmem_list_entry( ptr, type, member ) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define dbgmem_list_head( list ) \
    (list)->next
#define dbgmem_list_add_tail( list, entry ) \
    (entry)->next = (list); \
    (entry)->prev = (list)->prev; \
    (list)->prev->next = (entry); \
    (list)->prev = (entry) 
#define dbgmem_list_remove( entry ) \
    assert( (entry)->next != 0 ); \
    (entry)->prev->next = (entry)->next; \
    (entry)->next->prev = (entry)->prev;

static const unsigned long DBGMEM_CHECKER = 0x01020304; /* static const here to be able to get &DBGMEM_CHECKER for memory ops */
#define DBGMEM_CHECKER_SIZE 4
/* A way to be assured that checker and size matches actually ??? */

#define DBGMEM_FILENAME_MAXLENGTH 32
typedef struct dbgmem_block_s{
	unsigned long checker;
	dbgmem_list_entry_t list;
	size_t size;
	char filename[DBGMEM_FILENAME_MAXLENGTH];
	int line;
} dbgmem_block_t;

/* Managing a memory pool */
static dbgmem_list_entry_t dbgmem_blocklist;

void dbgmem_debug_heap_init(void)
{
	dbgmem_list_init(&dbgmem_blocklist);
}

static void dbgmem_dump_blocks()
{
    dbgmem_list_entry_t* entry = dbgmem_list_head( &dbgmem_blocklist );
    while( entry != &dbgmem_blocklist ) {
        dbgmem_block_t* block = dbgmem_list_entry( entry, dbgmem_block_t, list );
        dbgmem_log("Leaked %d bytes [0x%08x]\n",block->filename, block->line, block->size, block + 1);
        entry = entry->next;
    }

    if ( dbgmem_list_isempty(&dbgmem_blocklist ) ) {
        printf("No memory leaks detected.\n");
    }
}

void dbgmem_debug_heap_fini(void)
{
	dbgmem_dump_blocks();
}


void * dbgmem_store( size_t size, const char* filename, int line )
{
	dbgmem_block_t * block;
	
	block = (dbgmem_block_t*) malloc(sizeof(dbgmem_block_t) + size + DBGMEM_CHECKER_SIZE);
	
	if (block == NULL)
	{
		dbgmem_log("Error: malloc returned NULL",filename,line);
		return NULL; 
	}
	
	block -> checker = DBGMEM_CHECKER;
	block -> size = size;
	strncpy( block -> filename, filename, DBGMEM_FILENAME_MAXLENGTH );
	block -> line = line;
	
	/* Copy the checker at the end of the memory block */
	memcpy( (char*)block + sizeof(*block) + size, &DBGMEM_CHECKER, sizeof( DBGMEM_CHECKER ) );
	
	dbgmem_list_add_tail(&dbgmem_blocklist, &block -> list);
	
	return block + 1;
}

void dbgmem_remove( void* ptr, const char* filename, int line  )
{
	dbgmem_block_t * block;

	if (ptr == NULL) { return; }
	
	block = (dbgmem_block_t *) ptr - 1 ;
	
	if (block -> checker != DBGMEM_CHECKER)
	{
		dbgmem_log("Error: Corrupted Memory.",filename,line);
		assert(0);
	}
	
	/* Compare the checker at the end of the memory block */
	if ( 0 != memcmp( (char*)ptr + block->size, &DBGMEM_CHECKER, sizeof( DBGMEM_CHECKER ) ) )
	{
		dbgmem_log( "Error: Checker corrupted.", filename, line);
		assert(0);
	}
	
	dbgmem_list_remove(&block -> list);
	free(block);	
}


/* To overload C standard memory functions */
void * dbgmem_calloc( size_t num, size_t size , const char* filename, int line)
{
	void* ptr;
	int tsize;

    if ( no_dbgmem ) { return calloc( num, size ); }
    
    tsize = num * size;

    ptr = dbgmem_store( size, filename, line);

    if ( ptr == NULL ) {
        dbgmem_log("calloc of %d bytes [0x%08x] FAILED !\n", filename, line, tsize, ptr);
        return NULL;
    }

    memset( ptr, 0, size );

    dbgmem_log( "calloc of %d bytes [0x%08x] OK.\n", filename, line, tsize, ptr);

    return ptr;

}

void * dbgmem_malloc( size_t size, const char* filename, int line)
{
	void* ptr;
    if ( no_dbgmem ) { return malloc( size ); }
    
    ptr = dbgmem_store( size, filename, line);
    
    if ( ptr == NULL ) {
    	dbgmem_log("malloc of %d bytes [0x%08x] FAILED !\n", filename, line, size, ptr);
	return NULL;
    }
    
    dbgmem_log( "malloc of %d bytes [0x%08x] OK.\n", filename, line, size, ptr);
    
    return ptr;
}

void * dbgmem_realloc( void *ptr, size_t size, const char* filename, int line)
{
	void* newptr;

    if ( no_dbgmem ) { return realloc( ptr, size ); }
    
    if ( ptr == NULL ) {
        return dbgmem_malloc( size, filename, line);
    }

    if ( size == 0 ) {
        dbgmem_remove( ptr, filename, line);
        dbgmem_log("memory freed on realloc of %d bytes [0x%08x]",filename, line, size, ptr);
        return NULL;
    }

    newptr = dbgmem_store(size, filename, line);
    memcpy(newptr,ptr,size); /* copy memory content */
    dbgmem_remove(ptr, filename, line);
    
    dbgmem_log( "realloc of %d bytes [0x%08x] OK.\n", filename, line, size, ptr);

    return newptr;
    
}

void   dbgmem_free( void *ptr, const char* filename, int line)
{
    if ( no_dbgmem ) { free( ptr ); return; }

    if ( ptr == 0 ) {
        return;
    }

    dbgmem_remove( ptr, filename, line);
    
    dbgmem_log( "free [0x%08x] OK.\n", filename, line, ptr);
}




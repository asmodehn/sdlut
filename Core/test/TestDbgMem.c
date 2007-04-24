#include "dbgmem.h"

#include <stdio.h>

int main()
{
	char * str;

dbgmem_debug_heap_init();
atexit ( dbgmem_debug_heap_fini );

    str = (char*)malloc ( 5 * sizeof (char) );
    
	str[0] = 't';
	str[1] = 'e';
	str[2] = 's';
	str[3] = 't';
	str[4] = '\0';
	
	printf("%s\n",str);
    

  
    return 0;
}



#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <malloc.h>

static	unsigned	nonfatal;

int
main(
	int		argc,
	char * *	argv
)
{
	return( nonfatal ? 1 : 0 );
}

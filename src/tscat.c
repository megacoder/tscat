#include "config.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>

static	unsigned	nonfatal;

static	char const *	fmt = "%Y-%m-%d %H:%M:%S";

static	void
process(
	FILE *		fyle
)
{
	char		buf[ BUFSIZ + 1 ];
	char		timestamp[ BUFSIZ + 1 ];

	while( fgets( buf, BUFSIZ, fyle ) != NULL )	{
		/* Have a complete line					 */
		time_t const		now = time( NULL );
		struct tm * const	tm = localtime( &now );

		if( strftime( timestamp, BUFSIZ, fmt, tm ) == 0 )	{
			perror( "strftime" );
			exit( 1 );
		}
		if( printf( "%s %s", timestamp, buf ) < 0 )	{
			perror( "printf" );
			exit( 1 );
		}
	}
}

int
main(
	int		argc,
	char * *	argv
)
{
	process( stdin );
	return( nonfatal ? 1 : 0 );
}

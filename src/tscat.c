#include "config.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <errno.h>

static	unsigned	nonfatal;
static	char *		ofile;
static	char *		me = "tscat";
static	unsigned	n_sw;

static	char const *	fmt = "%Y-%m-%d %H:%M:%S";

static	void
say(
	int		e,
	char const *	fmt,
	...
)
{
	va_list		ap;

	fprintf( stderr, "%s: ", me );
	va_start( ap, fmt );
	vfprintf( stderr, fmt, ap );
	va_end( ap );
	if( e )	{
		fprintf(
			stderr,
			"; errno=%d (%s)",
			e,
			strerror( e )
		);
	}
	fprintf( stderr, ".\n" );
}

static	void
process(
	FILE *		fyle
)
{
	char		buf[ BUFSIZ + 1 ];
	char		timestamp[ BUFSIZ + 1 ];
	unsigned long	lineno;

	lineno = 0;
	while( fgets( buf, BUFSIZ, fyle ) != NULL )	{
		/* Have a complete line					 */
		time_t const		now = time( NULL );
		struct tm * const	tm = localtime( &now );

		if( strftime( timestamp, BUFSIZ, fmt, tm ) == 0 )	{
			perror( "strftime" );
			exit( 1 );
		}
		buf[ BUFSIZ ] = '\0';
		timestamp[ BUFSIZ ] = '\0';
		if( n_sw )	{
			printf( "%7lu\t", ++lineno );
		}
		if( printf( "%s %s", timestamp, buf ) < 0 )	{
			perror( "printf" );
			exit( 1 );
		}
	}
}

static	int
do_getopt(
	int		argc,
	char * *	argv
)
{
	int		c;

	while( (c = getopt( argc, argv, "f:no:" )) != EOF )	{
		switch( c )	{
		default:
			fprintf( stderr, "Huh?\n" );
			break;
		case 'f':
			fmt = optarg;
			break;
		case 'n':
			n_sw = 1;
			break;
		case 'o':
			ofile = optarg;
			break;
		}
	}
	return( (c == EOF) ? 0 : -1 );
}

int
main(
	int		argc,
	char * *	argv
)
{
	do	{
		if( do_getopt( argc, argv ) )	{
			++nonfatal;
			break;
		}
		if( ofile )	{
			if( freopen( ofile, "wt", stdout ) != stdout )	{
				say(
					errno,
					"cannot open '%s' for writing",
					ofile
				);
				++nonfatal;
				break;
			}
		}
		if( optind < argc )	{
			while( optind < argc )	{
				char * const	fn = argv[ optind++ ];
				FILE * const	fyle = fopen( fn, "rt" );

				if( ! fyle )	{
					say(
						errno,
					"cannot open '%s' for reading",
						fn
					);
					++nonfatal;
					continue;
				}
				process( fyle );
				if( fclose( fyle ) < 0 )	{
					say(
						errno,
						"cannot close '%s'",
						fn
					);
					++nonfatal;
				}
			}
		} else	{
			process( stdin );
		}
	} while( 0 );
	return( nonfatal ? 1 : 0 );
}

#include <stdio.h>

#include "File.h"
#include "Macros.h"
#include "Pattern.h"

void usage();

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		usage();

		return	1;
	}

	Pattern::Ptr	pPattern	= Pattern::create(argv[1]);

	if (nullptr == pPattern)
	{
		return	1;
	}

	if (false == pPattern->save(argv[2]))
	{
		return	1;
	}

	return	0;
}

void usage()
{
	printf("Usage: PNGToBackground PngFile FilePrefix\nConverts 32 bit png to background sprite table.\n");
}

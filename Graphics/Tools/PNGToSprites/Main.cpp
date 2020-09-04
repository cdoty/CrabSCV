#include <stdio.h>

#include "Sprites.h"

void usage();

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		usage();

		return	1;
	}

	Sprites::Ptr	pSprites	= Sprites::create(argv[1]);

	if (nullptr == pSprites)
	{
		return	1;
	}

	if (false == pSprites->save(argv[2]))
	{
		return	1;
	}

	return	0;
}

void usage()
{
	printf("Usage: PNGToSpriteSCV ImageFile TileData\n");
}

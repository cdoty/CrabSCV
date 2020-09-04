#include "Colors.h"
#include "Defines.h"
#include "File.h"
#include "Sprites.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
	close();
}

Sprites::Ptr Sprites::create(const std::string& _strFilename)
{
	INSTANCE(pSprites, Sprites())

	if (false == pSprites->initialize(_strFilename))
	{
		pSprites.reset();
	}

	return	pSprites;
}

bool Sprites::initialize(const std::string& _strFilename)
{
	if (false == loadSprites(_strFilename))
	{
		printf("Unable to load sprites.\n");

		return	false;
	}

	return	true;
}

void Sprites::close()
{
}

bool Sprites::save(const std::string& _strFilename)
{
	int	t_c	= (int)m_sprites.size();

	if (0 == t_c)
	{
		printf("No sprites defined.\n");

		return	false;
	}

	File::Ptr	pFile	= File::create();

	if (false == pFile->create(_strFilename, true))
	{
		printf("Unable to create file %s/\n", _strFilename.c_str());

		return	false;
	}

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		m_sprites[iLoop]->save(pFile);
	}

	pFile->close();

	return	true;
}

bool Sprites::loadSprites(const std::string& _strFilename)
{
	int	iWidth	= 0;
	int	iHeight	= 0;
	int	iDepth	= 0;

	uint8_t*	pPixels	= stbi_load(_strFilename.c_str(), &iWidth, &iHeight, &iDepth, 0);

	if (NULL == pPixels)
	{
		printf("Unable to find or load sprite image.\n");

		return	false;
	}

	if ((iWidth % gsc_iTileWidth) != 0 || (iHeight % gsc_iTileHeight) != 0)
	{
		printf("Image must be a multiple of %d width and %d height.\n", gsc_iTileWidth, gsc_iTileHeight);

		return	false;
	}

	if (false == extractTiles(pPixels, iWidth, iHeight))
	{
		return	false;
	}

	stbi_image_free(pPixels);

	return	true;
}

bool Sprites::extractTiles(const uint8_t* _pTiles, int _iWidth, int _iHeight)
{
	int	iTileWidth	= _iWidth / gsc_iTileWidth;
	int	iTileHeight	= _iHeight / gsc_iTileHeight;

	DEFINESHAREDBUFFER(pTileBuffer, uint8_t, gsc_iTileWidth * gsc_iTileHeight);

	for (int iYLoop = 0; iYLoop < iTileHeight; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < iTileWidth; ++iXLoop)
		{
			if (false == extractTile(_pTiles, _iWidth, _iHeight, pTileBuffer.get(), iXLoop * gsc_iTileWidth, iYLoop * gsc_iTileHeight))
			{
				printf("Unable to extract tile\n");

				return	false;
			}

			std::vector<uint8_t>	colors;

			getColors(pTileBuffer.get(), colors);

			int	t_c	= (int)colors.size();

			uint8_t	color;

			for (int iLoop = 0; iLoop < t_c; ++iLoop)
			{
				color	= colors[iLoop];

				if (color >= gsc_iColors)
				{
					color	= 0;
				}
			}

			Sprite::Ptr	pSprite	= Sprite::create(pTileBuffer.get(), color);

			m_sprites.push_back(pSprite);
		}
	}

	return	true;
}

bool Sprites::extractTile(const uint8_t* _pTiles, int _iWidth, int _iHeight, uint8_t* _pTile, int _iX, int _iY)
{
	const uint8_t*	pSrc	= _pTiles + (_iY * _iWidth + _iX) * 4;
	uint8_t*		pDest	= _pTile;

	for (int iYLoop = 0; iYLoop < gsc_iTileHeight; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < gsc_iTileWidth; ++iXLoop)
		{
			uint8_t	red		= *(pSrc++);
			uint8_t	green	= *(pSrc++);
			uint8_t	blue	= *(pSrc++);
			uint8_t	alpha	= *(pSrc++);

			int	colorIndex	= getPalette(red, green, blue, alpha);

			*pDest	= colorIndex;

			pDest++;
		}

		pSrc	+= (_iWidth - gsc_iTileWidth) * 4;
	}

	return	true;
}

void Sprites::getColors(const uint8_t* _pTile, std::vector<uint8_t>& _colors)
{
	for (int iLoop = 0; iLoop < gsc_iTileWidth * gsc_iTileHeight; ++iLoop)
	{
		int		t_c		= (int)_colors.size();
		uint8_t	color	= _pTile[iLoop];
		bool	bFound	= false;

		for (int iColor = 0; iColor < t_c; ++iColor)
		{
			if (color >= gsc_iColors || _colors[iColor] == color)
			{
				bFound	= true;

				break;
			}
		}

		if (true == bFound || color >= gsc_iColors)
		{
			continue;
		}

		_colors.push_back(color);
	}
}
				   
int Sprites::getPalette(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha)
{
	if (_alpha > 0)
	{
		for (int iLoop = 0; iLoop < gsc_iColors; ++iLoop)
		{
			const Color& color	= gsc_colors[iLoop];

			if (_red == color.red && _green == color.green && _blue == color.blue)
			{
				return	iLoop;
			}
		}
	}

	return	gsc_iColors;
}
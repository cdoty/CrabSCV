#include <algorithm>

#include "File.h"
#include "Palette.h"
#include "Pattern.h"
#include "stb_image.h"

static const int	gsc_iSpriteSize			= 16;		// Sprite size
static const int	gsc_iSpriteLimit		= 128;		// Sprite limit
static const int	gsc_iTileLimit			= 128;		// Tile limit
static const char*	gsc_szSpriteExtension	= ".spr";	// Sprite extension;
static const char*	gsc_szScreenExtension	= ".scn";	// Screen extension;
static const int	gsc_iDisplayStartY		= 0x1C;		// Display start y

Pattern::Pattern()	:
	m_pBuffer(NULL),
	m_iWidth(0),
	m_iHeight(0)
{
}

Pattern::~Pattern()
{
	close();
}

Pattern::Ptr Pattern::create(const std::string& _strFilename)
{
	INSTANCE(pPattern, Pattern())

	if (false == pPattern->initialize(_strFilename))
	{
		pPattern.reset();
	}

	return	pPattern;
}

bool Pattern::initialize(const std::string& _strFilename)
{
	int	iBpp;

	m_pBuffer	= stbi_load(_strFilename.c_str(), &m_iWidth, &m_iHeight, &iBpp, 4);

	if (NULL == m_pBuffer)
	{
		printf("Unable to load image %s.\n", _strFilename.c_str());
	
		return	false;
	}

	if (false == processSprites())
	{
		return	false;
	}

	return	true;
}

void Pattern::close()
{
	if (m_pBuffer != NULL)
	{
		stbi_image_free(m_pBuffer);

		m_pBuffer	= NULL;
	}
}

bool Pattern::save(const std::string& _strPrefix)
{
	int	iTileCount	= (int)m_patterns.size();

	if (iTileCount > gsc_iTileLimit)
	{
		printf("Too many tiles. Sprite patterns are limited to %d.\n", gsc_iTileLimit);

		return	false;
	}

	File::Ptr	pFile	= File::create();

	if (nullptr == pFile)
	{
		printf("Unable to create file interface.\n");

		return	false;
	}

	std::string	strFilename;

	strFilename	= _strPrefix;
	strFilename	+= gsc_szSpriteExtension;

	if (false == pFile->create(strFilename, true))
	{
		printf("Unable to create sprite file %s.\n", strFilename.c_str());

		return	false;
	}

	for (int iLoop = 0; iLoop < iTileCount; ++iLoop)
	{
		// Write pattern
		if (false == pFile->writeBuffer(m_patterns[iLoop].get(), gsc_iSpriteSize / 8 * gsc_iSpriteSize))
		{
			printf("Unable to write sprite data.\n");

			return	false;
		}
	}
			
	pFile->close();

	strFilename	= _strPrefix;
	strFilename	+= gsc_szScreenExtension;

	if (false == pFile->create(strFilename, true))
	{
		printf("Unable to create table file %s.\n", strFilename.c_str());

		return	false;
	}

	int	iSpriteCount	= (int)m_tilemap.size();

	if (iSpriteCount > gsc_iSpriteLimit)
	{
		printf("Too many sprites. Sprites are limited to %d.\n", gsc_iSpriteLimit);

		return	false;
	}

	for (int iLoop = 0; iLoop < iSpriteCount; ++iLoop)
	{
		// Write sprites
		if (false == pFile->writeBuffer((const uint8_t*)&m_tilemap[iLoop], sizeof(SpriteInfo)))
		{
			printf("Unable to write table data.\n");

			return	false;
		}
	}
			
	pFile->close();

	return	true;
}

bool Pattern::processSprites()
{
	if ((m_iWidth & (gsc_iSpriteSize - 1)) != 0 || (m_iHeight & (gsc_iSpriteSize - 1)) != 0)
	{
		printf("File width and selected height must be a multiple of %d.\n", gsc_iSpriteSize);

		return	false;
	}
	
	DEFINESHAREDBUFFER(pTile, uint8_t, gsc_iSpriteSize * gsc_iSpriteSize);

	for (int iYLoop = 0; iYLoop < m_iHeight; iYLoop += gsc_iSpriteSize)
	{
		for (int iXLoop = 0; iXLoop < m_iWidth; iXLoop += gsc_iSpriteSize)
		{
			if (true == grabTile(pTile.get(), iXLoop, iYLoop))
			{
				SpriteInfo	spriteInfo;

				spriteInfo.posX	= (iXLoop & 0xFE);
				spriteInfo.posY	= ((iYLoop + gsc_iDisplayStartY) & 0xFE);

				spriteInfo.tile	= encodeTile(pTile.get(), spriteInfo.palette) & 0x7F;

				m_tilemap.push_back(spriteInfo);
			}
		}
	}

	return	true;
}

bool Pattern::grabTile(uint8_t* _pBuffer, int _iX, int _iY)
{
	uint8_t*	pSource	= m_pBuffer	+ ((_iY * m_iWidth + _iX) * 4);
	uint8_t*	pDest	= _pBuffer;
	bool		bEmpty	= true;

	for (int iYLoop = 0; iYLoop < gsc_iSpriteSize; ++iYLoop)
	{
		for (int iXLoop = 0; iXLoop < gsc_iSpriteSize; ++iXLoop)
		{
			uint8_t	red		= *(pSource++);
			uint8_t	green	= *(pSource++);
			uint8_t	blue	= *(pSource++);
			uint8_t	alpha	= *(pSource++);

			int	iPalette	= findPalette(red, green, blue, alpha);

			if (iPalette < gsc_iColors)
			{
				bEmpty	= false;
			}

			*pDest	= iPalette;

			pDest++;
		}

		pSource	+= (m_iWidth - gsc_iSpriteSize) * 4;
	}

	return	false == bEmpty;
}

// Sprites are stored in a single bitplane encoded in 4x2 pixel chunks.
// R0P0 R0P1 R0P2 R0P3
// R1P0 R1P1 R1P2 R1P3
int Pattern::encodeTile(uint8_t* _pSrc, uint8_t& _palette)
{
	DEFINESHAREDBUFFER(pPatternBuffer, uint8_t, gsc_iSpriteSize / 8 * gsc_iSpriteSize);

	uint8_t*	pDest	= pPatternBuffer.get();
	uint8_t*	pSrc	= _pSrc;

	uint8_t	paletteIndex	= 0;

	for (int iRow = 0; iRow < gsc_iSpriteSize; iRow += 2)
	{
		for (int iPixels = 0; iPixels < 4; ++iPixels)
		{
			*pDest	= 0;

			for (int iColumn = 0; iColumn < 4; ++iColumn)
			{
				uint8_t	topPixel	= *pSrc;
				uint8_t	bottomPixel	= *(pSrc + gsc_iSpriteSize);

				if (topPixel < gsc_iColors)
				{
					paletteIndex	= topPixel;
				}

				else if (bottomPixel < gsc_iColors)
				{
					paletteIndex	= bottomPixel;
				}

				*pDest	|= (topPixel < gsc_iColors ? 1 << (4 + 3 - iColumn) : 0);
				*pDest	|= (bottomPixel < gsc_iColors ? 1 << (3 - iColumn) : 0);

				pSrc++;
			}

			pDest++;
		}

		// Skip 2nd line
		pSrc	+= gsc_iSpriteSize;
	}

	int	iSprite	= addSprite(pPatternBuffer);
	 
	_palette	= paletteIndex & 0x0F;

	return	iSprite;
}

int Pattern::addSprite(std::shared_ptr<uint8_t>& _pPattern)
{
	int	t_c	= (int)m_patterns.size();

	for (int iLoop = 0; iLoop < t_c; ++iLoop)
	{
		if (true == bufferSame(_pPattern.get(), m_patterns[iLoop].get(), gsc_iSpriteSize / 8 * gsc_iSpriteSize))
		{
			return	iLoop;
		}
	}

	int	iIndex	= (int)m_patterns.size();
	
	m_patterns.push_back(_pPattern);

	return	iIndex;
}

int Pattern::findPalette(int _iRed, int _iGreen, int _iBlue, int _iAlpha)
{
	if (0 == _iAlpha)
	{
		return	gsc_iColors;
	}

	for (int iLoop = 0; iLoop < gsc_iColors; ++iLoop)
	{
		if (_iRed == gsc_palette[iLoop].red && _iGreen == gsc_palette[iLoop].green && _iBlue == gsc_palette[iLoop].blue)
		{
			return	iLoop;
		}
	}

	return	gsc_iColors;
}

bool Pattern::bufferSame(uint8_t* _pBuffer1, uint8_t* _pBuffer2, int _iBufferSize)
{
	uint8_t*	pBuffer1Ptr	= _pBuffer1;
	uint8_t*	pBuffer2Ptr	= _pBuffer2;

	for (int iLoop = 0; iLoop < _iBufferSize; ++iLoop)
	{
		if (*pBuffer1Ptr != *pBuffer2Ptr)
		{
			return	false;
		}

		pBuffer1Ptr++;
		pBuffer2Ptr++;
	}

	return	true;
}
#include "Defines.h"
#include "Sprite.h"

Sprite::Sprite(int _iPixelColor)	:
	m_iPixelColor(_iPixelColor)
{
}

Sprite::~Sprite()
{
	close();
}

Sprite::Ptr Sprite::create(const uint8_t* _pBuffer, int _iPixelColor)
{
	INSTANCE(pSprite, Sprite(_iPixelColor))

	if (false == pSprite->initialize(_pBuffer))
	{
		pSprite.reset();
	}

	return	pSprite;
}

bool Sprite::initialize(const uint8_t* _pBuffer)
{
	convert(_pBuffer);

	return	true;
}

void Sprite::close()
{
}

bool Sprite::save(File::Ptr _pFile)
{
	if (nullptr == m_pTileBuffer)
	{
		printf("Buffer is invalid.\n");

		return	false;
	}

	_pFile->writeBuffer(m_pTileBuffer.get(), gsc_iTileWidth / 8 * gsc_iTileHeight);

	return	true;
}

// Sprites are stored in a single bitplane encoded in 4x2 pixel chunks.
// R0P0 R0P1 R0P2 R0P3
// R1P0 R1P1 R1P2 R1P3
void Sprite::convert(const uint8_t* _pBuffer)
{
	SHAREDBUFFER(m_pTileBuffer, uint8_t, gsc_iTileWidth / 8 * gsc_iTileHeight);
	
	const uint8_t*	pSrc	= _pBuffer;
	uint8_t*		pDest	= m_pTileBuffer.get();

	for (int iRow = 0; iRow < 16; iRow += 2)
	{
		for (int iBytes = 0; iBytes < 4; ++iBytes)
		{
			*pDest	= 0;

			for (int iColumn = 0; iColumn < 4; ++iColumn)
			{
				uint8_t	topPixel	= *pSrc;
				uint8_t	bottomPixel	= *(pSrc + gsc_iTileWidth);

				*pDest	|= (m_iPixelColor == topPixel ? 1 << (4 + 3 - iColumn) : 0);
				*pDest	|= (m_iPixelColor == bottomPixel ? 1 << (3 - iColumn) : 0);

				pSrc++;
			}

			pDest++;
		}

		pSrc	+= gsc_iTileWidth;
	}
}

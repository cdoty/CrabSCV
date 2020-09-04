#pragma once

#include "Macros.h"

class Pattern
{
	public:
		PTR(Pattern)

		// Constructor
		Pattern();

		// Destructor
		~Pattern();

		// Create
		static Ptr create(const std::string& _strFilename);

		// Initialize
		bool initialize(const std::string& _strFilename);

		// Close
		void close();

		// Save
		bool save(const std::string& _strPrefix);

	private:
		struct SpriteInfo
		{
			uint8_t	posY;		// Y position
			uint8_t	palette;	// Palette
			uint8_t	posX;		// X position
			uint8_t	tile;		// Tile index
		};

		std::vector<std::shared_ptr<uint8_t>>	m_patterns;	// Patterns
		std::vector<SpriteInfo>					m_tilemap;	// Tile map

		uint8_t*	m_pBuffer;		// Buffer
		int			m_iWidth;		// Width
		int			m_iHeight;		// Height

		// Process sprites
		bool processSprites();
		
		// Grab tile
		bool grabTile(uint8_t* _pBuffer, int _iX, int _iY);

		// Encode tile
		int encodeTile(uint8_t* _pSrc, uint8_t& _palette);

		// Add sprite
		int addSprite(std::shared_ptr<uint8_t>& _pPattern);

		// Find palette
		int findPalette(int _iRed, int _iGreen, int _iBlue, int _iAlpha);

		// Buffers same?
		bool bufferSame(uint8_t* _pBuffer1, uint8_t* _pBuffer2, int _iBufferSize);
};

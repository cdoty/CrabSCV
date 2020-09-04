#pragma once

#include <string>

#include "Macros.h"
#include "Sprite.h"

class Sprites
{
	public:
		PTR(Sprites)

		// Destructor
		~Sprites();

		// Create
		static Ptr create(const std::string& _strFilename);

		// Initialize
		bool initialize(const std::string& _strFilename);

		// Close
		void close();

		// Save
		bool save(const std::string& _strFilename);

	private:
		std::vector<Sprite::Ptr>	m_sprites;	// Sprites

		// Constructor
		Sprites();

		// Load sprites
		bool loadSprites(const std::string& _strFilename);

		// Extract tiles
		bool extractTiles(const uint8_t* _pTiles, int _iWidth, int _iHeight);

		// Extract tile
		bool extractTile(const uint8_t* _pTiles, int _iWidth, int _iHeight, uint8_t* _pTile, int _iX, int _iY);

		// Get colors
		void getColors(const uint8_t* _pTiles, std::vector<uint8_t>& _colors);

		// Get palette
		int getPalette(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha);
};

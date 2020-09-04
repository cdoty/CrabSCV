#pragma once

#include "Macros.h"
#include "File.h"

class Sprite
{
	public:
		PTR(Sprite)

		// Destructor
		~Sprite();

		// Create
		static Ptr create(const uint8_t* _pBuffer, int _iPixelColor);

		// Initialize
		bool initialize(const uint8_t* _pBuffer);

		// Close
		void close();

		// Save
		bool save(File::Ptr _pFile);

	private:
		SHAREDPTR(uint8_t, m_pTileBuffer);	// Tile buffer

		int	m_iPixelColor;	// Pixel color

		// Constructor
		Sprite(int _iPixelColor);

		// Convert
		void convert(const uint8_t* _pBuffer);
};
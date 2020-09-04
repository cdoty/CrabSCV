BackgroundScreen:
	binclude ../Graphics/Background.scn
BackgroundScreneEnd:

BackgroundScreenSize	equ	BackgroundScreneEnd - BackgroundScreen

BackgroundSprites:
	binclude ../Graphics/Background.spr
BackgroundSpritesEnd:

BackgroundSpritesSize	=	BackgroundSpritesEnd - BackgroundSprites

Sprites:
	binclude ../Graphics/Sprites.spr
SpritesEnd:

SpritesSize	equ	SpritesEnd - Sprites

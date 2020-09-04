	include	"GameDefines.inc"
	
startGame:
	; Setup background
	call 	setupBackground

	; Setup player sprite
	call	setupPlayer

	ei

gameplayLoop:
	skit	f2				; Wait for VBlank
	jr		gameplayLoop

	call	updatePlayer

	jr		gameplayLoop
	
	ret

setupBackground:
	lxi		h, BackgroundScreen			; Block transfer background sprite settings to VRAM
	lxi		d, BGSpriteTable
	lxi		b, BackgroundScreenSize

setupScreenLoop:
	block
	
	dcr		b
	jr		setupScreenLoop

	lxi		h, BackgroundSprites		; Block transfer background sprite graphics to VRAM
	lxi		d, BGSpriteVRAM
	lxi		b, BackgroundSpritesSize

setupBackgroundSpritesLoop:
	block
	
	dcr		b
	jr		setupBackgroundSpritesLoop

	lxi		h, Sprites					; Block transfer sprite graphics to VRAM
	lxi		d, SpriteVRAM
	lxi		b, SpritesSize

setupSpritesLoop:
	block
	
	dcr		b
	jr		setupSpritesLoop

	ret

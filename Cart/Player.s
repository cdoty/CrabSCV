updatePlayer:
	handleJoystick	moveLeft, moveRight, handleFire, handleIdle

	ret

moveLeft:
	mov		a, PlayerX

	lti		a, LeftEdge + MoveSpeed
	jr		doMoveLeft

	ret

doMoveLeft:
	sbi		a, MoveSpeed

	call	movePlayer

	ret
	
moveRight:
	mov		a, PlayerX

	gti		a, RightEdge - MoveSpeed
	jr		doMoveRight

	ret
	
doMoveRight:
	adi		a, MoveSpeed

	call	movePlayer

	ret

movePlayer:
	mov		PlayerX, a
	mov		b, a

	selectSpriteI	MCSpriteTable, PlayerSpriteIndex
	mov		a, b	
	setSpriteX
	
	selectSpriteI	MCSpriteTable, PlayerSpriteIndex + 1
	mov		a, b	
	setSpriteX
	
	mov		a, PlayerFrame
	adi		a, 1
	
	eqi		a, PlayerFrameCount
	jr		.updateFrame

	mvi		a, 0

.updateFrame:
	call	setPlayerFrame

	ret

handleFire:
	selectSpriteI	MCSpriteTable, PlayerSpriteIndex
	
	ret

handleIdle:
	mov		a, PlayerFrame
	
	nei		a, 0
	jr		.skipReset

	mvi		a, 0
	call	setPlayerFrame

.skipReset:
	ret

setupPlayer:
	mvi		a, DisplayStartX + (DisplayXSize / 2) - 8
	mov		PlayerX, a

	mvi		a, 0
	mov		PlayerFrame, a

	selectSpriteI MCSpriteTable, PlayerSpriteIndex

	; Create a sprite, with the next sprite overlayed on top, for the crab body
	setSprite DisplayStartX + (DisplayXSize / 2) - 8, PlayerStartY | 1, PlayerSprite, PlayerPalette
	
	; Create a normal sprite for the arms
	setSprite DisplayStartX + (DisplayXSize / 2) - 8, PlayerStartY - ArmOffsetY, PlayerSprite + 6, ClawPalette
	
	ret

setPlayerFrame:
	mov		PlayerFrame, a

	mov		b, a 

	selectSpriteI	MCSpriteTable, PlayerSpriteIndex	

	lxi		d, PlayerFrames	; Block transfer background sprite graphics to VRAM
	
	mov		a, b
	add		e, a

	ldax	d

	call	setSpriteTile

	ret

selectSprite macro spriteTable
	lxi	h, spriteTable
	sll	a				; Multiply sprite number by 4
	sll	a
	
	add	l, a			; Add it to the sprite table address
	endm

selectSpriteI macro spriteTable, spriteNum
	lxi	h, spriteTable
	mvi	a, spriteNum
	sll	a				; Multiply sprite number by 4
	sll	a
	
	add	l, a			; Add it to the sprite table address	
	endm

setSprite macro x, y, tile, color	; X, Y, and tile must be memory locations, color is a value
	mvi		a, y
	stax	h+		; Store Y

	mvi		a, color
	stax	h+		; Store color index

	mvi		a, x
	ani		a, 0FEh
	stax	h+		; Store X

	mvi		a, tile
	stax	h+		; Store tile number
	endm

setSpriteX macro
	push	h
	
	inx		h
	inx		h

	ani		a, 0FEh
	stax	h		; Store X

	pop		h
	endm

setSpriteXI macro x
	push	h
	
	inx		h
	inx		h

	mvi		a, x
	ani		a, 0FEh
	stax	h		; Store X

	pop		h
	endm

getSpriteX macro
	push	h
	
	inx		h
	inx		h

	ldax	h		; Load X

	pop		h
	endm

setSpriteY macro
	ani		0FEh	; And out 2 color mode flag
	stax	h		; Store Y
	endm

setSpriteYI macro y
	mvi		a, y
	ani		0FEh	; And out 2 color mode flag
	stax	h		; Store Y
	endm

getSpriteY macro
	ldax	h		; Load X
	ani		0FEh	; And out 2 color mode flag
	endm

setSpriteTile macro tile
	push	hl
	
	inx		h
	inx		h
	inx		h

	stax	h		; Store Tile

	pop		hl
	endm

setSpriteTileI macro tile
	push	hl
	
	inx		h
	inx		h
	inx		h

	mvi		a, tile
	stax	h		; Store Tile

	pop		hl
	endm

setSpriteColor macro
	push	h
	
	inx		h

	mvi		a, color
	stax	h		; Store Color

	pop		h
	endm

setSpriteColorI macro color
	push	hl
	
	inx		h

	mvi		a, color
	stax	h		; Store Color

	pop		hl
	endm

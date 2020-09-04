start:
	call	ClearTextArea	; Calls routine located at address 8Ch (0A1Bh)
	call	ClearSprites	; Calls routine located at address 8Eh (0A28h)
	call	ClearTiles		; Calls routine located at address 90h (0A4Ah)
	
	lxi		h, VDCData		; Set VDC settings
	lxi		d, VDCTable
	mvi		c, 3
	
	block

gameLoop:
	call	startGame
	
	jr		gameLoop

VDCData:
	db	0F4h
	db	00h
	db	00h
	db	0F1h

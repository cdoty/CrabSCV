; VDC memory mapped defines
BGSpriteVRAM	equ	2000h
SpriteVRAM		equ	2800h
TextVRAM		equ	3000h
BGSpriteTable	equ	3200h
SpriteTable		equ	3300h	; Sprite table for moving sprites
MCSpriteTable	equ	3380h	; Sprite table for multi-color moving sprites
VDCTable		equ	3400h

; BIOS routines
ClearTextArea	equ	0A1Bh
ClearSprites	equ	0A29h
ClearTiles		equ	0A4Ah

DisplayYSize		equ	222
DisplayStartX		equ	1Ch
DisplayXSize		equ	220-1Ch
DisplayEndX			equ	1Ch + DisplayXSize
DisplayStartY		equ	(DisplayYSize - 192)
PlayerStartY		equ	(178 + DisplayStartY)		; Player Y
PlayerSprite		equ 0 + 64						; Player sprite graphic
PlayerSpriteIndex	equ	0							; Player sprite index
ArmOffsetY			equ	4							; Arm offset
PlayerPalette		equ	2							; Player palette
ClawPalette			equ	8							; Claw palette
PlayerWidth			equ	11							; Player width
LeftEdge			equ	DisplayStartX				; Left Edge
RightEdge			equ	DisplayEndX - PlayerWidth	; Right Edge
MoveSpeed			equ	1							; Move speed

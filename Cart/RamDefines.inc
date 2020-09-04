	org	0FF80h

PlayerInput1:	; Player 1 input flags
	ds	1
	
PlayerInput2:	; Player 2 input flags
	ds	1
	
JoyRead:		; Joy read value
	ds	2

PlayerX:		; Player x position
	ds	1

PlayerFrame:	; Player frame
	ds	1

TempValues		; Temp value storage
	ds	4
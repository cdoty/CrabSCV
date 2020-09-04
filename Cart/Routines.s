;PA: FEh (~1)
;PB:
;11111110	P1 Left
;11111101	P1 Up
;11111011	P1 Fire 1
;11110111	P2 Left
;11101111	P2 Up
;11011111	P2 Fire 1

;PA: FDh (~2)
;PB:
;11111110	P1 Down
;11111101	P1 Right
;11111011	P1 Fire 2
;11110111	P2 Down
;11101111	P2 Right
;11011111	P2 Fire 2
;
; Produces %0012UDLR (1: Fire 1  2: Fire 2)
ReadJoysticks:
	mvi		a, 0FEh
	mov		pa, a
	mov		a, pb
	
	staw	JoyRead
	
	mvi		a, 0FDh
	mov		pa, a
	mov		a, pb
	
	staw	JoyRead + 1

	xra		a, a
	
	bit		0, JoyRead
	ori		a, 2
	
	bit		1, JoyRead
	ori		a, 8
	
	bit		2, JoyRead
	ori		a, 20h
	
	bit		0, JoyRead + 1
	ori		a, 4
	
	bit		1, JoyRead + 1
	ori		a, 1
	
	bit		2, JoyRead + 1
	ori		a, 10h
	
	staw	PlayerInput1

	xra		a, a
	
	bit		3, JoyRead
	ori		a, 2
	
	bit		4, JoyRead
	ori		a, 8
	
	bit		5, JoyRead
	ori		a, 20h
	
	bit		3, JoyRead
	ori		a, 4
	
	bit		4, JoyRead
	ori		a, 1
	
	bit		5, JoyRead
	ori		a, 10h
	
	staw	PlayerInput2
	
	ret

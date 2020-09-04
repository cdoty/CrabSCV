; handleJoystick(leftRoutine, rightRoutine, fireRoutine, idleRoutine). Routines must ret.
handleJoystick macro leftRoutine, rightRoutine, fireRoutine, idleRoutine
	call	ReadJoysticks
	
	bit		0, PlayerInput1
	jr		checkLeft
	
	call	rightRoutine
	
	jr		checkFire

checkLeft:
	bit		1, PlayerInput1
	jr		playerIdle
	
	call	leftRoutine

	jr		checkFire

playerIdle:
	call	handleIdle

checkFire:
	bit		5, PlayerInput1
	jr		endInput

	call	fireRoutine
	
endInput:
	endm

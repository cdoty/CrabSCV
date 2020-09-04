PlayerFrameDelay	equ 4

PlayerFrames:
	db	PlayerFrameDelay dup PlayerSprite
	db	PlayerFrameDelay dup PlayerSprite + 2
	db	PlayerFrameDelay dup PlayerSprite
	db	PlayerFrameDelay dup PlayerSprite + 4
PlayerFramesEnd:

PlayerFrameCount	equ PlayerFramesEnd - PlayerFrames

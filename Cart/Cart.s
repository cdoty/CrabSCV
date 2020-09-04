	cpu	7801

	include "Defines.inc"
	include "Input.inc"
	include "RamDefines.inc"
	include "Sprites.inc"
	include "SystemDefines.inc"
	
	org	8000h

	db	'H'	; Cartridge header

	di
	lxi		sp, StackStart

	jr		start
	
	include "Startup.s"
	include "Game.s"
	include "GameData.s"
	include "Player.s"
	include "Routines.s"
	include "Data.s"
	
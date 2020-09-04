Tools\PNGToBackground Source\Background.png Background
IF ERRORLEVEL 1 goto errorOut

Tools\PNGToSprites Source\Sprites.png Sprites.spr
IF ERRORLEVEL 1 goto errorOut

exit /B 0

:errorOut
echo Build Error

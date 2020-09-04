..\tools\as\asw -g MAP Cart.s
IF ERRORLEVEL 1 goto errorOut

..\tools\as\p2bin Cart.p Crab.bin
IF ERRORLEVEL 1 goto errorOut

..\tools\PadFile 255 32768 Crab.bin
IF ERRORLEVEL 1 goto errorOut

echo Build completed successfully

exit /B 0

:errorOut
echo Build Error

2 color sprite notes:
  
2 color sprites must start in the lower 0x80 bytes of the sprite table.  
bit 0 of the Y position adds 1 to the sprite frame for the overlayed frame.  
bit 0 of the X position adds 8 to the sprite frame for the overlayed frame.  
bit 0 of the tile number inverts the pattern depending the on the X and Y bits.  
The starting sprite palette determines the overlayed palette.  
The sprites can be swapped around to get a different color combination.  
See Enri's document for the palette table and the tile number inversion table.  

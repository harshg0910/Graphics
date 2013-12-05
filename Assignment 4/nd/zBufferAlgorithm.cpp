Initialize
          note : z-depth and z-buffer(x,y) is positive........
           z-buffer(x,y)=max depth; and
           COLOR(x,y)=background color.

Begin:

      for(each polygon P in the polygon list) 
      do{
          for(each pixel(x,y) that intersects P) 
          do{
               Calculate z-depth of P at (x,y)
               If (z-depth < z-buffer[x,y]) 
               then{
                      z-buffer[x,y]=z-depth;
                      COLOR(x,y)=Intensity of P at(x,y);
                   }
            }
        }
  display COLOR array.


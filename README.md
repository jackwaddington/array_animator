# array_animator
_Create an array and display it - repeat._


I have been playing with addressable LEDs. As that project grows arms and legs I saw some fun in playing with the core of how the addressable LEDs are working - arrays.

I have taken that to C in the CLI to simulate a problem I created:

- If I were to have a strip of LEDs, and i tie them onto, for example, the corner of a table - can I walk LEDs out from the centre?
- When a value reaches the end of the string, it should return to its start point.
- The split point can be animated.

We would need to define:
- the point of the corner of the table.
- any trim at the ends - where the LEDs do not need to display - perhaps they are dangling off the end.


Example outputs: 
```
./a.out 40 5 17 10 20
strip_len = 40
l_trim = 5
r_trim = 23
split = 10
cycles = 20
Running for 20 cycles.
     -----|------------                 
     ----//\-----------                 
     ---/-|-\----------                 
     --/--\--\---------                 
     -/---|---\--------                 
     /----/----\-------                 
     -----|-----\------                 
     ----/\------\-----                 
     ---/-|-------\----                 
     --/--/--------\---                 
     -/---|---------\--                 
     /----\----------\-                 
     -----|-----------\                 
     ----//------------                 
     ---/-|\-----------                 
     --/--\-\----------                 
     -/---|--\---------                 
     /----/---\--------                 
     -----|----\-------                 
     ----/\-----\------                 

Finished.
```

```
./a.out 65 25 4 30 20
strip_len = 65
l_trim = 25
r_trim = 61
split = 30
cycles = 20
Running for 20 cycles.
                         -----|------------------------------    
                         ----//\-----------------------------    
                         ---/-|-\----------------------------    
                         --/--\--\---------------------------    
                         -/---|---\--------------------------    
                         /----/----\-------------------------    
                         -----|-----\------------------------    
                         ----/\------\-----------------------    
                         ---/-|-------\----------------------    
                         --/--/--------\---------------------    
                         -/---|---------\--------------------    
                         /----\----------\-------------------    
                         -----|-----------\------------------    
                         ----//------------\-----------------    
                         ---/-|-------------\----------------    
                         --/--\--------------\---------------    
                         -/---|---------------\--------------    
                         /----/----------------\-------------    
                         -----|-----------------\------------    
                         ----/\------------------\-----------    

Finished.
```

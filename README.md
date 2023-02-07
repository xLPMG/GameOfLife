# GameOfLife (Life_Simulator)

My implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++

## Deployment

Build with CMake (version 3.25.2 or newer) <br>
Go to /build and run Life_Simulator file

## Data file usage

You can use text files as input. They need to have the following structure:

[data_size_x] [data_size_y] [world_size]<br>
[x0,0] [x0,1] [x0,2] ... [x0,data_size_x-1]<br>
[x1,0] [x1,1]<br>
[x2,0]<br>
   .<br> 
   .<br>
   .<br>
[xdata_size_y-1,0]

The values do not have to be formatted and are only separated by spaces. For example the matrix structure above can be written as: <br>
[data_size] [world_size] [x0,0] [x0,1] [x0,2] ... [x0,data_size-1] [x1,0] [x1,1] ... [x1,0] [x1,1] ... [x1,data_size-1] ......

### Explanation
Every matrix entry is either 0 (dead cell) or 1 (live cell).<br>
**[data_size_x]** is an integer and specifies how many columns of data the input matrix has (for reading purposes).<br>
**[data_size_y]** is an integer and specifies how many rows of data the input matrix has (for reading purposes).<br>
**[world_size]** can be much larger (>=data_size) and specifies the size of the area (input n for a n*n square for simplicity), where the Game Of Life will be simulated in. Every "field" in the world which lies outside of the specified matrix is set to 0.<br>

Example files can be found in `/configs` <br>
Config files need to be in the same directory as the Life_Simulator file (likely `/build`) as path specification does not work (yet).

# GameOfLife (Life_Simulator)

My implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++

## Demo
Random distribution example:
<img width="1242" alt="random_sim" src="https://user-images.githubusercontent.com/17238289/218282695-5496bbfa-3478-48d0-8fa0-462f37600db3.png">

## Deployment

Build with CMake (version 3.25.2 or newer) <br>
Go to /build and run Life_Simulator file

## Data file usage

You can use text files as input. They need to have the following structure:<br>
---------------------------------------------------------<br>
[data_size_x] [data_size_y] [world_size_x] [world_size_y]<br>
[0,0] [0,1] [0,2] ... [0,data_size_x-1]<br>
[1,0] [1,1]<br>
[2,0]<br>
   .<br> 
   .<br>
   .<br>
[xdata_size_y-1,0]<br>
---------------------------------------------------------<br>
The values do not have to be formatted and are only separated by spaces. For example the matrix structure above can be written as: <br>
[data_size] [world_size] [0,0] [0,1] [0,2] ... [0,data_size-1] [1,0] [1,1] ... [1,0] [1,1] ... [1,data_size-1] ......

### Explanation
Every matrix entry is either 0 (dead cell) or 1 (live cell).<br>
**[data_size_x]** is an integer and specifies how many columns of data the input matrix has (for reading purposes).<br>
**[data_size_y]** is an integer and specifies how many rows of data the input matrix has (for reading purposes).<br>
**[world_size]** can be much larger (>=data_size) and specifies the size of the area, where the Game Of Life will be simulated in. Every "field" in the world which lies outside of the specified matrix is set to 0.<br>
**[world_size_x]** width of the world (integer).<br>
**[world_size_y]** height of the world (integer).<br>


Example files can be found in `/configs` <br>
Config files need to be in the same directory as the Life_Simulator file (likely `/build`) as path specification does not work (yet).

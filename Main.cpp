#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int delay=100000;

int getLivingNeighborsCount(int** world, int world_size_x, int world_size_y, int x, int y)
{
    int count = 0;
    int cX, cY;
    for (int i = -1; i < 2; i++) {
          for (int j = -1; j < 2; j++) {
            cX = x+i;
            cY = y+j;
            if(!(i==0 && j==0) && cX>=0 && cY >= 0 && cX < world_size_y && cY < world_size_x ){
              if(world[cX][cY] == 1){
                  count++;
              }
            }
          }
        }
    return count;
}

int simulate(int** world, int world_size_x, int world_size_y){
  int steps=0;

  //create copy of array as workspace
  int **worldCopy = new int*[world_size_y];
  for (int i = 0; i < world_size_y; i++){
      worldCopy[i] = new int[world_size_x];
  }

  for (int i=0 ; i < world_size_y; i++) {
    for (int j=0 ; j < world_size_x; j++) {
      worldCopy[i][j] = world[i][j];
    }
  }
  while(true){
    for(int i=0;i<world_size_y;i++){
      for(int j=0;j<world_size_x;j++){
        int livingNeighbors = getLivingNeighborsCount(world, world_size_x, world_size_y, i, j);
        //make changes only on copy
        if (world[i][j] == 1 && (livingNeighbors == 2 || livingNeighbors == 3)) {
                worldCopy[i][j] = 1;
                cout << "●";
        } else if (world[i][j] == 0 && livingNeighbors == 3) {
                worldCopy[i][j] = 1;
                cout << "●";
        }else {
                worldCopy[i][j] = 0;
                cout << " ";
        }
      }
      cout << endl;
    }
    cout << "step: " << steps << endl;
    steps++;
    for(int i=0;i<world_size_y+1;i++){
      cout << "\x1b[A";
    }
    //apply changes to real array
    for (int i=0 ; i < world_size_y; i++) {
      for (int j=0 ; j < world_size_x; j++) {
        world[i][j] = worldCopy[i][j];
      }
    }

    usleep(delay);
  }
  return 0;
}

int main(){

  int world_size_x=0;
  int world_size_y=0;

  int spawnchance=50;
  bool useFile = false;
  string response="";
  string inFileName = "example.dat";

  cout << "The Game of Life" << endl;
  cout << "Use a config file? (y/n): ";
  cin >> response;

  if(response=="n"){
  useFile=false;
  cout << "Input a world size (width): ";
  cin >> world_size_x;
  cout << "Input a world size (height): ";
  cin >> world_size_y;
  cout << "Input a spawn chance for a living cell in % (int: 0-100): ";
  cin >> spawnchance;
}else if(response=="y"){
  useFile=true;
  cout << "Provide a file name: ";
  cin >> inFileName;
}else{
  return 0;
}
  cout << "Choose a delay in microseconds(1s = 10^6μs): ";
  cin >> delay;

if(!useFile){
  //set up world
  int **world = new int*[world_size_y];
  for (int i = 0; i < world_size_y; i++){
      world[i] = new int[world_size_x];
  }

  cout << "Generating starting pattern based on spawn chance:" << endl;
  //fill world randomly (using given chance)
  int randNum;
  // i = rows, j = columns
  for (int i = 0; i < world_size_y; i++) {
        for (int j = 0; j < world_size_x; j++) {
          randNum = rand() % 100;
          if(randNum<=spawnchance){
            world[i][j] = 1;
            cout << "●";
          }else {
            world[i][j] = 0;
            cout << " ";
          }

        }
        cout << endl;
    }
    cout << "Starting simulation:" << endl;
    simulate(world, world_size_x, world_size_y);
  } else {
  //read file
  ifstream inFile;
  int data_size_x, data_size_y;

  inFile.open(inFileName.c_str());
    if (inFile.is_open())
    {
      //read data size as first two parameters
      inFile >> data_size_x;
      inFile >> data_size_y;
      //read world size as third and fourth parameter
      inFile >> world_size_x;
      inFile >> world_size_y;

      //set up world
      int **world = new int*[world_size_y];
      for (int i = 0; i < world_size_y; i++){
          world[i] = new int[world_size_x];
      }
      //read file data into world
      cout << "Reading data from file:" << endl;
        for (int i = 0; i < world_size_y; i++) {
              for (int j = 0; j < world_size_x; j++) {
                if( i < data_size_y && j < data_size_x ) {
                  inFile >> world[i][j];
                  if(world[i][j]==1){
                    cout << "●";
                  }else{
                    cout << " ";
                  }
                } else {
                  world[i][j] = 0;
                  cout << " ";
                }
              }

              cout << endl;

          }
        inFile.close();
        cout << "Starting simulation:" << endl;
        simulate(world, world_size_x, world_size_y);
    } else {
        cerr << "Can't find input file " << inFileName << endl;
        return 1;
    }
  }
  return 0;
}

#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int world_size=0;
int delay=100000;

int getLivingNeighborsCount(int** world, int world_size, int x, int y)
{
    int i, j, count = 0;
    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if ((i == x && j == y) || (i < 0 || j < 0)
                || (i >= world_size || j >= world_size)) {
                continue;
            }
            if (world[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

int simulate(int** world, int world_size){
  int steps=0;
  while(true){
    for(int i=0;i<world_size;i++){
      for(int j=0;j<world_size;j++){
        int livingNeighbors = getLivingNeighborsCount(world, world_size, i, j);
        if (world[i][j] == 1 && (livingNeighbors == 2 || livingNeighbors == 3)) {
                world[i][j] = 1;
                cout << "■";
        } else if (world[i][j] == 0 && livingNeighbors == 3) {
                world[i][j] = 1;
                cout << "■";
        }else {
                world[i][j] = 0;
                cout << " ";
        }
      }
      cout << endl;
    }
    cout << "step: " << steps << endl;
    steps++;
    for(int i=0;i<world_size+1;i++){
      cout << "\x1b[A";
    }
    usleep(delay);
  }
  return 0;
}

int main(){

  int spawnchance=50;
  bool useFile = false;
  string response="";
  string inFileName = "example.dat";

  cout << "The Game of Life" << endl;
  cout << "Use a config file? (y/n): ";
  cin >> response;

  if(response=="n"){
  useFile=false;
  cout << "Input a world size: ";
  cin >> world_size;
  cout << "Input a spawn chance for a living cell in % (int: 0-100): ";
  cin >> spawnchance;
}else if(response=="y"){
  useFile=true;
  cout << "Provide a file name: ";
  cin >> inFileName;
}else{
  return 0;
}
  cout << "Choose a delay in microseconds(100000 recommended): ";
  cin >> delay;

if(!useFile){
  //set up world
  int world[world_size][world_size];
  int *px[world_size];
  for (int i = 0; i < world_size; i++){
      px[i] = world[i];
}
  //fill world randomly (using given chance)
  int randNum;
  for (int i = 0; i < world_size; i++) {
        for (int j = 0; j < world_size; j++) {
          randNum = rand() % 100;
          if(randNum<=spawnchance){
            world[i][j] = 1;
          }else {
            world[i][j] = 0;
          }

        }
    }
    simulate(px, world_size);
  } else {
  //read file
  ifstream inFile;
  inFile.open(inFileName.c_str());
    if (inFile.is_open())
    {
      //read world size in first line
      inFile >> world_size;

      //set up world
      int world[world_size][world_size];
      int *px[world_size];
      for (int i = 0; i < world_size; i++){
          px[i] = world[i];
        }
      //read file data into world
      for (int i = 0; i < world_size; i++) {
            for (int j = 0; j < world_size; j++) {
                inFile >> world[i][j];
            }
        }
        inFile.close();
        simulate(px, world_size);
    } else {
        cerr << "Can't find input file " << inFileName << endl;
        return 1;
    }
  }
  return 0;
}

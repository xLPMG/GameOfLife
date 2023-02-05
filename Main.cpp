#include <iostream>
#include <unistd.h>

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

  cout << "The Game of Life" << endl;
  cout << "Input a world size: ";
  cin >> world_size;
  cout << "Choose a delay in microseconds(100000 recommended): ";
  cin >> delay;

  int world[world_size][world_size];

  // Build an array of pointers to rows.
  int *px[world_size];
  for (int i = 0; i < world_size; i++)
      px[i] = world[i];

  for (int i = 0; i < world_size; i++) {
        for (int j = 0; j < world_size; j++) {
            world[i][j] = rand() % 2;
        }
    }

  simulate(px, world_size);

  return 0;
}

#include <iostream>
//#include "gtest/gtest.h"
#include "Matrix.h"
#include "Map.h"
#include "Bfs.h"
#include "GameFlow.h"
#include "Udp.h"
#include <unistd.h>

using namespace std;

int main(int args, char **argv) {
    GameFlow *g = new GameFlow(atoi(argv[1]));
    g->startGame();
    delete (g);
    return 0;
}

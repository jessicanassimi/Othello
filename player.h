#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
using namespace std;

#define BOARD_SIZE 8

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Move *> get_possible_moves(Board *board, Side side);
    int compute_score(Board *board);
    int competitive_compute_score(Board *board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *board;
    Side my_side;
    Side other_side;
    int heuristic[BOARD_SIZE][BOARD_SIZE];
};

#endif

#include "player.h"
#include <vector>

using namespace std;

#define BOARD_SIZE 8

// Testing Github 

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = new Board();
    my_side = side;
    if (my_side == BLACK)
    {
		other_side = WHITE;
	}
	else
	{
		other_side = BLACK;
	}
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	/*
	 * TODO
	 */
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    if (opponentsMove != NULL)
    {
		board->doMove(opponentsMove, other_side);
	}
	if (board->isDone() || !board->hasMoves(my_side))
	{
		return NULL;
	}
	vector<Move *> possible_moves;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			Move *move = new Move(i, j);
			if (board->checkMove(move, my_side))
			{
				possible_moves.push_back(move);
			}
			else
			{
				delete move;
			}
		}
	}
	board->doMove(possible_moves[0], my_side);
	return possible_moves[0];
}

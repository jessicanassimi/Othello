#include "player.h"


using namespace std;

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
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			heuristic[i][j] = 0;
		}
	}
	heuristic[0][0] = 15;
	heuristic[0][BOARD_SIZE-1] = 15;
	heuristic[BOARD_SIZE-1][0] = 15;
	heuristic[BOARD_SIZE-1][BOARD_SIZE-1] = 15;
	
	heuristic[0][1] = -5;
	heuristic[1][0] = -5;
	heuristic[BOARD_SIZE-2][0] = -5;
	heuristic[BOARD_SIZE-1][1] = -5;
	heuristic[0][BOARD_SIZE-2] = -5;
	heuristic[1][BOARD_SIZE-1] = -5;
	heuristic[BOARD_SIZE-1][BOARD_SIZE-2] = -5;
	heuristic[BOARD_SIZE-2][BOARD_SIZE-1] = -5;
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
	if (testingMinimax)
	{
		vector<Move *> possible_moves = get_possible_moves(board, my_side);
		int maximum = -100000;
		Move *bestMove = NULL;
		for (int i = 0; i < possible_moves.size(); i++)
		{
			Board *copy = board->copy();
			copy->doMove(possible_moves[i], my_side);
			vector<Move *> level1 = get_possible_moves(copy, other_side);
			int minimum = 10000;
			for (int j = 0; j < level1.size(); j++)
			{
				Board *copy2 = copy->copy();
				copy2->doMove(level1[j], other_side);
				int score = compute_score(copy2);
				if (score < minimum)
				{
					minimum = score;
				}
			}
			if (minimum > maximum) 
			{
			    maximum = minimum;
			    bestMove = possible_moves[i];
			}
		}
		board->doMove(bestMove, my_side);
		return bestMove;
	}
	else
	{
		
		vector<Move *> possible_moves = get_possible_moves(board, my_side);
		int maximum = -100000;
		Move *bestMove = NULL;
		for (int i = 0; i < possible_moves.size(); i++)
		{
			Board *copy = board->copy();
			copy->doMove(possible_moves[i], my_side);
			vector<Move *> level1 = get_possible_moves(copy, other_side);
			int minimum = 10000;
			for (int j = 0; j < level1.size(); j++)
			{
				Board *copy2 = copy->copy();
				copy2->doMove(level1[j], other_side);
				int score = competitive_compute_score(copy2);
				if (score < minimum)
				{
					minimum = score;
				}
			}
			if (minimum > maximum) 
			{
			    maximum = minimum;
			    bestMove = possible_moves[i];
			}
		}
		board->doMove(bestMove, my_side);
		return bestMove;
	}
	
}

vector<Move *> Player::get_possible_moves(Board *board, Side side)
{
	vector<Move *> possible_moves;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			Move *move = new Move(i, j);
			if (board->checkMove(move, side))
			{
				possible_moves.push_back(move);
			}
			else
			{
				delete move;
			}
		}
	}
	return possible_moves;
}

int Player::compute_score(Board *board)
{
	if (my_side == WHITE)
	{
		return board->countWhite() - board->countBlack();
	}
	else
	{
		return board->countBlack() - board->countWhite();
	}
}

int Player::competitive_compute_score(Board *board)
{
	
	int sum = 0;
	for (int i = 0; i < BOARD_SIZE; i++) 
	{
		for (int j = 0; j < BOARD_SIZE; j++) 
		{
			if (board->get(my_side, i, j)) 
			{
				sum += heuristic[i][j];	
			}
			else if (board->get(other_side, i, j)) 
			{
				sum -= heuristic[i][j];	
			}
		}
	}
	return sum;
}

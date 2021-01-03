#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

int Point(Board board, Player player)
{
    int player_orbs = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (player.get_color() == board.get_cell_color(i, j)) {
                player_orbs += board.get_orbs_num(i, j);
            }
        }
    }
    return player_orbs;
}

int alphabeta_minimax(int depth, bool maximizingPlayer, int alpha, int beta, Board board, Player* player, Player* enemy, int* x_pos, int* y_pos)
{
    int point;
    int largest;
    bool first_valid = true;
    Board board_temp = board;
    if (depth == 5) {
        // return the number of orbs of the player's color
        return Point(board, *player);
    }
    if (maximizingPlayer) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                if (board.place_orb(i, j, player)) {
                    point = max(alpha, alphabeta_minimax(depth + 1, false, alpha, beta, board, player, enemy, x_pos, y_pos));

                    // if the depth is 0, then x_pos & y_pos are the row & col where the largest point exists
                    // we need to find the row & col that has the largest point
                    // if the point is the largest, then x_pos = row, y_pos = j
                    if (depth == 0) {
                        if (first_valid) {
                            largest = point;
                            first_valid = false;
                            *x_pos = i;
                            *y_pos = j;
                        }
                        if (point > largest) {
                            largest = point;
                            *x_pos = i;
                            *y_pos = j;
                        }
                    }
                    board = board_temp;
                    alpha = point;              // point >= alpha
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return alpha;
    }
    else {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                if (board.place_orb(i, j, enemy)) {
                    beta = min(beta, alphabeta_minimax(depth + 1, true, alpha, beta, board, player, enemy, x_pos, y_pos));
                    board = board_temp;
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return beta;
    }
}


void algorithm_A(Board board, Player player, int index[]){
    ////    TIME    ////
    //clock_t start = clock();
    ////    TIME    ////


    ////    VARIABLES   ////
    int row;    // the row to place orb
    int col;    // the col to place orb
    char color;
    ////    VARIABLES   ////


    ////    PLAYER  ////
    Player R_player('r');
    Player B_player('b');
    ////    PLAYER  ////


    ////    MINIMAX     ////
    color = player.get_color();     // know which color the algo will play
    if (color == 'r')               // player means red
        alphabeta_minimax(0, true, -32768, 32767, board, &R_player, &B_player, &row, &col);
    else if (color == 'b')          // player means blue
        alphabeta_minimax(0, true, -32768, 32767, board, &B_player, &R_player, &row, &col);
    ////    MINIMAX     ////


    ////    OUTPUT INDEX    ////
    index[0] = row;
    index[1] = col;
    ////    OUTPUT INDEX    ////

    ////    TIME    ////
    //clock_t end = clock();
    //double time_taken = double(end - start) / CLOCKS_PER_SEC;
    //cout << "Algorithm_A Time: " << time_taken << endl;
    ////    TIME    ////
}
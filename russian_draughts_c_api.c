
#include "russian_draughts_c_api.h"

void clearBoard(int(*cells)[8][8]) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (getCellColor(r, c) == BOARD_CELL_COLOR_WHITE) {
				(*cells)[r][c] = BOARD_CELL_STATUS_INVALID;
				continue;
			}
			(*cells)[r][c] =BOARD_CELL_STATUS_FREE;
		}
	}
}

void initBoard(int (*cells)[8][8]) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (getCellColor(r, c) == BOARD_CELL_COLOR_WHITE) {
				(*cells)[r][c] = BOARD_CELL_STATUS_INVALID;
				continue;
			}
			(*cells)[r][c] = (r < 3)? BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE : BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE;
		}
	}
}

int getCellColor(int row, int col) {
	if (row < 0 || col < 0 || row > 7 || col > 7) return BOARD_CELL_COLOR_INVALID;
	if (row % 2) return (col % 2) ? BOARD_CELL_COLOR_BLACK: BOARD_CELL_COLOR_WHITE;
	return (col % 2) ? BOARD_CELL_COLOR_WHITE: BOARD_CELL_COLOR_BLACK;
}

/*
	getCellStatus:
		checks cells status, color and check if cell is inside board boundaries
*/
int getCellStatus(int(*cells)[8][8], int row, int col) {
	if (row < 0 || col < 0 || row > 7 || col > 7) return BOARD_CELL_STATUS_INVALID;
	return (*cells)[row][col];
}

int thereIsAQueenInCell(int bcs) {
	return bcs == BOARD_CELL_STATUS_OCCUPIED_WITH_RED_QUEEN_PIECE || bcs == BOARD_CELL_STATUS_OCCUPIED_WITH_WHITE_QUEEN_PIECE;
}

int getPieceColor(int bcs) {
	if (bcs == BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE || bcs == BOARD_CELL_STATUS_OCCUPIED_WITH_WHITE_QUEEN_PIECE) return PIECE_COLOR_WHITE;
	if (bcs == BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE || bcs == BOARD_CELL_STATUS_OCCUPIED_WITH_RED_QUEEN_PIECE) return PIECE_COLOR_RED;
	return PIECE_COLOR_INVALID;
}

int changeCellStatus(int(*cells)[8][8], int row, int col, int ncs) {
	if (getCellStatus(cells, row, col) == BOARD_CELL_STATUS_INVALID) return 0;
	if (ncs < BOARD_CELL_STATUS_FREE || ncs > BOARD_CELL_STATUS_OCCUPIED_WITH_RED_QUEEN_PIECE) return 0;
	(*cells)[row][col] = ncs;
	return 1;
}

/*
	isValidMove: checks if proposed move is valid, and returns resulting move type

	IMPORTANT: russian draught rules taken from:
		http://www.ludoteka.com/damas_rusas.html
*/
int isValidMove(int (*cells)[8][8], int start_row, int start_col, int end_row, int end_col, int *taken_oponent_piece_row, int *taken_oponent_piece_col) {
	// no move: start and end positions are the same
	if (start_row == end_row && start_col == end_col) return MOVE_TYPES_INVALID;

	// only diagonal moves are allowed
	if (start_col != end_col + end_row - start_row && start_col != end_col - end_row + start_row) return MOVE_TYPES_INVALID;

	// checking start cell
	int starting_cell_status = getCellStatus(cells, start_row, start_col);
	if (starting_cell_status == BOARD_CELL_STATUS_INVALID) return MOVE_TYPES_INVALID;// a cell with status "invalid" cann't be used to receive/content a piece (white cells or out of board cells)
	if (starting_cell_status == BOARD_CELL_STATUS_FREE) return MOVE_TYPES_INVALID;// starting cell must content a piece

	// checking end cell
	int end_cell_status = getCellStatus(cells, end_row, end_col);
	if (end_cell_status == BOARD_CELL_STATUS_INVALID) return MOVE_TYPES_INVALID;// a cell with status "invalid" cann't be used to receive/content a piece (white cells or out of board cells)
	if (end_cell_status != BOARD_CELL_STATUS_FREE) return MOVE_TYPES_INVALID;// destination cell must be empty

	// checking queen moves
	if (thereIsAQueenInCell(starting_cell_status))
	{
		// looking for numbers of pieces inside queen move, just one oponent piece allowed (taking oponent piece) and no one own piece allowed
		int row_direction = (end_row > start_row) ? 1 : -1;// computing move vector
		int col_direction = (end_col > start_col) ? 1 : -1;
		int queen_color = getPieceColor(starting_cell_status);
		int oponent_piece_count = 0;

		// check all cells in diagonal, between startin cell and ending cell
		for (int row = start_row + row_direction, col = start_col + col_direction; row != end_row; row += row_direction, col += col_direction)
		{
			int actual_piece_color = getPieceColor(getCellStatus(cells, row, col));
			if (actual_piece_color == PIECE_COLOR_INVALID) continue;// no piece in actual checked cell
			if (queen_color == actual_piece_color) return MOVE_TYPES_INVALID;// queen is trying to jump over own pieces
			if (oponent_piece_count > 0) return MOVE_TYPES_INVALID;// there is more than one oponent piece in queen move
			if(taken_oponent_piece_row) *taken_oponent_piece_row = row;
			if(taken_oponent_piece_col) *taken_oponent_piece_col = col;
			oponent_piece_count++;
		}
		if (oponent_piece_count == 1) return MOVE_TYPES_TAKING_OPONENT_PIECE;
		return MOVE_TYPES_SINGLE_MOVE;
	}

	// checking single piece moves
	int num_steps;
	switch (getPieceColor(starting_cell_status))
	{
	case PIECE_COLOR_WHITE:
		num_steps = end_row - start_row;
		break;
	case PIECE_COLOR_RED:
		num_steps = start_row - end_row;
		break;
	default:
		return MOVE_TYPES_INVALID;
	}

	if (num_steps == 1) return MOVE_TYPES_SINGLE_MOVE;// single piece moving a single step to free cell
	if (num_steps == -1) return MOVE_TYPES_INVALID;// single piece trying to move backwards
	if (num_steps > 2 || num_steps < -2) return MOVE_TYPES_INVALID;// single piece trying to move like a queen

	// this move is only valid if there is a oponent piece in the middle (taking oponent piece)
	int middle_row = (start_row + end_row) / 2;
	int middle_col = (start_col + end_row) / 2;
	int middle_piece_color = getPieceColor(getCellStatus(cells, middle_row, middle_col));
	if (middle_piece_color == PIECE_COLOR_INVALID) return MOVE_TYPES_INVALID;// there is not a piece in middle cell
	if (middle_piece_color == getPieceColor(starting_cell_status)) return MOVE_TYPES_INVALID;// there is a own piece in the middle cell
	if(taken_oponent_piece_row) *taken_oponent_piece_row = middle_row;
	if(taken_oponent_piece_col) *taken_oponent_piece_col = middle_col;
	return MOVE_TYPES_TAKING_OPONENT_PIECE;
}


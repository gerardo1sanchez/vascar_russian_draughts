
enum PIECE_COLOR {
	PIECE_COLOR_INVALID,
	PIECE_COLOR_WHITE,
	PIECE_COLOR_RED
};

enum BOARD_CELL_STATUS {
	BOARD_CELL_STATUS_INVALID,// this isnn't a valid cell, must not be used, and this is a end state (cann't be changed)
	BOARD_CELL_STATUS_FREE,
	BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE,
	BOARD_CELL_STATUS_OCCUPIED_WITH_WHITE_QUEEN_PIECE,
	BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE,
	BOARD_CELL_STATUS_OCCUPIED_WITH_RED_QUEEN_PIECE
};

enum BOARD_CELL_COLOR {
	BOARD_CELL_COLOR_INVALID,
	BOARD_CELL_COLOR_WHITE,
	BOARD_CELL_COLOR_BLACK
};

enum MOVE_TYPES {
	MOVE_TYPES_INVALID,
	MOVE_TYPES_SINGLE_MOVE,
	MOVE_TYPES_TAKING_OPONENT_PIECE
};

int getCellColor(int row, int col);
void initBoard(int (*cells)[8][8]);
void clearBoard(int (*cells)[8][8]);
int getCellColor(int row, int col);
int getCellStatus(int(*cells)[8][8], int row, int col);
int thereIsAQueenInCell(int bcs);
int getPieceColor(int bcs);
int changeCellStatus(int(*cells)[8][8], int row, int col, int ncs);
int isValidMove(int (*cells)[8][8], int start_row, int start_col, int end_row, int end_col, int *taken_oponent_piece_row, int *taken_oponent_piece_col);

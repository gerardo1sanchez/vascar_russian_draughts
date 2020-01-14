
#include "gtest/gtest.h"

extern "C" {
#include "../russian_draughts_c_api.h"
}

TEST(Board_Iniciatialization, InitBoard) {
	int cells [8][8];
	initBoard(&cells);


	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 8; col++) {
			switch (row)
			{
			case 0:
			case 2:
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE);
				}
				break;
			case 1:
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				break;
			case 3:
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_FREE);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				break;
			case 4:
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_FREE);
				}
				break;
			case 5:
			case 7:
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				break;
			case 6:
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE);
				}
				break;
			}
		}
	}
}

TEST(Board_Iniciatialization, ClearBoard) {
	int cells [8][8];
	clearBoard(&cells);

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 8; col++) {
			if (row % 2) {
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_FREE);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
			}
			else {
				if (col % 2) {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_INVALID);
				}
				else {
					EXPECT_TRUE(getCellStatus(&cells, row, col) == BOARD_CELL_STATUS_FREE);
				}
			}
		}
	}
}

TEST(SinglePiecesMoves, Invalid_Move_Over_Occupied_Cell)
{
	int cells[8][8];

	// white pieces one step move
	for (int row = 0; row < 7; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
			if (col > 0) {
				EXPECT_TRUE(changeCellStatus(&cells, row + 1, col - 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row + 1, col - 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
				EXPECT_TRUE(changeCellStatus(&cells, row + 1, col - 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row + 1, col - 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
			}
			if (col < 7) {
				EXPECT_TRUE(changeCellStatus(&cells, row + 1, col + 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row + 1, col + 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
				EXPECT_TRUE(changeCellStatus(&cells, row + 1, col + 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row + 1, col + 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
			}
		}
	}

	// red pieces one step move
	for (int row = 1; row < 8; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
			if (col > 0) {
				EXPECT_TRUE(changeCellStatus(&cells, row - 1, col - 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row - 1, col - 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
				EXPECT_TRUE(changeCellStatus(&cells, row - 1, col - 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row - 1, col - 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
			}
			if (col < 7) {
				EXPECT_TRUE(changeCellStatus(&cells, row - 1, col + 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row - 1, col + 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
				EXPECT_TRUE(changeCellStatus(&cells, row - 1, col + 1, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
				EXPECT_TRUE(isValidMove(&cells, row, col, row - 1, col + 1, nullptr, nullptr) == MOVE_TYPES_INVALID);
			}
		}
	}
}

TEST(SinglePiecesMoves, Valid_One_Step_Moves) {
	int cells[8][8];

	// white pieces one step move
	for (int row = 0; row < 7; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
			if (col > 0) {
				EXPECT_TRUE(isValidMove(&cells, row, col, row + 1, col - 1, nullptr, nullptr) == MOVE_TYPES_SINGLE_MOVE);
			}
			if (col < 7) {
				EXPECT_TRUE(isValidMove(&cells, row, col, row + 1, col + 1, nullptr, nullptr) == MOVE_TYPES_SINGLE_MOVE);
			}
		}
	}

	// red pieces one step move
	for (int row = 1; row < 8; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
			if (col > 0) {
				EXPECT_TRUE(isValidMove(&cells, row, col, row - 1, col - 1, nullptr, nullptr) == MOVE_TYPES_SINGLE_MOVE);
			}
			if (col < 7) {
				EXPECT_TRUE(isValidMove(&cells, row, col, row - 1, col + 1, nullptr, nullptr) == MOVE_TYPES_SINGLE_MOVE);
			}
		}
	}
}

TEST(SinglePiecesMoves, Invalid_Dialogonal_Moves) {
	int cells[8][8];

	// analizing invalid moves for white pieces
	for (int row = 0; row < 8; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
			for (int offset = 2; offset < 8; offset++) {
				EXPECT_TRUE(isValidMove(&cells, row, col, (row - offset) % 8, (col - offset) % 8, nullptr, nullptr) == MOVE_TYPES_INVALID);
				EXPECT_TRUE(isValidMove(&cells, row, col, (row - offset) % 8, (col - offset) % 8, nullptr, nullptr) == MOVE_TYPES_INVALID);
			}
		}
	}

	// analizing invalid moves for red pieces
	for (int row = 0; row < 8; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
			for (int offset = 1; offset < 7; offset++) {
				EXPECT_TRUE(isValidMove(&cells, row, col, (row + offset) % 8, (col + offset) % 8, nullptr, nullptr) == MOVE_TYPES_INVALID);
				EXPECT_TRUE(isValidMove(&cells, row, col, (row + offset) % 8, (col + offset) % 8, nullptr, nullptr) == MOVE_TYPES_INVALID);
			}
		}
	}
}

TEST(SinglePiecesMoves, Invalid_Horizontal_Moves) {
	int cells [8][8];

	// white horizontal moves
	for (int row = 0; row < 3; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
			for (int offset = 1; offset < 8; offset++) {
				EXPECT_TRUE(isValidMove(&cells, row, col, row, (col + offset) % 8, nullptr, nullptr) == 0);
			}
		}
	}

	// red horizontal moves
	for (int row = 5; row < 8; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
			for (int offset = 1; offset < 8; offset++) {
				EXPECT_TRUE(isValidMove(&cells, row, col, row, (col + offset) % 8, nullptr, nullptr) == 0);
			}
		}
	}
}

TEST(SinglePiecesMoves, Invalid_Vertical_Moves) {
	int cells [8][8];
	initBoard(&cells);

	// white vertical moves
	for (int row = 0; row < 3; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_WHITE_PIECE) != 0);
			for (int offset = 1; offset < 8; offset++) {
				EXPECT_TRUE(isValidMove(&cells, row, col, (row + offset) % 8, col, nullptr, nullptr) == 0);
			}
		}
	}

	// red vertical moves
	for (int row = 5; row < 8; row++) {
		for (int col = (row % 2); col < 8; col += 2) {
			clearBoard(&cells);
			EXPECT_TRUE(changeCellStatus(&cells, row, col, BOARD_CELL_STATUS_OCCUPIED_WITH_SINGLE_RED_PIECE) != 0);
			for (int offset = 1; offset < 8; offset++) {
				EXPECT_TRUE(isValidMove(&cells, row, col, (row + offset) % 8, col, nullptr, nullptr) == 0);
			}
		}
	}
}

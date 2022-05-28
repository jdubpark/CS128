#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col < 0 || col >= Board::kBoardWidth) {
    throw runtime_error("Invalid column is provided!");
  }

  int row = 0;
  while (b.board[row][col] != DiskType::kEmpty && row < Board::kBoardHeight) {
    row++;
  }

  if (b.board[row][col] != DiskType::kEmpty) {
    throw runtime_error("All rows for the given column are filled!");
  }

  b.board[row][col] = disk;
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag) ||
         SearchForWinner(b, disk, WinningDirection::kLeftDiag);
}

bool SearchHorizontal(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth - 3; i++) {
    // check four horizontally, from i to i + 3, for each row
    for (int j = 0; j < Board::kBoardHeight; j++) {
      if (b.board[j][i] == disk && b.board[j][i + 1] == disk &&
          b.board[j][i + 2] == disk && b.board[j][i + 3] == disk)
        return true;
    }
  }
  return false;
}

bool SearchVertical(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight - 3; i++) {
    // check four vertically, from i to i + 3, for each col
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk && b.board[i + 1][j] == disk &&
          b.board[i + 2][j] == disk && b.board[i + 3][j] == disk)
        return true;
    }
  }
  return false;
}

bool SearchRightDiag(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight - 3; i++) {
    // check four right diagonally, i to i + 3, for each col from j to j + 3
    for (int j = 0; j < Board::kBoardWidth - 3; j++) {
      if (b.board[i][j] == disk && b.board[i + 1][j + 1] == disk &&
          b.board[i + 2][j + 2] == disk && b.board[i + 3][j + 3] == disk)
        return true;
    }
  }
  return false;
}

bool SearchLeftDiag(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight - 3; i++) {
    for (int j = 0; j < Board::kBoardWidth - 3; j++) {
      if (b.board[i][j + 3] == disk && b.board[i + 1][j + 2] == disk &&
          b.board[i + 2][j + 1] == disk && b.board[i + 3][j] == disk)
        return true;
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  switch (to_check) {
  case WinningDirection::kHorizontal: {
    return SearchHorizontal(b, disk);
    break;
  }
  case WinningDirection::kVertical: {
    return SearchVertical(b, disk);
    break;
  }
  case WinningDirection::kRightDiag: {
    return SearchRightDiag(b, disk);
    break;
  }
  default:
    return SearchLeftDiag(b, disk);
    break;
  }
}

bool BoardLocationInBounds(int row, int col) {
  return (row >= 0 && row < Board::kBoardHeight) &&
         (col >= 0 && col < Board::kBoardWidth);
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
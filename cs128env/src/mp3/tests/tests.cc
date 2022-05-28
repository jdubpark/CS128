// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Board column overflow", "[board_col_overflow]") {
  Board board;  // NOLINT
  InitBoard(board);

  // Should overflow on 7th drop on the same col
  int col = 1;
  DropDiskToBoard(board, DiskType::kPlayer1, col);
  DropDiskToBoard(board, DiskType::kPlayer2, col);
  DropDiskToBoard(board, DiskType::kPlayer1, col);
  DropDiskToBoard(board, DiskType::kPlayer2, col);
  DropDiskToBoard(board, DiskType::kPlayer1, col);
  DropDiskToBoard(board, DiskType::kPlayer2, col);
  REQUIRE_THROWS_AS(DropDiskToBoard(board, DiskType::kPlayer1, col),
                    std::runtime_error);
}

TEST_CASE("Board position non-existent", "[board_pos_nonexistent]") {
  Board board;  // NOLINT
  InitBoard(board);

  REQUIRE(!BoardLocationInBounds(100, 100));
  REQUIRE_THROWS_AS(DropDiskToBoard(board, DiskType::kPlayer1, -100),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(board, DiskType::kPlayer1, 100),
                    std::runtime_error);
}

TEST_CASE("Board solved horizontally", "[board_solve_horizontal]") {
  Board board;  // NOLINT
  InitBoard(board);

  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 1);
  DropDiskToBoard(board, DiskType::kPlayer1, 2);
  DropDiskToBoard(board, DiskType::kPlayer1, 3);
  REQUIRE(CheckForWinner(board, DiskType::kPlayer1));
}

TEST_CASE("Board solved vertically", "[board_solve_vertical]") {
  Board board;  // NOLINT
  InitBoard(board);

  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  REQUIRE(CheckForWinner(board, DiskType::kPlayer1));
}

TEST_CASE("Board solved left diagonally", "[board_solve_left_diag]") {
  Board board;  // NOLINT
  InitBoard(board);

  // 2
  // 1 2
  // 1 1 2
  // 1 1 1 2
  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 0);
  DropDiskToBoard(board, DiskType::kPlayer1, 1);
  DropDiskToBoard(board, DiskType::kPlayer1, 1);
  DropDiskToBoard(board, DiskType::kPlayer1, 2);
  DropDiskToBoard(board, DiskType::kPlayer2, 0);
  DropDiskToBoard(board, DiskType::kPlayer2, 1);
  DropDiskToBoard(board, DiskType::kPlayer2, 2);
  DropDiskToBoard(board, DiskType::kPlayer2, 3);
  REQUIRE(CheckForWinner(board, DiskType::kPlayer2));
}

TEST_CASE("Board solved right diagonally", "[board_solve_right_diag]") {
  Board board;  // NOLINT
  InitBoard(board);

  //       2
  //     2 1
  //   2 1 1
  // 2 1 1 1
  DropDiskToBoard(board, DiskType::kPlayer1, 1);
  DropDiskToBoard(board, DiskType::kPlayer1, 2);
  DropDiskToBoard(board, DiskType::kPlayer1, 2);
  DropDiskToBoard(board, DiskType::kPlayer1, 3);
  DropDiskToBoard(board, DiskType::kPlayer1, 3);
  DropDiskToBoard(board, DiskType::kPlayer1, 3);
  DropDiskToBoard(board, DiskType::kPlayer2, 0);
  DropDiskToBoard(board, DiskType::kPlayer2, 1);
  DropDiskToBoard(board, DiskType::kPlayer2, 2);
  DropDiskToBoard(board, DiskType::kPlayer2, 3);
  REQUIRE(CheckForWinner(board, DiskType::kPlayer2));
}

/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

bool IsSolved(WordLocation wl, std::vector<CharPositions> cps) {
  if (wl.word.empty()) {
    return false;
  }
  for (size_t i = 0; i < wl.char_positions.size(); i++) {
    CharPositions cp1 = wl.char_positions.at(i);
    CharPositions cp2 = cps.at(i);
    if (cp1.character != cp2.character || cp1.row != cp2.row ||
        cp1.col != cp2.col) {
      return false;
    }
  }
  return true;
}

TEST_CASE("Horizontal", "[horizontal]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u', 'd'},
                                        {'h', 'e', 'l', 'l', 'o', 'x'},
                                        {'c', 'a', 'l', 'o', 'm', 'd'},
                                        {'a', 'e', 't', 'p', 'o', 'o'},
                                        {'t', 'j', 'u', 's', 't', 'w'}};
  WordSearchSolver wss(puzzle);
  REQUIRE(IsSolved(wss.FindWord("hello"),
                   {CharPositions{'h', 1, 0},
                    CharPositions{'e', 1, 1},
                    CharPositions{'l', 1, 2},
                    CharPositions{'l', 1, 3},
                    CharPositions{'o', 1, 4}}));
}

TEST_CASE("Vertical", "[vertical]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'h', 'u', 'd'},
                                        {'o', 'e', 'l', 'e', 'o', 'x'},
                                        {'c', 'p', 'l', 'l', 'm', 'd'},
                                        {'a', 'o', 't', 'l', 'o', 'o'},
                                        {'t', 'o', 'u', 'o', 't', 'w'}};
  WordSearchSolver wss(puzzle);
  REQUIRE(IsSolved(wss.FindWord("cat"),
                   {CharPositions{'c', 2, 0},
                    CharPositions{'a', 3, 0},
                    CharPositions{'t', 4, 0}}));
}

TEST_CASE("Left Diagonal", "[left-diagonal]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'h', 'u', 'd'},
                                        {'j', 'e', 'a', 'e', 'e', 'x'},
                                        {'u', 'l', 'l', 'b', 'm', 'g'},
                                        {'o', 'o', 'u', 'a', 'o', 'o'},
                                        {'t', 't', 't', 'o', 't', 'm'}};
  WordSearchSolver wss(puzzle);
  REQUIRE(IsSolved(wss.FindWord("mat"),
                   {{CharPositions{'m', 2, 4}},
                    {CharPositions{'a', 3, 3}},
                    {CharPositions{'t', 4, 2}}}));
}

TEST_CASE("Right Diagonal", "[right-diagonal]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'h', 'u', 'd'},
                                        {'h', 'e', 'l', 'e', 'o', 'x'},
                                        {'u', 'a', 'l', 'b', 'm', 'g'},
                                        {'s', 'o', 't', 'l', 'o', 'o'},
                                        {'t', 'o', 'u', 'o', 't', 'w'}};
  WordSearchSolver wss(puzzle);
  REQUIRE(IsSolved(wss.FindWord("hat"),
                   {CharPositions{'h', 1, 0},
                    CharPositions{'a', 2, 1},
                    CharPositions{'t', 3, 2}}));
  // REQUIRE_THROWS_AS(IsSolved(wss.FindWord("dingdong"),
  //                            {CharPositions{'h', 1, 0},
  //                             CharPositions{'e', 1, 1},
  //                             CharPositions{'l', 1, 2},
  //                             CharPositions{'l', 1, 3},
  //                             CharPositions{'o', 1, 4}}),
  //                   std::out_of_range);
}

// TEST_CASE("Fail Cases", "[fail]") {
//   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'h', 'u', 'd'},
//                                         {'h', 'e', 'l', 'e', 'o', 'x'},
//                                         {'u', 'a', 'l', 'b', 'm', 'g'},
//                                         {'s', 'o', 't', 'l', 'o', 'o'},
//                                         {'t', 'o', 'u', 'o', 't', 'w'}};
//   WordSearchSolver wss(puzzle);
//   REQUIRE_THROWS_AS(IsSolved(wss.FindWord("dingdong"),
//                              {CharPositions{'h', 1, 0},
//                               CharPositions{'e', 1, 1},
//                               CharPositions{'l', 1, 2},
//                               CharPositions{'l', 1, 3},
//                               CharPositions{'o', 1, 4}}),
//                     std::out_of_range);
// }

/////////////////////////////////////////////////////////////////////////////////////////////
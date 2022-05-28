#include "WordSearchSolver.hpp"

#include <cstddef>
#include <iostream>
#include <limits>

#include "CharPositions.hpp"
#include "WordLocation.hpp"

using namespace std;

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

bool LocationInBounds(size_t row, size_t col, size_t height, size_t width) {
  return ((row < height) && (col < width));
}

WordSearchSolver::WordSearchSolver(const vector<vector<char>>& puzzle):
    puzzle_(puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation FindWordHorizontal(const string& word,
                                const vector<vector<char>>& puzzle) {
  size_t height = puzzle.size();
  size_t word_size = word.size();
  for (size_t i = 0; i < height; i++) {
    vector<char> row = puzzle.at(i);
    string row_word(row.begin(), row.end());  // vector<char> to string
    for (size_t j = 0; j < row_word.size() - word_size + 1; j++) {
      string row_sub_word = row_word.substr(j, word_size);
      if (word == row_sub_word) {
        vector<CharPositions> char_positions;
        for (size_t k = j; k < j + word_size; k++) {
          CharPositions cp = CharPositions{row_word.at(k), i, k};
          char_positions.push_back(cp);
        }
        return WordLocation{word, char_positions};
      }
    }
  }
  return WordLocation{};
}

WordLocation FindWordVertical(const string& word,
                              const vector<vector<char>>& puzzle) {
  size_t height = puzzle.size();
  size_t width = puzzle.at(0).size();
  size_t word_size = word.size();
  for (size_t i = 0; i < width; i++) {
    string col_word;
    for (size_t j = 0; j < height; j++) {
      col_word.push_back(puzzle.at(j).at(i));
    }
    for (size_t j = 0; j < col_word.size() - word_size + 1; j++) {
      string col_sub_word = col_word.substr(j, word_size);
      if (word == col_sub_word) {
        vector<CharPositions> char_positions;
        for (size_t k = j; k < j + word_size; k++) {
          // cout << word << ":" << i << ":" << k << endl;
          CharPositions cp = CharPositions{col_word.at(k), k, i};
          char_positions.push_back(cp);
        }
        return WordLocation{word, char_positions};
      }
    }
  }
  return WordLocation{};
}

WordLocation FindWordLeftDiag(const string& word,
                              const vector<vector<char>>& puzzle) {
  size_t height = puzzle.size();
  size_t width = puzzle.at(0).size();
  for (size_t i = 0; i < height; i++) {
    for (size_t j = width - 1; j != numeric_limits<size_t>::max(); j--) {
      string vec_word;
      vector<CharPositions> char_pos;
      for (size_t k = 0; k < word.size(); k++) {
        size_t row = i + k;
        size_t col = j - k;
        if (!LocationInBounds(row, col, height, width)) {
          break;
        }
        char ch = puzzle.at(row).at(col);
        vec_word.push_back(ch);
        char_pos.push_back(CharPositions{ch, row, col});
        if (vec_word == word) {
          return WordLocation{word, char_pos};
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation FindWordRightDiag(const string& word,
                               const vector<vector<char>>& puzzle) {
  size_t height = puzzle.size();
  size_t width = puzzle.at(0).size();
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      string vec_word;
      vector<CharPositions> char_pos;
      for (size_t k = 0; k < word.size(); k++) {
        if (!LocationInBounds(i + k, j + k, height, width)) {
          break;
        }
        char ch = puzzle.at(i + k).at(j + k);
        vec_word.push_back(ch);
        char_pos.push_back(CharPositions{ch, i + k, j + k});
        if (vec_word == word) {
          return WordLocation{word, char_pos};
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const string& word) {
  WordLocation ho =
      WordSearchSolver::FindWord(word, CheckDirection::kHorizontal);
  WordLocation vt = WordSearchSolver::FindWord(word, CheckDirection::kVertical);
  WordLocation ld = WordSearchSolver::FindWord(word, CheckDirection::kLeftDiag);
  WordLocation rd =
      WordSearchSolver::FindWord(word, CheckDirection::kRightDiag);
  if (!ho.word.empty()) {
    return ho;
  }
  if (!vt.word.empty()) {
    return vt;
  }
  if (!ld.word.empty()) {
    return ld;
  }
  if (!rd.word.empty()) {
    return rd;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const string& word,
                                        CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal) {
    return FindWordHorizontal(word, puzzle_);
  }
  if (direction == CheckDirection::kVertical) {
    return FindWordVertical(word, puzzle_);
  }
  if (direction == CheckDirection::kLeftDiag) {
    return FindWordLeftDiag(word, puzzle_);
  }
  return FindWordRightDiag(word, puzzle_);
}
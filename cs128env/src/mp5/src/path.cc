#include "path.hpp"

#include <iostream>
#include <vector>

using namespace std;

Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  if (length < 0) {
    throw runtime_error("Invalid path length");
  }
  for (size_t i = 0; i < length_; i++) {
    path_.push_back(starting_row);
  }
}

size_t Path::Length() const { return length_; }

size_t Path::StartingRow() const { return starting_row_; }

unsigned int Path::EleChange() const { return ele_change_; }

void Path::IncEleChange(unsigned int value) {
  if (value <= 0) return;
  ele_change_ += value;
}

const vector<size_t>& Path::GetPath() const { return path_; }

// Assigns the value of row (path_.at(col) will evaluate to row)
void Path::SetLoc(size_t col, size_t row) { path_[col] = row; }
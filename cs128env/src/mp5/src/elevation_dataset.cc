#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

vector<int> SplitDatasetLine(string line) {
  vector<int> tokens;
  string token;

  for (size_t i = 0; i < line.size(); i++) {
    char ch = line[i];
    // cout << i << ": " << ch << " - " << token << endl;
    if (ch == ' ') {
      // whitespace ch
      if (!token.empty()) {
        tokens.push_back(stoi(token));  // convert string to int (stoi)
      }
      token = "";
    } else {
      token.push_back(ch);
    }
  }

  if (!token.empty()) tokens.push_back(stoi(token));  // last token

  return tokens;
}

ElevationDataset::ElevationDataset(const string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  // Min/Max elevations changed as lines are processed
  min_ele_ = numeric_limits<int>::max();
  max_ele_ = numeric_limits<int>::min();

  // Process lines
  ifstream data_file(filename);
  if (data_file.fail() || data_file.bad())
    throw runtime_error("Input file read error");

  if (data_file.is_open()) {
    string line;
    size_t row_count = 0;
    while (getline(data_file, line)) {
      if (data_file.fail() || data_file.bad())
        throw runtime_error("Input file read error");

      if (line.empty() || line.size() == 1) continue;
      row_count += 1;
      vector<int> ele_row = SplitDatasetLine(line);
      // if (ele_row.size() != width_)
      //   throw runtime_error("Input width does not match provided width");

      data_.push_back(ele_row);
      for (int ele : ele_row) {
        if (ele < min_ele_)
          min_ele_ = ele;
        else if (ele > max_ele_)
          max_ele_ = ele;
      }
    }
    data_file.close();

    if (row_count != height_)
      throw runtime_error("Input height does not match provided height");
  }
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_[row][col];
}

const vector<vector<int>>& ElevationDataset::GetData() const { return data_; }
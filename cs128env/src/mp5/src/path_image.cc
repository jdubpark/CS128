#include "path_image.hpp"

// #include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "color.hpp"
#include "path.hpp"
// #include "elevation_dataset.hpp"

#define RGB_RED_R 252
#define RGB_RED_G 25
#define RGB_RED_B 63
#define RGB_GREEN_R 31
#define RGB_GREEN_G 253
#define RGB_GREEN_B 13
#define MAX numeric_limits<unsigned int>::max()

using namespace std;

Path FindBestPath(const ElevationDataset& dataset,
                  vector<vector<Color>>& path_image,
                  size_t row_,
                  Path row_path,
                  size_t height,
                  size_t width) {
  size_t row = row_;
  path_image[row][0] = Color(RGB_RED_R, RGB_RED_G, RGB_RED_B);
  for (size_t col = 1; col < width; col++) {
    unsigned int fwd = MAX, top = MAX, bot = MAX;
    int last_col_val = dataset.DatumAt(row, col - 1);
    fwd = abs(dataset.DatumAt(row, col) - last_col_val);
    if (row > 0) {
      bot = abs(dataset.DatumAt(row - 1, col) - last_col_val);
    }
    if (row < height - 1) {
      top = abs(dataset.DatumAt(row + 1, col) - last_col_val);
    }
    if (fwd <= bot && fwd <= top)
      row_path.IncEleChange(fwd);
    else if (top <= bot) {
      row_path.IncEleChange(top);
      row += 1;
    } else {
      row_path.IncEleChange(bot);
      row -= 1;
    }
    row_path.SetLoc(col, row);
    path_image[row][col] = Color(RGB_RED_R, RGB_RED_G, RGB_RED_B);
  }
  return row_path;
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  path_image_ = image.GetImage();
  height_ = dataset.Height();
  width_ = dataset.Width();
  size_t best_path_row = 0;
  unsigned int best_path_ele = MAX;
  for (size_t row = 0; row < height_; row++) {
    Path row_path(width_, row);
    row_path =
        FindBestPath(dataset, path_image_, row, row_path, height_, width_);
    paths_.push_back(row_path);
    if (row_path.EleChange() < best_path_ele) {
      best_path_row = row;
      best_path_ele = row_path.EleChange();
    }
  }
  vector<size_t> best_row = paths_[best_path_row].GetPath();
  for (size_t col = 0; col < width_; col++) {
    size_t row = best_row[col];
    path_image_[row][col] = Color(RGB_GREEN_R, RGB_GREEN_G, RGB_GREEN_B);
  }
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const vector<Path>& PathImage::Paths() const { return paths_; }

const vector<vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const string& name) const {
  ofstream ppm_file;
  ppm_file.open(name);
  ppm_file << "P3\n";                            // magic number
  ppm_file << width_ << " " << height_ << "\n";  // width, empty space, height
  ppm_file << "255\n";                           // RGB 255
  // actual data
  for (size_t i = 0; i < height_; i++) {
    string line;
    for (size_t j = 0; j < width_; j++) {
      Color color = path_image_[i][j];
      line += to_string(color.Red()) + " ";
      line += to_string(color.Green()) + " ";
      line += to_string(color.Blue()) + " ";
    }
    // cout << line << endl;
    ppm_file << line.substr(0, line.size() - 1) << "\n";
  }
  // done
  ppm_file.close();
}
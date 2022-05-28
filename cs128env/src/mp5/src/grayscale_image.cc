#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "color.hpp"
#include "elevation_dataset.hpp"

#define MAX_COLOR_VALUE 255

using namespace std;

int CalculateShadeOfGray(int elevation_point, int min_ele, int max_ele) {
  // cout << elevation_point << ":" << min_ele << ":" << max_ele << endl;
  float num = (float)elevation_point - (float)min_ele;
  float denom = (float)max_ele - (float)min_ele;
  if (max_ele == min_ele) return 0;
  return (int)round(num / denom * (float)MAX_COLOR_VALUE);
}

// Get Color Representations
vector<vector<Color>> GetColorReps(const ElevationDataset& dataset) {
  const vector<vector<int>>& data = dataset.GetData();
  int min_ele = dataset.MinEle();
  int max_ele = dataset.MaxEle();

  vector<vector<Color>> image;
  for (const vector<int>& ele_row : data) {
    vector<Color> colors;
    for (int ele : ele_row) {
      int shade_of_gray = CalculateShadeOfGray(ele, min_ele, max_ele);
      // cout << shade_of_gray << endl;
      Color color = Color(shade_of_gray, shade_of_gray, shade_of_gray);
      colors.push_back(color);
    }
    image.push_back(colors);
  }

  return image;
}

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  height_ = dataset.Height();
  width_ = dataset.Width();
  image_ = GetColorReps(dataset);
}

GrayscaleImage::GrayscaleImage(const string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  ElevationDataset dataset = ElevationDataset(filename, width_, height_);
  image_ = GetColorReps(dataset);
}

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const vector<vector<Color>>& GrayscaleImage::GetImage() const { return image_; }

void GrayscaleImage::ToPpm(const string& name) const {
  ofstream ppm_file;
  ppm_file.open(name);
  ppm_file << "P3\n";                            // magic number
  ppm_file << width_ << " " << height_ << "\n";  // width, empty space, height
  ppm_file << "255\n";                           // RGB 255
  // actual data
  for (size_t i = 0; i < height_; i++) {
    string line;
    for (size_t j = 0; j < width_; j++) {
      Color color = image_[i][j];
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

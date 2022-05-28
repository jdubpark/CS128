#include "image_ppm.hpp"

using namespace std;

// implement the rest of ImagePPM's functions here

// Returns the pixel in the image at (row, col).
// You may assume that row and col will always be within the bounds of the
// image.
Pixel ImagePPM::GetPixel(int row, int col) const { return pixels_[row][col]; }

// Returns the max color value of the image (this is not always 255!)
int ImagePPM::GetMaxColorValue() const { return max_color_value_; }

// // outputs the image in plain PPM format to os
ostream& operator<<(ostream& os, const ImagePPM& image) {
  os << "P3" << std::endl;
  os << image.width_ << " " << image.height_ << std::endl;
  os << image.GetMaxColorValue() << std::endl;
  for (int i = 0; i < image.height_; i++) {
    for (int j = 0; j < image.width_; j++) {
      Pixel px = image.GetPixel(i, j);
      os << px.GetRed() << "\n"
         << px.GetGreen() << "\n"
         << px.GetBlue() << std::endl;
    }
  }
  return os;
}

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}

void ImagePPM::RemoveVerticalSeam(const int* seam) {
  auto* new_pixels = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    int removed = 0;
    new_pixels[row] = new Pixel[width_ - 1];
    for (int col = 0; col < width_; col++) {
      if (col == seam[row]) {  // seam to remove
        removed = 1;
        continue;  // skip adding to new pixels
      }
      new_pixels[row][col - removed] = pixels_[row][col];
    }
  }

  // clear old pixels
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }
  delete[] pixels_;

  // assign new pixels
  pixels_ = new_pixels;
  width_ -= 1;
}

void ImagePPM::RemoveHorizontalSeam(const int* seam) {
  auto* new_pixels = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    new_pixels[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; col++) {
    int removed = 0;
    for (int row = 0; row < height_; row++) {
      if (row == seam[col]) {  // seam to remove
        removed = 1;
        continue;  // skip adding to new pixels
      }
      new_pixels[row - removed][col] = pixels_[row][col];
    }
  }

  // clear old pixels
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }
  delete[] pixels_;

  // assign new pixels
  pixels_ = new_pixels;
  height_ -= 1;
}

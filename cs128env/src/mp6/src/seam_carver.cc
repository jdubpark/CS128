#include "seam_carver.hpp"

#define LARGE_NUM 100000000

int SmallestOfThree(int x, int y, int z) {
  return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

// implement the rest of SeamCarver's functions here

// Returns the instance’s image
const ImagePPM& SeamCarver::GetImage() const { return image_; }

// Returns the height of the instance’s image
int SeamCarver::GetHeight() const { return image_.GetHeight(); }

// Returns the width of the instance’s image
int SeamCarver::GetWidth() const { return image_.GetWidth(); }

// Returns the energy of the pixel at (row, col) of the instance’s image.
// You may assume that row and col will always be within bounds.
int SeamCarver::GetEnergy(int row, int col) const {
  // return energy_[row][col];
  int height = image_.GetHeight(),
      width = image_.GetWidth();               // since image can be carved
  int row_a = row > 0 ? row - 1 : height - 1;  // above, wrap around
  int row_b = row < height - 1 ? row + 1 : 0;  // below, wrap
  int col_l = col > 0 ? col - 1 : width - 1;
  int col_r = col < width - 1 ? col + 1 : 0;
  Pixel px_a = image_.GetPixel(row_a, col), px_b = image_.GetPixel(row_b, col);
  Pixel px_l = image_.GetPixel(row, col_l), px_r = image_.GetPixel(row, col_r);
  int r_col = px_l.GetRed() - px_r.GetRed(),
      r_row = px_a.GetRed() - px_b.GetRed();
  int g_col = px_l.GetGreen() - px_r.GetGreen(),
      g_row = px_a.GetGreen() - px_b.GetGreen();
  int b_col = px_l.GetBlue() - px_r.GetBlue(),
      b_row = px_a.GetBlue() - px_b.GetBlue();
  int d2_col = r_col * r_col + g_col * g_col + b_col * b_col;
  int d2_row = r_row * r_row + g_row * g_row + b_row * b_row;
  return d2_col + d2_row;
}

// Returns the horizontal seam of image_ with the least amount of energy.
// Notice the array returned by this method is on the free store; keep in mind
// when the memory should be free’d.
int* SeamCarver::GetHorizontalSeam() const {
  int row = FindMinPathHorizontal();
  int* seam = new int[image_.GetWidth()];
  seam[0] = row;
  // second col to the second last col, inclusive (sema[col+1])
  for (int col = 0; col < image_.GetWidth() - 1; col++) {
    int row_rt = row > 0 ? GetEnergy(row - 1, col + 1) : LARGE_NUM;
    int row_r = GetEnergy(row, col + 1);
    int row_rb =
        row < image_.GetHeight() - 1 ? GetEnergy(row + 1, col + 1) : LARGE_NUM;
    int row_min_energy = SmallestOfThree(row_rt, row_r, row_rb);
    if (row_min_energy == row_r || row_min_energy == LARGE_NUM) {
      seam[col + 1] = row;
    } else if (row_min_energy == row_rt) {
      seam[col + 1] = row - 1;
      row -= 1;
    } else {
      seam[col + 1] = row + 1;
      row += 1;
    }
  }
  return seam;
}

// Returns the vertical seam of image_ with the least amount of energy.
// Notice the array returned by this method is on the free store; keep in mind
// when the memory should be free’d.
int* SeamCarver::GetVerticalSeam() const {
  int col = FindMinPathVertical();
  int* seam = new int[image_.GetHeight()];
  seam[0] = col;
  // second row to the second last row, inclusive (sema[row+1])
  for (int row = 0; row < image_.GetHeight() - 1; row++) {
    int col_bl = col > 0 ? GetEnergy(row + 1, col - 1) : LARGE_NUM;
    int col_b = GetEnergy(row + 1, col);
    int col_br =
        col < image_.GetWidth() - 1 ? GetEnergy(row + 1, col + 1) : LARGE_NUM;
    int col_min_energy = SmallestOfThree(col_bl, col_b, col_br);
    if (col_min_energy == col_b || col_min_energy == LARGE_NUM) {
      seam[row + 1] = col;
    } else if (col_min_energy == col_bl) {
      seam[row + 1] = col - 1;
      col -= 1;
    } else {
      seam[row + 1] = col + 1;
      col += 1;
    }
  }
  return seam;
}

// Removes one horizontal seam in image_.
// Creating a public member function of the ImagePPM class to carve a seam might
// help.
void SeamCarver::RemoveHorizontalSeam() {
  int* seam = GetHorizontalSeam();
  image_.RemoveHorizontalSeam(seam);
  delete[] seam;
}

void SeamCarver::RemoveVerticalSeam() {
  int* seam = GetVerticalSeam();
  image_.RemoveVerticalSeam(seam);
  delete[] seam;
}

// DP
int SeamCarver::FindMinPathVertical() const {
  int** path = new int*[image_.GetHeight()];
  for (int row = 0; row < image_.GetHeight(); row++) {
    path[row] = new int[image_.GetWidth()];
  }
  // For each cell in the last row, path[row][col] ← E(row, col)
  for (int col = 0; col < image_.GetWidth(); col++) {
    path[image_.GetHeight() - 1][col] = GetEnergy(image_.GetHeight() - 1, col);
  }
  // From second-last row to first row
  for (int row = image_.GetHeight() - 2; row >= 0; row--) {
    for (int col = 0; col < image_.GetWidth(); col++) {
      // Best ← min(Values[/*down-right*/], Values[/*down*/],
      // Values[/*down-left*/])
      int energy_dl = col > 0 ? GetEnergy(row + 1, col - 1) : LARGE_NUM;
      int energy_d = GetEnergy(row + 1, col);
      int energy_dr =
          col < image_.GetWidth() - 1 ? GetEnergy(row + 1, col + 1) : LARGE_NUM;
      int lowest_energy = SmallestOfThree(energy_dl, energy_d, energy_dr);
      path[row][col] = GetEnergy(row, col) + lowest_energy;
    }
  }
  // Return minimum cell of energy_[0]
  int min_idx = 0, min_energy = LARGE_NUM;
  for (int col = 0; col < image_.GetWidth(); col++) {
    if (path[0][col] < min_energy) {
      min_energy = path[0][col];
      min_idx = col;
    }
  }
  // delete path
  for (int i = 0; i < image_.GetHeight(); i++) delete[] path[i];
  delete[] path;
  return min_idx;
}

int SeamCarver::FindMinPathHorizontal() const {
  int** path = new int*[image_.GetHeight()];
  for (int row = 0; row < image_.GetHeight(); row++) {
    path[row] = new int[image_.GetWidth()];
  }
  // For each cell in the last col, path[row][col] ← E(row, col)
  for (int row = 0; row < image_.GetHeight(); row++) {
    path[row][image_.GetWidth() - 1] = GetEnergy(row, image_.GetWidth() - 1);
  }
  // From second-last col to first col
  for (int col = image_.GetWidth() - 2; col >= 0; col--) {
    for (int row = 0; row < image_.GetHeight(); row++) {
      // right top, right, right bottom
      int energy_rt = row > 0 ? GetEnergy(row - 1, col + 1) : LARGE_NUM;
      int energy_r = GetEnergy(row, col + 1);
      int energy_rb = row < image_.GetHeight() - 1 ? GetEnergy(row + 1, col + 1)
                                                   : LARGE_NUM;
      int lowest_energy = SmallestOfThree(energy_rb, energy_r, energy_rt);
      path[row][col] = GetEnergy(row, col) + lowest_energy;
    }
  }
  // Return minimum cell of path[0]
  int min_idx = 0, min_energy = LARGE_NUM;
  for (int row = 0; row < image_.GetHeight(); row++) {
    if (path[row][0] < min_energy) {
      min_energy = path[row][0];
      min_idx = row;
    }
  }
  // delete path
  for (int i = 0; i < image_.GetHeight(); i++) delete[] path[i];
  delete[] path;
  return min_idx;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

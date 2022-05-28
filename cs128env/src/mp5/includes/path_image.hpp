#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  Path best_path_row_ = Path(0, 0);
};

#endif
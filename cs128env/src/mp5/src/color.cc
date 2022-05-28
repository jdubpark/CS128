#include "color.hpp"

#include <iostream>

using namespace std;

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  const int kMaxColorValue = 255;
  if (r < 0 || r > kMaxColorValue || g < 0 || g > kMaxColorValue || b < 0 ||
      b > kMaxColorValue) {
    throw runtime_error("Invalid RGB color");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
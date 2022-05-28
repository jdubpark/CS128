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
#include <string>
#include <fstream>
#include <iostream>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("All tie row1 2w 3h", "[one]") {
//   const string& filepath =
//       "/home/vagrant/src/mp5/example-data/ex_input_data/all-tie-row1-2w-3h.dat";
//   ElevationDataset data = ElevationDataset(filepath, 2, 3);
//   REQUIRE(data.Height() == 3);
//   REQUIRE(data.Width() == 2);
//   REQUIRE(data.DatumAt(0, 0) == 9);
// }

// TEST_CASE("Map input w844 h480", "[four]") {
//   const string& filepath =
//       "/home/vagrant/src/mp5/example-data/ex_input_data/"
//       "map-input-w844-h480.dat";
//   ElevationDataset data = ElevationDataset(filepath, 844, 480);
//   REQUIRE(data.Width() == 844);
//   REQUIRE(data.Height() == 480);
//   REQUIRE(data.DatumAt(0, 0) == 2564);
// }

// TEST_CASE("Prompt 5w 2h", "[5w-2h]") {
//   const string& input_path =
//       "/home/vagrant/src/mp5/example-data/ex_input_data/"
//       "prompt_5w_2h.dat";

//   ElevationDataset data = ElevationDataset(input_path, 5, 2);
//   GrayscaleImage image = GrayscaleImage(data);
//   PathImage path_image = PathImage(image, data);

//   REQUIRE(data.Width() == 5);
//   REQUIRE(data.Height() == 2);
//   REQUIRE(data.DatumAt(0, 0) == 10);

//   REQUIRE(data.Width() == image.Width());
//   REQUIRE(data.Height() == image.Height());

//   REQUIRE(data.MinEle() == 10);
//   REQUIRE(data.MaxEle() == 40);

//   image.ToPpm(
//       "/home/vagrant/src/mp5/example-data/test_output_grayscale/"
//       "prompt_5w_2h.ppm");
//   path_image.ToPpm(
//       "/home/vagrant/src/mp5/example-data/test_output_paths/"
//       "prompt_5w_2h.ppm");
// }

TEST_CASE("Map Input w51 h55", "[w51-h55]") {
  const string& input_path =
      "/home/vagrant/src/mp5/example-data/ex_input_data/"
      "map-input-w51-h55.dat";

  ElevationDataset data = ElevationDataset(input_path, 51, 55);
  GrayscaleImage image = GrayscaleImage(data);
  PathImage path_image = PathImage(image, data);

  REQUIRE(data.Width() == 51);
  REQUIRE(data.Height() == 55);
  REQUIRE(data.DatumAt(0, 0) == -4373);

  REQUIRE(data.Width() == image.Width());
  REQUIRE(data.Height() == image.Height());

  image.ToPpm(
      "/home/vagrant/src/mp5/example-data/test_output_grayscale/"
      "map-input-w51-h55.ppm");
  path_image.ToPpm(
      "/home/vagrant/src/mp5/example-data/test_output_paths/"
      "map-input-w51-h55.ppm");
}

// TEST_CASE("Map input w480 h480", "[w480-h480]") {
//   const string& input_path =
//       "/home/vagrant/src/mp5/example-data/ex_input_data/"
//       "map-input-w480-h480.dat";

//   ElevationDataset data = ElevationDataset(input_path, 480, 480);
//   GrayscaleImage image = GrayscaleImage(data);
//   PathImage path_image = PathImage(image, data);

//   REQUIRE(data.Width() == 480);
//   REQUIRE(data.Height() == 480);
//   REQUIRE(data.DatumAt(0, 0) == 2537);

//   REQUIRE(data.Width() == image.Width());
//   REQUIRE(data.Height() == image.Height());

//   image.ToPpm(
//       "/home/vagrant/src/mp5/example-data/test_output_grayscale/"
//       "map-input-w480-h480.ppm");
//   path_image.ToPpm(
//       "/home/vagrant/src/mp5/example-data/test_output_paths/"
//       "map-input-w480-h480.ppm");
// }

/////////////////////////////////////////////////////////////////////////////////////////////
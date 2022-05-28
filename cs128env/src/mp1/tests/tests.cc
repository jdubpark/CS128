#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <string>

#include "functions.hpp"

// TEST_CASE("A test case", "[case-1]") {
//   bool something = true;
//   REQUIRE(something == true);
// }

TEST_CASE("Hawaiian Words", "[hawaiian_words]") {
  REQUIRE(HawaiianWords("aloha") == "ah-loh-hah");
  REQUIRE(HawaiianWords("Kakahiaka") == "kah-kah-hee-ah-kah");
  REQUIRE(HawaiianWords("MaHALO") == "mah-hah-loh");
  // REQUIRE(HawaiianWords("random") == "random");
  REQUIRE(HawaiianWords("E komo mai") == "eh koh-moh meye");
  REQUIRE(HawaiianWords("maui") == "mow-ee");
  REQUIRE(HawaiianWords("kane") == "kah-neh");
  REQUIRE(HawaiianWords("HOALOHA") == "hoh-ah-loh-hah");
  REQUIRE(HawaiianWords("makua") == "mah-koo-ah");
  REQUIRE(HawaiianWords("keikikane") == "kay-kee-kah-neh");
  REQUIRE(HawaiianWords("humuhumunukunukuapua'a") ==
          "hoo-moo-hoo-moo-noo-koo-noo-koo-ah-poo-ah'ah");
  REQUIRE(HawaiianWords("keiki") == "kay-kee");
  REQUIRE(HawaiianWords("Hoaloha") == "hoh-ah-loh-hah");
  REQUIRE(HawaiianWords("kaiapuni") == "keye-ah-poo-nee");
  REQUIRE(HawaiianWords("wahine") == "wah-hee-neh");
  REQUIRE(HawaiianWords("iwa") == "ee-vah");
  REQUIRE(HawaiianWords("Huaai") == "hoo-ah-eye");
}

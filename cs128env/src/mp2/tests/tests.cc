#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <string>
using namespace std;

#include "functions.hpp"

string file_name =
    "/home/vagrant/src/mp2/tests/ex-str-database-from-prompt.dat";

TEST_CASE("No Match", "[case-1]") {
  string dna_strand =
      "GGTACAGATGGCAAAGATGAGATGAGATGGTCGTCGAGCAATCGTTTCGATAATGAATGAATGAATGAATGA"
      "ATGAATGACACACGTCGATGCTAGCGGCGGATCGTATATTATAACCCCTAG";
  REQUIRE(MatchDNA(file_name, dna_strand) == "No match");
}

TEST_CASE("Match", "[case-2]") {
  string dna_strand =
      "AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGA"
      "GATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA";
  REQUIRE(MatchDNA(file_name, dna_strand) == "Casey");

  dna_strand =
      "TATTATTATTATAACCCTGCGCGCGCGCGATCCAGCATTAGCTAGCATCAAGATGAGATGAGATGGAATTTC"
      "GAAATGAATGAATGAATGAATGAATGAATG";
  REQUIRE(MatchDNA(file_name, dna_strand) == "Amani");

  dna_strand = "AGATGAGATGAGATGAGATGAGATG";
  REQUIRE(MatchDNA(file_name, dna_strand) == "Casey");
}
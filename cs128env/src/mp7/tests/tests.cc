#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <iostream>
#include <string>

#include "dna_strand.hpp"
#include "node.hpp"

std::string GetStrand(DNAstrand* strand) {
  std::string str;
  Node* tmp = strand->Head();
  while (tmp != nullptr) {
    str.push_back(tmp->data);
    tmp = tmp->next;
  }
  return str;
}

// TEST_CASE("Does nothing", "[does-nothing]") { REQUIRE(true == true); }
TEST_CASE("Example 1", "[example-1]") {
  DNAstrand* strand = new DNAstrand();

  std::string get_strand = "";
  const char seq[] = "ctgaattcg";
  const char pat[] = "gaattc";
  const char new_seq[] = "tgatc";
  const char exp[] = "cttgatcg";

  for (int i = 0; i < 9; i++) {
    strand->PushBack(seq[i]);
  }

  get_strand = GetStrand(strand);
  // REQUIRE(get_strand == "ctgaattcg");
  std::cout << "Original: " << get_strand << std::endl;

  Node* match = strand->Match(pat);
  // std::cout << match->data << " " << match->next->data << " " << std::endl;
  // REQUIRE(match->data == "t" && *match->next->data == "g");

  DNAstrand* new_strand = new DNAstrand();
  for (int i = 0; i < 5; i++) {
    new_strand->PushBack(new_seq[i]);
  }
  strand->SpliceIn(pat, *new_strand);

  get_strand = GetStrand(strand);
  std::cout << "To add: " << GetStrand(new_strand) << std::endl;
  std::cout << "To replace: gaattc" << std::endl;
  std::cout << "New strand: " << get_strand << std::endl;
  std::cout << "New head: " << strand->Head()->data << std::endl;
  std::cout << "New tail: " << strand->Tail()->data << std::endl;
  REQUIRE(get_strand == exp);
}

// TEST_CASE("Example 2", "[example-2]") {
//   DNAstrand* strand = new DNAstrand();

//   std::string get_strand = "";
//   const char seq[] = "ctata";
//   const char new_seq[] = "tga";
//   const char pat[] = "ta";

//   for (int i = 0; i < 5; i++) {
//     strand->PushBack(seq[i]);
//   }

//   get_strand = GetStrand(strand);
//   REQUIRE(get_strand == "ctata");
//   std::cout << get_strand << std::endl;

//   // Node* match = strand->Match(pat);
//   // std::cout << match->data << " " << match->next->data << " " <<
//   std::endl;

//   DNAstrand* new_strand = new DNAstrand();
//   for (int i = 0; i < 3; i++) {
//     new_strand->PushBack(new_seq[i]);
//   }
//   strand->SpliceIn(pat, *new_strand);

//   get_strand = GetStrand(strand);
//   std::cout << get_strand << std::endl;
//   std::cout << GetStrand(new_strand) << std::endl;
//   std::cout << strand->Head()->data << std::endl;
//   std::cout << strand->Tail()->data << std::endl;
//   REQUIRE(get_strand == "ctatga");
// }
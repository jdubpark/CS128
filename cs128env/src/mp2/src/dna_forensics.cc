#include <iostream>
#include <string>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }

  std::string file_name = argv[1];
  std::string dna_strand = argv[2];

  std::cout << MatchDNA(file_name, dna_strand) << std::endl;

  return 0;
}
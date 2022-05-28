#include "solution.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_ints_from_file(string file_name) {
  vector<int> ints = {};
  ifstream ifs(file_name);
  
  if (ifs.fail() || !ifs.good()) {
    throw std::runtime_error("Invalid file");
  }
  
  while (ifs.good()) {
    int value = 0;
    ifs >> value;
    if (ifs.bad()) {
    } else if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      ints.push_back(value);
    }
  }
  return ints;
}


#include <iostream>

#include "illini_book.hpp"

void PrintSteps(std::vector<int> steps) {
  if (steps.begin() == steps.end()) {
    std::cout << "empty";
  } else {
    for (auto const& step : steps) {
      std::cout << step << ", ";
    }
  }
  std::cout << std::endl;
}

inline const char* BoolToString(bool b) { return b ? "true" : "false"; }

int main() {
  IlliniBook graph("./example/persons.csv", "./example/relations.csv");

  std::cout << "==== AreRelated ====" << std::endl;
  // std::cout << BoolToString(graph.AreRelated(0, 1)) << " == false" <<
  // std::endl;
  std::cout << BoolToString(graph.AreRelated(1, 2)) << " == true" << std::endl;
  std::cout << BoolToString(graph.AreRelated(3, 2)) << " == true" << std::endl;
  std::cout << BoolToString(graph.AreRelated(1, 9)) << " == false" << std::endl;
  std::cout << BoolToString(graph.AreRelated(1, 2, "128")) << " == true"
            << std::endl;
  std::cout << BoolToString(graph.AreRelated(1, 2, "124")) << " == false"
            << std::endl;
  std::cout << BoolToString(graph.AreRelated(1, 6, "128")) << " == true"
            << std::endl;
  std::cout << BoolToString(graph.AreRelated(1, 6, "124")) << " == true"
            << std::endl;

  std::cout << "==== GetRelated ====" << std::endl;
  std::cout << graph.GetRelated(1, 2) << " == 1" << std::endl;
  std::cout << graph.GetRelated(3, 2) << " == 2" << std::endl;
  std::cout << graph.GetRelated(1, 9) << " == -1" << std::endl;
  std::cout << graph.GetRelated(1, 2, "128") << " == 1" << std::endl;
  std::cout << graph.GetRelated(1, 2, "124") << " == -1" << std::endl;
  std::cout << graph.GetRelated(1, 6, "128") << " == 2" << std::endl;
  std::cout << graph.GetRelated(1, 6, "124") << " == 1" << std::endl;

  std::cout << "==== GetSteps ====" << std::endl;
  PrintSteps(graph.GetSteps(1, 1));
  PrintSteps(graph.GetSteps(1, 2));
  PrintSteps(graph.GetSteps(1, 3));
  PrintSteps(graph.GetSteps(9, 1));

  std::cout << "==== CountGroups ====" << std::endl;
  std::cout << graph.CountGroups() << " == 3" << std::endl;
  std::cout << graph.CountGroups("128") << " == 6" << std::endl;
  std::cout << graph.CountGroups("124") << " == 6" << std::endl;
  std::cout << graph.CountGroups("173") << " == 10" << std::endl;
  std::cout << graph.CountGroups(std::vector<std::string>{"128", "173"})
            << " == 6" << std::endl;
  std::cout << graph.CountGroups(std::vector<std::string>{"128", "124", "173"})
            << " == 3" << std::endl;

  return 0;
}

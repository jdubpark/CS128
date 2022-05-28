#include "solution.hpp"  // NOLINT

#include <iostream>
#include <queue>

Solution::Solution(
    const std::vector<std::pair<std::string, std::string>>& prerequisites) {
  std::map<std::string, std::vector<std::string>> map;
  for (auto& course_orders : prerequisites) {
    if (adj_.count(course_orders.first) > 0) {
      std::string prereq = course_orders.first;
      std::string course = course_orders.second;
      adj_.at(prereq).push_back(course);
    } else {
      std::vector<std::string> temp = {course_orders.second};
      std::string prereq = course_orders.first;
      std::vector<std::string> > vec = (prereq, temp);
      std::list<int> dest(vec.begin(), vec.end());
      adj_.insert(dest);
    }
  }
}

int Solution::Solve(const std::string& start, const std::string& dest) {
  std::queue<std::pair<std::string, int>> queue;
  if (adj_.count(start) == 0) {
    return -1;
  }
  queue.push({start, 0});
  while (queue.size() != 0) {
    std::string f = queue.front().first;
    int counter = queue.front().second;
    queue.pop();
    if (f == dest) return counter;
    std::list<std::string> adj = adj_[f];
    for (auto i : adj) {
      queue.push({i, counter + 1});
    }
  }
  return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Provide function definitions (uncomment to use!)                          //
///////////////////////////////////////////////////////////////////////////////

void Solution::AddVertex(const std::string& vertex) {
  if (VertexInGraph(vertex))
    throw std::runtime_error("vertex already in graph.");
  adj_.insert(std::pair(vertex, std::list<std::string>()));
}

std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
  return adj_.find(vertex)->second;
}

bool Solution::VertexInGraph(const std::string& vertex) {
  return adj_.find(vertex) != adj_.end();
}

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  os << "Contents:" << std::endl;
  for (const auto& pair : sol.adj_) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }
  return os;
}

#include "illini_book.hpp"

#include "utilities.hpp"

std::vector<std::vector<std::string>> ReadFile(const std::string& file_path) {
  std::vector<std::vector<std::string>> lines;
  std::ifstream file(file_path);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      // using printf() in all tests for consistency
      lines.push_back(utilities::Split(line.c_str(), ','));
      line.clear();
    }
    file.close();
  }
  return lines;
}

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::vector<std::vector<std::string>> uins_vec = ReadFile(people_fpath);
  std::vector<std::vector<std::string>> relations = ReadFile(relations_fpath);

  for (std::vector<std::string> uin_wrap : uins_vec) {
    graph_[std::stoi(uin_wrap.at(0))] = std::map<int, std::string>();
  }

  for (std::vector<std::string> relation : relations) {
    int from = std::stoi(relation.at(0));
    int to = std::stoi(relation.at(1));
    std::string re = relation.at(2);
    graph_[from][to] = re;
    graph_[to][from] = re;
  }
}

IlliniBook::IlliniBook(const IlliniBook& rhs) { graph_ = rhs.graph_; }

IlliniBook& IlliniBook::operator=(const IlliniBook& rhs) {
  if (&rhs == this) {
    return *this;
  }
  graph_ = rhs.graph_;
  return *this;
}

bool DoesKeyExist(std::map<int, int> map, int key) {
  return map.find(key) != map.end();
}

std::map<int, int> IlliniBook::Dijkstra(
    int src, const std::set<std::string>& relations) const {
  std::queue<int> queue;
  std::map<int, int> dist;
  dist[src] = 0;
  queue.push(src);
  while (!queue.empty()) {
    int node = queue.front();
    queue.pop();
    for (auto const& neighbor : graph_.at(node)) {
      int dest = neighbor.first;
      if (dist.find(dest) == dist.end()) {
        if (!relations.empty() &&
            relations.find(graph_.at(node).at(dest)) == relations.end()) {
          continue;
        }
        dist[dest] = dist.at(node) + 1;
        queue.push(dest);
      }
    }
  }
  return dist;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::map<int, int> dist = Dijkstra(uin_1, std::set<std::string>{});
  return DoesKeyExist(dist, uin_2);
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  std::map<int, int> dist =
      Dijkstra(uin_1, std::set<std::string>{relationship});
  return DoesKeyExist(dist, uin_2);
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::map<int, int> dist = Dijkstra(uin_1, std::set<std::string>{});
  return DoesKeyExist(dist, uin_2) ? dist.at(uin_2) : -1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::map<int, int> dist =
      Dijkstra(uin_1, std::set<std::string>{relationship});
  return DoesKeyExist(dist, uin_2) ? dist.at(uin_2) : -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> steps;
  std::map<int, int> dist = Dijkstra(uin, std::set<std::string>{});
  for (auto const& node : dist) {
    if (node.second == n) {
      steps.push_back(node.first);
    }
  }
  return steps;
}

size_t IlliniBook::CountGroups() const {
  std::list<int> nodes;
  for (auto const& node : graph_) {
    nodes.push_back(node.first);
  }
  size_t components = 0;
  while (!nodes.empty()) {
    std::set<int> visited;
    std::queue<int> queue;
    int node = nodes.front();
    queue.push(node);
    while (!queue.empty()) {
      int dest = queue.front();
      visited.insert(node);
      queue.pop();
      nodes.remove(dest);
      if (graph_.count(dest) == 1) {
        for (auto const& neighbor : graph_.at(dest)) {
          if (visited.count(neighbor.first) != 1) {
            queue.push(neighbor.first);
            visited.insert(neighbor.first);
          }
        }
      }
    }
    nodes.remove(node);
    components += 1;
  }
  return components;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::list<int> nodes;
  for (auto const& node : graph_) {
    nodes.push_back(node.first);
  }
  size_t components = 0;
  while (!nodes.empty()) {
    std::set<int> visited;
    std::queue<int> queue;
    int node = nodes.front();
    queue.push(node);
    while (!queue.empty()) {
      int dest = queue.front();
      visited.insert(node);
      queue.pop();
      nodes.remove(dest);
      if (graph_.count(dest) == 1) {
        for (auto const& neighbor : graph_.at(dest)) {
          if (visited.count(neighbor.first) != 1 &&
              graph_.at(dest).count(neighbor.first) != 0 &&
              graph_.at(dest).at(neighbor.first) == relationship) {
            queue.push(neighbor.first);
            visited.insert(neighbor.first);
          }
        }
      }
    }
    nodes.remove(node);
    components += 1;
  }
  return components;
}

bool ExistsInVector(const std::string& node,
                    const std::vector<std::string>& vec) {
  bool result = false;
  for (auto const& x : vec) {
    if (x == node) {
      result = true;
      break;
    }
  }
  return result;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  std::list<int> nodes;
  for (auto const& node : graph_) {
    nodes.push_back(node.first);
  }
  size_t components = 0;
  while (!nodes.empty()) {
    std::set<int> visited;
    std::queue<int> queue;
    int node = nodes.front();
    queue.push(node);
    while (!queue.empty()) {
      int dest = queue.front();
      visited.insert(node);
      queue.pop();
      nodes.remove(dest);
      if (graph_.count(dest) == 1) {
        for (auto const& neighbor : graph_.at(dest)) {
          if (visited.count(neighbor.first) != 1 &&
              graph_.at(dest).count(neighbor.first) != 0 &&
              ExistsInVector(graph_.at(dest).at(neighbor.first),
                             relationships)) {
            queue.push(neighbor.first);
            visited.insert(neighbor.first);
          }
        }
      }
    }
    nodes.remove(node);
    components += 1;
  }
  return components;
}
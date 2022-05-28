#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "utilities.hpp"
using namespace std;

vector<string> ReadFile(const string& file_name) {
  vector<string> lines;
  ifstream ifs{file_name};
  for (string line; getline(ifs, line); line = "") {
    lines.push_back(line);
  }
  return lines;
}

// Finds the number of the longest repeating (search) string in full string
int FindLongestRepeating(const string& search_str, const string& full_str) {
  int longest = 0;
  int best_len = 0;
  int search_len = search_str.length();

  for (unsigned i = 0; i < full_str.length(); i += 1) {
    string sub = full_str.substr(i, search_len);
    if (search_str == sub) {
      i += search_len - 1;
      best_len++;
      if (best_len > longest) longest = best_len;
    } else {
      best_len = 0;
    }
  }
  return longest;
}

string FindBestCandidate(const map<string, map<string, int>>& candidates,
                         map<string, int> str_longest) {
  map<string, map<string, int>>::const_iterator it;
  map<string, int> people;
  for (it = candidates.begin(); it != candidates.end(); it++) {
    string person_name = it->first;
    map<string, int> person_str = it->second;
    map<string, int>::const_iterator it2;
    for (it2 = person_str.begin(); it2 != person_str.end(); it2++) {
      string str_name = it2->first;
      int str_value = it2->second;
      if (str_longest[str_name] == str_value) {
        people[person_name] += 1;
      }
    }
  }

  map<string, int>::const_iterator it2;
  for (it2 = people.begin(); it2 != people.end(); it2++) {
    if (it2->second == static_cast<int>(str_longest.size())) {
      return it2->first;
    }
  }
  return "No match";
}

string MatchDNA(const string& file_name, const string& dna_strand) {
  vector<string> lines = ReadFile(file_name);
  vector<string> str;  // STR
  map<string, map<string, int>> candidates;

  for (const string& line : lines) {
    vector<string> substrs = utilities::GetSubstrs(line, ',');
    vector<string> slice_first =
        vector<string>(substrs.begin() + 1, substrs.end());  // [1:]
    if (substrs.at(0) == "Names" || substrs.at(0) == "name") {
      str = slice_first;  // set STR
    } else {
      string person = substrs.at(0);
      for (int i = 0, len = slice_first.size(); i < len; i++) {
        candidates[person][str.at(i)] = stoi(slice_first.at(i));
      }
    }
  }

  map<string, int> str_longest;
  for (const string& str_value : str) {
    str_longest[str_value] = FindLongestRepeating(str_value, dna_strand);
  }

  return FindBestCandidate(candidates, str_longest);
}
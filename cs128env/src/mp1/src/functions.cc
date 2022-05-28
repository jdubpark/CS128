#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Your function definitions should go in this source file.

void AddAndSkip(std::string& phonetics,
                const std::string& kStr,
                char& chn,
                int& idx,
                int& len) {
  phonetics += kStr;
  idx += 1;
  if (chn != ' ' && chn != '\'' && idx != len - 1) phonetics += "-";
}

bool IsCharVowel(char ch) {
  return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

std::vector<std::string> SplitString(std::string str) {
  std::string delimiter = " ";
  size_t idx = 0;
  std::string token;
  std::vector<std::string> tokens;

  // Loop through the words, parse each word by delimiter, deleting along the
  // way
  while ((idx = str.find(delimiter)) != std::string::npos) {
    token = str.substr(0, idx);
    str.erase(0, idx + delimiter.length());
  }

  // final token
  tokens.push_back(str);

  return tokens;
}

void EmitNotPart(const std::string& word) {
  std::cout << word
            << " contains a character not a part of the Hawaiian language."
            << std::endl;
}

bool IsIllegalChar(char& ch) {
  return !IsCharVowel(ch) && ch != 'p' && ch != 'k' && ch != 'h' && ch != 'l' &&
         ch != 'm' && ch != 'n' && ch != 'w' && ch != '\'' && ch != ' ';
}

void CheckVowels(
    std::string& phonetics, char& ch, char& chn, int& i, int& len) {
  if (ch == 'a') {
    if (chn == 'i' || chn == 'e')
      return AddAndSkip(phonetics, "eye", chn, i, len);
    if (chn == 'o' || chn == 'u')
      return AddAndSkip(phonetics, "ow", chn, i, len);
    phonetics += "ah";
  }

  else if (ch == 'e') {
    if (chn == 'i') return AddAndSkip(phonetics, "ay", chn, i, len);
    if (chn == 'u') return AddAndSkip(phonetics, "eh-oo", chn, i, len);
    phonetics += "eh";
  }

  else if (ch == 'i') {
    if (chn == 'u') return AddAndSkip(phonetics, "ew", chn, i, len);
    phonetics += "ee";
  }

  else if (ch == 'o') {
    if (chn == 'i') return AddAndSkip(phonetics, "oy", chn, i, len);
    if (chn == 'u') return AddAndSkip(phonetics, "ow", chn, i, len);
    phonetics += "oh";
  }

  else if (ch == 'u') {
    if (chn == 'i') return AddAndSkip(phonetics, "ooey", chn, i, len);
    phonetics += "oo";
  }

  // All vowels (one or two length) end with "-"
  if (chn != ' ' && chn != '\'' && i != len - 1) phonetics += "-";
}

std::string HawaiianWords(std::string str) {
  std::string phonetics;

  std::vector<std::string> words = SplitString(str);

  for (std::string word : words) {
    for (int i = 0, len = word.size(); i < len; i++) {
      char ch = std::tolower(word[i]);
      if (IsIllegalChar(ch)) {
        EmitNotPart(word);
        break;
      }
    }
  }

  for (int i = 0, len = str.size(); i < len; i++) {
    char ch = std::tolower(str[i]);
    char chp = std::tolower(str[i - 1]);
    char chn = std::tolower(str[i + 1]);
    if (ch == ' ')
      phonetics += " ";
    else if (IsCharVowel(ch))
      CheckVowels(phonetics, ch, chn, i, len);
    else if (ch == 'w')
      phonetics += chp == 'i' || chp == 'e' ? "v" : "w";
    else
      phonetics.push_back(ch);
  }

  return phonetics;
}
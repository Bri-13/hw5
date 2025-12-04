#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool inDictionary(const string& word, const set<string>& dict);
void makeWords(string newWord, string& floating, size_t index, size_t n, const set<string>& dict, set<string>& words);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  // Add your code here
  set<string> potentialWords;
  size_t n = in.size();
  string newWord = in;
  string floatingChars = floating;

  makeWords(newWord, floatingChars, 0, n, dict, potentialWords);
  
  return potentialWords;
}

// Define any helper functions here
bool inDictionary(const string& word, const set<string>& dict){
  return dict.find(word) != dict.end();
}

void makeWords(string newWord, string& floating, size_t index, size_t n, const set<string>& dict, set<string>& words){
  // base case
  if(index == n){
    // reached valid size so now check before adding
    if((floating.size() == 0) && inDictionary(newWord, dict)){
      words.insert(newWord);
    }
    return;
  }
  

  if(newWord[index] != '-'){
    // if char at index is not -, then move to next index
    makeWords(newWord, floating, index + 1, n, dict, words);
  }
  else{
    // fill in letters a-z at that index to try all combos/options
    for(char letter = 'a'; letter < 'z'+1; letter++){
      bool floatFlag = false;
      size_t prevIndex=0;
      for(size_t i=0; i<floating.size(); i++){
        if(floating[i] == letter){
          floatFlag = true;
          prevIndex = i;
          floating.erase(floating.begin() + i);
          break;
        }
      }

      newWord[index] = letter;
      makeWords(newWord, floating, index + 1, n, dict, words);
      // might need to undo and try next option
      if(floatFlag){
        floating.insert(floating.begin() + prevIndex, letter);
      }
    }
  }
}
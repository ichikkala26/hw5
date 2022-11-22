// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void guessFinder(std::string in, const std::string floating, const std::set<std::string>& dict,
std::set<std::string>& possibleGuesses, unsigned int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    //create set for possible guesses
    std::set<std::string> possibleGuesses;
    //create index to iterate through the in
    unsigned int index=0;
    //recursive call
    guessFinder(in, floating, dict, possibleGuesses, index);
    //return possible guesses
    return possibleGuesses;
}

// Define any helper functions here

void guessFinder(std::string in, const std::string floating, const std::set<std::string>& dict,
std::set<std::string>& possibleGuesses, unsigned int index)
{
  if(index==in.size())
  {
    if(dict.find(in)!=dict.end())
    {
      //cout<< in <<endl;
      possibleGuesses.insert(in);
    }
    return;
  }
  else if(in[index]!='-')
  {
    guessFinder(in, floating, dict, possibleGuesses, index+1);
  }
  else
  {
    std::set<char> addedFloats;
    std::string alphabet = "qwertyuiopasdfghjklzxcvbnm";
    for(unsigned int i=0; i<floating.size();i++)
    {
      addedFloats.insert(floating[i]);
      in[index] = floating[i];
      std::string newFloating = floating.substr(0,i) + floating.substr(i+1, floating.size());
    //char toRemove = floating[i];
    //std::string newFloating = floating.erase(remove(floating.begin(), floating.end(), toRemove), floating.end())
      guessFinder(in, newFloating, dict, possibleGuesses, index+1);
      in[index] = '-';
    }

    bool noRoom = true;
    unsigned int numOfSpaces = 0;
    for(unsigned int j=0; j<in.size(); j++)
    {
      if(in[j]=='-')
      {
        numOfSpaces++;
      }
    }

    if(numOfSpaces!=floating.size())
    {
      noRoom = false;
    }

    if(!noRoom)
    {
      for(unsigned int k=0; k<alphabet.size(); k++)
      {
        if(addedFloats.find(alphabet[k])==addedFloats.end())
        {
          in[index]= alphabet[k];
          guessFinder(in, floating, dict, possibleGuesses, index+1);
          in[index] = '-';
        }
      }
    }
  }
}




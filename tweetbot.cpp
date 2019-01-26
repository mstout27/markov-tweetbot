//File containing several methods to aid in making a markov chain from text

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>

using namespace std;

vector<string> readFile(string name){
    vector<string> allWords;
    string word;
    ifstream file;

    file.open(name.c_str());

    while (file >> word){
        allWords.push_back(word);
    }
    return allWords;
}

map<string, vector<string> > makeDict(vector<string> allWords){
  
  map<string, vector<string> > markovChain;
  
  
  for(vector<string>::const_iterator myit = allWords.begin(); myit != allWords.end()-1; ++myit){
    vector<string>::const_iterator nextVal = myit;
    nextVal++;
    markovChain[*myit].push_back(*nextVal);
  }
  
  return markovChain;
}



int main(int argc, char* argv[]){
    string filename = argv[1];
    vector<string> wordList = readFile(filename);

    map<string, vector<string> > markovDict = makeDict(wordList);

    
   /* 
    for(map<string, vector<string> >::const_iterator it = markovDict.begin(); it != markovDict.end(); ++it){
      cout << "[ " << it->first << " ] [ ";
      for(vector<string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
        cout << *it2 << " ";
      }
      cout << "]" << endl;
    }
    */
    
    
    //--making final output string
    
    map<string, vector<string> >::const_iterator iter = markovDict.begin();
    srand(time(0));
    int start = rand() % markovDict.size();
    advance(iter, start); 
    
    string currWord = iter->first; 
    
    
    //capital letters
    /* 
    
    for(iter; iter != markovDict.end(); iter++){
      if(!(isupper(currWord[0]))){
        currWord = iter->first; 
        if(iter == markovDict.end()){
          iter = markovDict.begin();
        }
      }
      else{
        currWord = iter->first; 
        break;
      }
    }
    */
    
    
    
    int charCount = 280;
    
    do{  
      cout << currWord << " ";
      charCount -= currWord.length() + 1;
      
      /*
      if(currWord.substr(currWord.length()-1,1) == "." || "?" || "!"){ //new sentence
        start = rand() % markovDict.size();
        advance(iter, start); 
    
  
        currWord = iter->first; 
    
        for(iter; iter != markovDict.end(); iter++){
          if(!(isupper(currWord[0]))){
            iter++;
            if(iter == markovDict.end()){
              iter = markovDict.begin();
            }
          }
          else{
            break;
          }
        }
        
      } //end new sentence
      */
      
      //currWord = iter->first; 
      
      
      int secondRand = rand() % (iter->second).size(); 
      currWord = iter->second[secondRand];
      
      int advanceAmt = 0;
      for(map<string, vector<string> >::const_iterator currIter = markovDict.begin(); currIter->first != currWord; ++currIter){
        advanceAmt++;
      }
      
      iter = markovDict.begin();
      advance(iter,advanceAmt);  //iterate iter so iter->first becomes word from previous iter->second
      
      
      
    } while(charCount > 0);  
    
    
    cout << endl;

    return 0;
}

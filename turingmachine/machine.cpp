#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "machine.h"
using namespace std;

bool is_json_valid(Json::Value & j){
  // finals should be on states
  // initial should be on states
  // the keys should be the same
  // the blank should not be on symbols

  Json::Value set_finals = j["finals"];
  Json::Value states = j["states"];
  string initial_str = j["initial"].asString();
  string keys[] = {"states", "initial", "symbols", "finals", "blank", "start",
                   "transitions"};

  // finals
  Json::ValueIterator start = set_finals.begin();
  Json::ValueIterator end = set_finals.end();
  Json::Value aux;
  for(; start != end; ++start){
    aux = *start;
    if(! in_value(states, aux.asString())){
      cout << "Error in json file; final state "
           << aux.asString() << " should be on states" << endl;

      exit(EXIT_FAILURE);
    }

  }

  // initial
  if(! in_value(states, initial_str)){
    cout << "Error in json file; initial state "
         << initial_str << " should be on states" << endl;

    exit(EXIT_FAILURE);
  }

  // check the keys
  for(string e: keys){
    aux = j[e];
    if(aux.isNull()){
      cout << "Error in json file; " << e << " should be a key on json file"
           << endl;
      exit(EXIT_FAILURE);
    }
  }

  // check blank symbol
  string blank = j["blank"].asString();
  if(in_value(j["symbols"], blank)){
    cout << "Error in json file; blank symbol " << blank << " should not be on"
         << " symbols" << endl;
    exit(EXIT_FAILURE);
  }

  return true;
}


Json::Value get_json_content(const string local){
  ifstream file_json(local, ifstream::binary);
  Json::Value js;

  if(file_json.is_open()){
      file_json >> js;
      file_json.close();
      is_json_valid(js);
      return js;
  }
  cout << "File not foud at " << local << endl;
  exit(EXIT_FAILURE);
}

bool in_value(Json::Value & e, string target){
  Json::ValueIterator where = find(e.begin(), e.end(), target);
  return where != e.end();
}

string extract_word(string & target, char blank){
  int local = target.find_first_of(blank) - 1;
  return target.substr(1, local);
}


#include <iostream>
#include <string>


#include "json/json.h"
#include "machine.h"

// JSON structure


// TODO
// compile it with make g++
// present the final word without blank and start
// make automated test
// documentate JSON structure
// integrate this project with python
//   http://stackoverflow.com/questions/1153577/integrate-python-and-c
using namespace std;

const string LOCAL = "/home/alex/Documentos/cod/my/cpp-qt/qt-teste/struct.json";
const string RIGHT = "R";
const string LEFT  = "L";



void maquina(string word_user){
  cout << "comecou a trabalhar mas parou" << endl;
  string word;
  int index = 1;
  Json::Value structure  = get_json_content(LOCAL);
  string blank_str = structure["blank"].asString();
  string start = structure["initial"].asString();
  Json::Value transitions = structure["transitions"];
  Json::Value current_state = transitions[start];
  string str_current = start;
  Json::Value tmp_state;
  // construct; use start and blank from json file
  word = structure["start"].asString() + word_user + blank_str;
  string aux;

  // word[index] shoud be a key of current state
  // if true will give [next_state, to_write, direction]
  try {
    while(true){
      tmp_state = current_state[word.substr(index, 1)];
      if(!tmp_state.isNull()){
        str_current = tmp_state[0].asString();
        current_state = transitions[str_current];
        aux = tmp_state[1].asString();

        // if word[index] is blank add other blank
        if(word[index] == blank_str.at(0)){
          word += blank_str;
        }
        word[index] = aux.at(0);

        if(tmp_state[2].asString() == RIGHT){
          ++index;
        } else {
          --index;
        }

      // no state to go
      } else {
        if(in_value(structure["finals"], str_current)){
          cout << "True; " << word << endl;
        } else {
          cout << "False; " << word << endl;
        }
        break;
      }
    }

  } catch(Json::LogicError e){
      cout << "False;; " << word << endl;
  }

}



int main(){

  maquina("0001");
  return 0;
}

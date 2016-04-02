#include <iostream>
#include <string>
#include <cstdlib>

#include "json/json.h"
#include "machine.h"


// TODO
// make validations on json
// alex@pc:~/Documentos/cod/my/cpp-qt/turingmachine$ # finals shold be in states
// alex@pc:~/Documentos/cod/my/cpp-qt/turingmachine$ # initial shold be in states
// alex@pc:~/Documentos/cod/my/cpp-qt/turingmachine$
// integrate this project with python
//   http://stackoverflow.com/questions/1153577/integrate-python-and-c
using namespace std;


const string RIGHT = "R";
const string LEFT  = "L";



string machine(string word_user, const string json_path){

  int index = 1;
  Json::Value structure = get_json_content(json_path);
  string blank_str = structure["blank"].asString();
  char blank_chr = blank_str.at(0);
  string start = structure["initial"].asString();
  Json::Value transitions = structure["transitions"];
  Json::Value current_state = transitions[start];
  string str_current = start;
  Json::Value tmp_state;
  // construct; use start and blank from json file
  string word = structure["start"].asString() + word_user + blank_str;
  string aux;
  string output;
  string aux_direction;

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
        if(word[index] == blank_chr){
          word += blank_str;
        }
        word[index] = aux.at(0);

        aux_direction = tmp_state[2].asString();
        if(aux_direction == RIGHT){
          ++index;
        } else if(aux_direction == LEFT){
          --index;
        } else {
          cout << "Invalid direction: " << aux_direction << endl;
          exit(EXIT_FAILURE);
        }

      // no state to go
      } else {
        if(in_value(structure["finals"], str_current)){
          output = "True:";
        } else {
          output = "False:";
        }
        output += extract_word(word, blank_chr);
        break;
      }
    }

  } catch(Json::LogicError e){
    output = "False:" + extract_word(word, blank_chr);
  }

  return output;

}



int main(int argc, char * argv[]){
  if(argc != 3){
      cout << "Failed; should pass <word2test> <path_json>" << endl;
      exit(EXIT_FAILURE);
  }
  string word(argv[1]);
  string file_local(argv[2]);
  string e = machine(word, file_local);
  cout << e << endl;
  return 0;
}

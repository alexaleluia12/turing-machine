#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "machine.h"
using namespace std;

Json::Value get_json_content(const string local){
  ifstream file_json(local, ifstream::binary);
  Json::Value js;

  if(file_json.is_open()){
      file_json >> js;
      file_json.close();
      return js;
  }
  cout << "File not foud at " << local << endl;
  exit(EXIT_FAILURE);


}

bool in_value(Json::Value & e, string target){
  Json::ValueIterator where = find(e.begin(), e.end(), target);
  return where != e.end();
}

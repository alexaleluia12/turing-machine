#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include "json/json.h"

using namespace std;

Json::Value get_json_content(const string local);
bool in_value(Json::Value & e, string target);
#endif // MACHINE_H


//
// Created by James on 08/12/2017.
//

#ifndef ASSIGNMENT_GAMEOBJECT_H
#define ASSIGNMENT_GAMEOBJECT_H

#include <string>
#include <forward_list>
#include <list>

using std::string;

class GameObject {
public:
    const string *oName;
    const string *oDescription;
    const string *oKeyword;
    string oLocation;

    GameObject(const string *oN, const string *oD, const string *oK);

    const string *getName() const;

    const string *getDesc() const;

    const string *getKey() const;

    string getLocation();

    void setLocation(string location);
};


#endif //ASSIGNMENT_GAMEOBJECT_H

//
// Created by James on 08/12/2017.
//

#include <iostream>
#include "GameObject.h"

GameObject::GameObject(const string *oN, const string *oD, const string *oK) :
        oName(oN), oDescription(oD), oKeyword(oK) {
};

const string *GameObject::getName() const {
    return this->oName;
}

const string *GameObject::getDesc() const {
    return this->oDescription;
}

const string *GameObject::getKey() const {
    return this->oKeyword;
}

string GameObject::getLocation() {
    return this->oLocation;
}

void GameObject::setLocation(string location) {
    this->oLocation = location;
}




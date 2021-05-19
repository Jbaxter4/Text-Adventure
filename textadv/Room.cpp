//
// Created by DrMark on 10/2/2017.
//

#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include <iostream>


std::list<Room *> Room::rooms;
std::list<GameObject *> Room::allObjects;


Room::Room(const string *_name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), east(nullptr), south(nullptr), west(nullptr) {
};

Room::~Room() {
    Room::rooms.remove(this);
}

void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    if (!objects.empty()) {
        std::cout << "The room contains: " << std::endl;
        for (auto object : objects) {
            std::cout << *object->getName() << std::endl;
        }
    }
}

Room *Room::addRoom(const string *_name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

Room *Room::addRoom(Room *room) {
    Room::rooms.push_back(room);
}

Room *Room::getNorth() const {
    return this->north;
}

void Room::setNorth(Room *_north) {
    this->north = _north;
}

Room *Room::getEast() const {
    return this->east;
}

void Room::setEast(Room *_east) {
    this->east = _east;
}

Room *Room::getSouth() const {
    return this->south;
}

void Room::setSouth(Room *_south) {
    this->south = _south;
}

Room *Room::getWest() const {
    return this->west;
}

void Room::setWest(Room *_west) {
    this->west = _west;
}

const string *Room::getName() const {
    return this->name;
}

Room *Room::findRoom(string name) {
    for (auto room : rooms) {
        if (name == *room->getName()) {
            return room;
        }
    }
}

void Room::addObject(GameObject *object) {
    objects.push_back(object);
    allObjects.push_back(object);
}

void Room::getObject(GameObject *object) {
    objects.push_back(object);
}

void Room::setLocations() {
    string location;
    for (auto room : rooms) {
        if (!room->objects.empty()) {
            location = *room->getName();
            for (auto object : room->objects) {
                object->setLocation(location);
                const string oName = *object->getName();
                for (auto obj : allObjects) {
                    if (*obj->getName() == oName) {
                        obj->setLocation(location);
                    }
                }
            }
        }
    }
    if (!State::inventory.empty()) {
        for (auto object : State::inventory) {
            object->setLocation("Inventory");
        }
    }
}

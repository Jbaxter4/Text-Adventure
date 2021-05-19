//
// Created by DrMark on 10/2/2017.
//


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"

using std::string;

class Room {
    const string *name;
    const string *description;
    Room *north;
    Room *east;
    Room *south;
    Room *west;
public:
    static std::list<Room *> rooms;
    static std::list<GameObject *> allObjects;
    std::list<GameObject *> objects;

    Room(const string *_name, const string *_desc);

    ~Room();

    virtual void describe() const;

    static Room *addRoom(const string *_name, const string *_desc);

    static Room *addRoom(Room *room);

    Room *getNorth() const;

    void setNorth(Room *_north);

    Room *getEast() const;

    void setEast(Room *_east);

    Room *getSouth() const;

    void setSouth(Room *_south);

    Room *getWest() const;

    void setWest(Room *_west);

    const string *getName() const;

    void addObject(GameObject *object);

    void setLocations();

    void getObject(GameObject *object);

    Room *findRoom(string name);
};

#endif //TEXTADV_ROOM_H

//
// Created by DrMark on 10/2/2017.
//

#include <iostream>
#include "State.h"

/**
 * Current state of the game.
 */

std::list<GameObject *> State::inventory;

void State::announceInv() const {
    if (!inventory.empty()) {
        std::cout << "Item's in inventory: " << std::endl;
        for (auto object : inventory) {
            std::cout << *object->getName() << std::endl;
        }
    } else {
        std::cout << "Your inventory is empty." << std::endl;
    }
}

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room *State::getCurrentRoom() {
    return this->currentRoom;
}

/*const string State::getName() {
    return *getCurrentRoom()->getName();
}*/

void State::getObject(GameObject *object) {
    inventory.push_back(object);
}





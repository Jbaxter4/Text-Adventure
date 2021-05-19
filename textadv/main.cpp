
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <sstream>
#include <fstream>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

void initRooms() {
    auto *r1 = new Room(&r1name, &r1desc);
    auto *r2 = new Room(&r2name, &r2desc);
    auto *r3 = new Room(&r3name, &r3desc);
    auto *r4 = new Room(&r4name, &r4desc);
    auto *r5 = new Room(&r5name, &r5desc);
    auto *o1 = new GameObject(&o1oName, &o1oDesc, &o1oKey);
    auto *o2 = new GameObject(&o2oName, &o2oDesc, &o2oKey);
    auto *o3 = new GameObject(&o3oName, &o3oDesc, &o3oKey);

    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    r2->addObject(o1);
    r3->addObject(o2);
    r5->addObject(o3);

    r1->setNorth(r2);
    r2->setSouth(r1);
    r1->setEast(r3);
    r3->setWest(r1);
    r2->setWest(r4);
    r4->setEast(r2);
    r1->setWest(r5);
    r5->setEast(r1);
    r5->setNorth(r4);
    r4->setSouth(r5);
}

void initState() {
    currentState = new State(Room::rooms.front());
    currentState->getCurrentRoom()->setLocations();
}

void gameLoop() {
    bool gameOver = false;
    while (!gameOver) {
        bool firstCommandOk = false;
        inputCommand(&commandBuffer);

        std::string endOfVerb;
        std::string secondWord;
        std::stringstream stream(commandBuffer);
        stream >> endOfVerb;
        stream >> secondWord;

        if ((endOfVerb == "north") || (endOfVerb == "n")) {
            firstCommandOk = true;
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(northRoom);
            }
        } else if ((endOfVerb == "east") || (endOfVerb == "e")) {
            firstCommandOk = true;
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(eastRoom);
            }
        } else if ((endOfVerb == "south") || (endOfVerb == "s")) {
            firstCommandOk = true;
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(southRoom);
            }
        } else if ((endOfVerb == "west") || (endOfVerb == "w")) {
            firstCommandOk = true;
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(westRoom);
            }
        } else if (endOfVerb == "stay") {
            firstCommandOk = true;
            currentState->announceLoc();
        } else if (endOfVerb == "inventory") {
            firstCommandOk = true;
            currentState->announceInv();
        } else if (endOfVerb == "get") {
            firstCommandOk = true;
            uint8_t check = 0;
            if (!currentState->getCurrentRoom()->objects.empty()) {
                for (auto object : currentState->getCurrentRoom()->objects) {
                    if (secondWord == *object->getKey()) {
                        currentState->getObject(object);
                        currentState->getCurrentRoom()->objects.remove(object);
                        std::cout << *object->getName() + " was added to the inventory." << std::endl;
                        object->oLocation = "Inventory";
                        check++;
                        break;
                    }
                }
                if (check == 0) {
                    std::cout << "That item is not in this room to get." << std::endl;
                }
            } else {
                std::cout << "There is no object in this room to get!" << std::endl;
            }
            currentState->getCurrentRoom()->setLocations();
        } else if (endOfVerb == "drop") {
            firstCommandOk = true;
            uint8_t check = 0;
            if (!currentState->inventory.empty()) {
                for (auto object : currentState->inventory) {
                    if (secondWord == *object->getKey()) {
                        currentState->getCurrentRoom()->getObject(object);
                        currentState->inventory.remove(object);
                        std::cout << *object->getName() + " was dropped." << std::endl;
                        check++;
                        break;
                    }
                }
                if (check == 0) {
                    std::cout << "That item is not in your inventory to drop." << std::endl;
                }
            } else {
                std::cout << "Your inventory is empty, you can't drop anything!" << std::endl;
            }
            currentState->getCurrentRoom()->setLocations();
        } else if (endOfVerb == "examine") {
            firstCommandOk = true;
            uint8_t check = 0;
            if ((currentState->inventory.empty()) && (currentState->getCurrentRoom()->objects.empty())) {
                std::cout << "There is nothing to examine." << std::endl;
            } else {
                for (auto object : currentState->inventory) {
                    if (secondWord == *object->getKey()) {
                        std::cout << *object->getDesc() << std::endl;
                        check++;
                        break;
                    }
                }
                for (auto object : currentState->getCurrentRoom()->objects) {
                    if (secondWord == *object->getKey()) {
                        std::cout << *object->getDesc() << std::endl;
                        check++;
                        break;
                    }
                }
                if (check == 0) {
                    std::cout << "That object is not in your inventory or nearby to be examined." << std::endl;
                }
            }
        } else if ((endOfVerb == "quit") || (endOfVerb == "q")) {
            firstCommandOk = true;
            gameOver = true;
        } else if (endOfVerb == "save") {
            firstCommandOk = true;
            std::ofstream file("GameFile.txt");
            file << *currentState->getCurrentRoom()->getName() << "\n";
            for (auto object : currentState->getCurrentRoom()->allObjects) {
                file << object->oLocation << "\n" << *object->getName() << "\n";
            }
            file.close();
            gameOver = true;
        } else if (endOfVerb == "load") {
            firstCommandOk = true;
            string line;
            std::ifstream file("GameFile.txt");
            if (file.is_open()) {
                for (auto room : currentState->getCurrentRoom()->rooms) {
                    room->objects.clear();
                }
                (getline(file, line));
                for (auto room : currentState->getCurrentRoom()->rooms) {
                    if (*room->getName() == line) {
                        currentState->goTo(room);
                    }
                }
                while (getline(file, line)) {
                    string locationLine = line;
                    (getline(file, line));
                    string itemLine = line;
                    for (auto object : currentState->getCurrentRoom()->allObjects) {
                        if (itemLine == (*object->getName())) {
                            if (locationLine != "Inventory") {
                                Room *box = currentState->getCurrentRoom()->findRoom(locationLine);
                                box->getObject(object);
                            } else if (locationLine == "Inventory") {
                                currentState->getObject(object);
                            }
                        }
                    }
                }
                file.close();
            }
            currentState->getCurrentRoom()->setLocations();

        }

        if (!firstCommandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}


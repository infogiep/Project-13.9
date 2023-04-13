#include "netW.h"

#include <memory>
#include <iostream>

Network::Man::Man() : id(-1) {
}
Network::Man::Man(const Name _name, int _id) : id(_id) {
    strcpy_s(name, _name);
}
Network::Man& Network::Man::operator=(const Man& other) {
    strcpy_s(name, other.name);
    id = other.id;
    return *this;
}
Network::Man::Man(const Man& other)
{
    strcpy_s(name, other.name);
    id = other.id;
}
bool Network::Man::operator==(const Man& other) {
    return other.id == this->id;
}
Network::Network() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            friend_matrix[i][j] = 0;
    for (int i = 0; i < SIZE; i++) {
        busyids.add(false);
    }
}
void Network::addMan(const Name name) {
    Man man = findManByName(name);
    if (man.id >= 0)
        return;
    int i = 0;
    for (; i < SIZE; i++)
        if (!busyids[i])
            break;
    busyids[i] = true;
    people.add(Man(name, i));
}

void Network::delMan(const Name name) {
    Man man = findManByName(name);
    if (man.id < 0)
        return;
    busyids[man.id] = false;
    int index = people.find(man);
    for (int i = 0; i < people.size(); i++) {
        friend_matrix[i][man.id] = 0;
        friend_matrix[man.id][i] = 0;
    }
    people.del(index);
}

void Network::addRel(const Name name_1, const Name name_2) {
    Man m1 = findManByName(name_1);
    Man m2 = findManByName(name_2);
    if (m1.id < 0 || m2.id < 0)
        return;
    friend_matrix[m1.id][m2.id] = 1;
    friend_matrix[m2.id][m1.id] = 1;
}

void Network::ThreeHands() {
    int wavesLevels[SIZE];
    for (int i = 0; i < SIZE; i++) {
        wavesLevels[i] = -1;
    }
    wavesLevels[0] = 0;

    StaticArray<int> queue;
    queue.add(0);

    while (queue.size()) {
        int currentManIndex = queue[0];
        queue.del(0);
        for (int i = 0; i < people.size(); i++)
            if (are_friends(people[currentManIndex], people[i]) &&
                wavesLevels[i] == -1)
            {
                wavesLevels[i] = wavesLevels[currentManIndex] + 1;
                queue.add(i);
            }
    }

    for (int i = 0; i < people.size(); i++) {
        for (int j = i + 1; j < people.size(); j++) {
            if (abs(wavesLevels[i] - wavesLevels[j]) <= 3) {
                std::cout << people[i].name << " " << people[j].name << std::endl;
            }
        }
    }
}


bool Network::are_friends(const Man& m1, const Man& m2) {
    return friend_matrix[m1.id][m2.id] == 1;
}

bool Network::man_exists_with_id(int man_id) {
    for (int i = 0; i < people.size(); i++)
        if (people[i].id == man_id)
            return true;
    return false;
}

Network::Man Network::findManByName(const Name name) {
    for (int i = 0; i < people.size(); i++)
        if (!strcmp(name, people[i].name))
            return people[i];
    return Man();
}
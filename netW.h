#pragma once

#include "net.h"
#define NAMELENGTH 30
typedef char Name[NAMELENGTH];

class Network 
{
public:
    struct Man 
    {
        Man();
        Man(const Name _name, int _id);
        Man& operator=(const Man& other);
        Man(const Man& other);
        bool operator==(const Man& other);
        Name name;
        friend class Network;
    private:
        int id;

    };

    Network();
    void addMan(const Name name);
    void delMan(const Name name);
    void addRel(const Name name_1, const Name name_2);
    void ThreeHands();

private:
    bool are_friends(const Man& m1, const Man& m2);
    bool man_exists_with_id(int man_id);
    Man findManByName(const Name name);
private:
    int friend_matrix[SIZE][SIZE];
    StaticArray<Man> people;
    StaticArray<bool> busyids;
};

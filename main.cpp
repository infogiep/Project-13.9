#include <iostream>
#include "netW.h"

int main(char* arr[], int count)
{
    Network razg;

    razg.addMan("Alex");
    razg.addMan("Vasya");
    razg.addMan("Natasha");
    razg.addMan("Maria");
    razg.addMan("Sergey");

    razg.delMan("Maria");
    razg.addMan("Larisa");

    razg.addRel("Alex", "Vasya");
    razg.addRel("Vasya", "Natasha");
    razg.addRel("Natasha", "Larisa");
    razg.addRel("Larisa", "Sergey");

    razg.ThreeHands();

    return 0;
}
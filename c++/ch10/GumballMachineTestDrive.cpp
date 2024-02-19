#include "GumballMachine.h"

int main(int argc, char **argv)
{
    GumballMachine *gumballMachine = new GumballMachine(5);

    std::cout << *gumballMachine;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    std::cout << *gumballMachine;

    gumballMachine->insertQuarter();
    gumballMachine->ejectQuarter();
    gumballMachine->turnCrank();

    std::cout << *gumballMachine;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->ejectQuarter();

    std::cout << *gumballMachine;

    gumballMachine->insertQuarter();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    std::cout << *gumballMachine;

    gumballMachine->refill(5);

    std::cout << *gumballMachine;

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    std::cout << *gumballMachine;

    return 0;
}
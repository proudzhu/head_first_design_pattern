#ifndef SOLD_OUT_STATE_H
#define SOLD_OUT_STATE_H

#include <iostream>
#include "State.h"
#include "GumballMachine.h"

class SoldOutState:
    public State
{
    public:
        SoldOutState(GumballMachine *machine):
            machine_(machine) { }

        void insertQuarter(void)
        {
            std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
        }

        void ejectQuarter(void)
        {
            std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
        }

        void turnCrank(void)
        {
            std::cout << "You turned, but there are no gumballs" << std::endl;
        }

        void dispense(void)
        {
            std::cout << "No gumball dispensed" << std::endl;
        }

        void refill(void)
        {
            machine_->setState(machine_->getNoQuarterState());
        }

    protected:
        void toString(std::ostream &os) const
        {
            os << "sold out";
        }

    private:
        GumballMachine *machine_;
};

#endif

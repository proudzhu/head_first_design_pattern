#ifndef NO_QUARTER_STATE_H
#define NO_QUARTER_STATE_H

#include <iostream>
#include "State.h"
#include "GumballMachine.h"

class NoQuarterState:
    public State
{
    public:
        NoQuarterState(GumballMachine *machine):
            machine_(machine) { }

        void insertQuarter(void)
        {
            machine_->setState(machine_->getHasQuarterState());
            std::cout << "You inserted a quarter" << std::endl;
        }

        void ejectQuarter(void)
        {
            std::cout << "You haven't inserted a quarter" << std::endl;
        }

        void turnCrank(void)
        {
            std::cout << "You turned, but there's no quarter" << std::endl;
        }

        void dispense(void)
        {
            std::cout << "You need to pay first" << std::endl;
        }

        void refill(void) { }

    protected:
        void toString(std::ostream &os) const
        {
            os << "waiting for quarter";
        }

    private:
        GumballMachine *machine_;
};

#endif

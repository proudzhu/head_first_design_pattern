#ifndef HAS_QUARTER_STATE_H
#define HAS_QUARTER_STATE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "State.h"
#include "GumballMachine.h"

class HasQuarterState:
    public State
{
    public:
        HasQuarterState(GumballMachine *machine) :
            machine_(machine)
        {
            std::srand(std::time(nullptr));
        }

        void insertQuarter(void)
        {
            std::cout << "You can't insert another quarter" << std::endl;
        }

        void ejectQuarter(void)
        {
            std::cout << "Quarter returned" << std::endl;
            machine_->setState(machine_->getNoQuarterState());
        }

        void turnCrank(void)
        {
            std::cout << "You turned..." << std::endl;
            int winner = std::rand() % 10;
            if (winner == 0 && machine_->getCount() > 1) {
                machine_->setState(machine_->getWinnerState());
            } else {
                machine_->setState(machine_->getSoldState());
            }
        }

        void dispense(void)
        {
            std::cout << "No gumball dispensed" << std::endl;
        }

        void refill(void) { }

    protected:
        void toString(std::ostream &os) const
        {
            os << "waiting for turn of crank";
        }

    private:
        GumballMachine *machine_;
};

#endif

#ifndef WINNER_STATE_H
#define WINNER_STATE_H

#include <iostream>
#include "State.h"
#include "GumballMachine.h"

class WinnerState:
    public State
{
    public:
        WinnerState(GumballMachine *machine):
            machine_(machine) { }

        void insertQuarter(void)
        {
            std::cout << "Please wait, we're already giving you a gumball" << std::endl;
        }

        void ejectQuarter(void)
        {
            std::cout << "Sorry, you already turned the crank" << std::endl;
        }

        void turnCrank(void)
        {
            std::cout << "Turing twice doesn't get you another gumball" << std::endl;
        }

        void dispense(void)
        {
            std::cout << "YOU'RE A WINNER! You get two gumballs for your quarter" << std::endl;
            machine_->releaseBall();
            if (machine_->getCount() == 0) {
                machine_->setState(machine_->getSoldOutState());
            } else {
                machine_->releaseBall();
                if (machine_->getCount() > 0) {
                    machine_->setState(machine_->getNoQuarterState());
                } else {
                    std::cout << "Oops, out of gumballs!" << std::endl;
                    machine_->setState(machine_->getSoldOutState());
                }
            }
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

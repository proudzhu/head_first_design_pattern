#ifndef GUMBALL_MACHINE_H
#define GUMBALL_MACHINE_H

#include <iostream>
#include <cstdint>
#include "State.h"

class GumballMachine
{
    friend std::ostream& operator<<(std::ostream &, const GumballMachine &);
    public:
        GumballMachine(int numberGumballs);

        void insertQuarter(void);
        void ejectQuarter(void);
        void turnCrank(void);
        void refill(int numberGumballs);
        State *getState(void) const;
        void setState(State *state);
        void releaseBall(void);
        State *getSoldOutState(void);
        State *getNoQuarterState(void);
        State *getHasQuarterState(void);
        State *getSoldState(void);
        State *getWinnerState(void);
        int32_t getCount(void) const;

    private:
        State *soldOutState_;
        State *noQuarterState_;
        State *hasQuarterState_;
        State *soldState_;
        State *winnerState_;

        State *state_;
        int32_t count_;
};

#endif

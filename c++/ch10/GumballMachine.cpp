
#include "GumballMachine.h"
#include "SoldOutState.h"
#include "NoQuarterState.h"
#include "HasQuarterState.h"
#include "SoldState.h"
#include "WinnerState.h"

GumballMachine::GumballMachine(int numberGumballs) : count_(numberGumballs)
{
    soldOutState_ = new SoldOutState(this);
    noQuarterState_ = new NoQuarterState(this);
    hasQuarterState_ = new HasQuarterState(this);
    soldState_ = new SoldState(this);
    winnerState_ = new WinnerState(this);
    state_ = numberGumballs > 0 ? noQuarterState_ : soldOutState_;
}

void GumballMachine::insertQuarter(void)
{
    state_->insertQuarter();
}

void GumballMachine::ejectQuarter(void)
{
    state_->ejectQuarter();
}

void GumballMachine::turnCrank(void)
{
    state_->turnCrank();
    state_->dispense();
}

void GumballMachine::refill(int numberGumballs)
{
    count_ += numberGumballs;
    std::cout << "The gumball machine was just refilled; its new count is: " << count_ << std::endl;
    state_->refill();
}

State* GumballMachine::getState(void) const
{
    return state_;
}

void GumballMachine::setState(State *state)
{
    state_ = state;
}

void GumballMachine::releaseBall(void)
{
    std::cout << "A gumball comes rolling out the solt..." << std::endl;
    if (count_ != 0) {
        count_ -= 1;
    }
}

State *GumballMachine::getSoldOutState(void)
{
    return soldOutState_;
}

State *GumballMachine::getNoQuarterState(void)
{
    return noQuarterState_;
}

State *GumballMachine::getHasQuarterState(void)
{
    return hasQuarterState_;
}

State *GumballMachine::getSoldState(void)
{
    return soldState_;
}

State *GumballMachine::getWinnerState(void)
{
    return winnerState_;
}

int32_t GumballMachine::getCount(void) const
{
    return count_;
}

std::ostream&
operator<<(std::ostream &os, const GumballMachine &gbm)
{
	os << "\nMighty Gumball, Inc.";
	os << "\nC++ enabled Standing Gumball Model #2004";
	os << "\nInventory: " << gbm.getCount() << " gumball";
	if (gbm.getCount() != 1)
		os << "s";
	os << "\n";
	os << "Machine is " << *gbm.getState() << "\n\n";
	return os;
}
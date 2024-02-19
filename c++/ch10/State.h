#ifndef STATE_H
#define STATE_H

class State
{
    friend std::ostream& operator<<(std::ostream&, const State &);
    public:
        virtual void insertQuarter(void) = 0;
        virtual void ejectQuarter(void) = 0;
        virtual void turnCrank(void) = 0;
        virtual void dispense(void) = 0;
        virtual void refill(void) = 0;
    protected:
        virtual void toString(std::ostream &) const = 0;
};

inline
std::ostream& operator<<(std::ostream& os, const State &state)
{
	state.toString(os);
	return os;
}

#endif

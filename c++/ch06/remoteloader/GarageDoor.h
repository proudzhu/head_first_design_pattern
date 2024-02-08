#ifndef GARAGE_DOOR_H
#define GARAGE_DOOR_H

#include <string>

class GarageDoor
{
    public:
        GarageDoor(const std::string &l) : location(l) { }

        void up(void)
        {
            std::cout << location << " GarageDoor up" << std::endl;
        }

        void down(void)
        {
            std::cout << location << " GarageDoor down" << std::endl;
        }

        void stop(void)
        {
            std::cout << location << " GarageDoor stop" << std::endl;
        }

        void lightOn(void)
        {
            std::cout << location << " GarageDoor lightOn" << std::endl;
        }

        void lightOff(void)
        {
            std::cout << location << " GarageDoor lightOff" << std::endl;
        }

    private:
        std::string location;
};

class GarageDoorUpCommand :
    public Command
{
    public:
        GarageDoorUpCommand(GarageDoor* garage_door):
            garage_door_(garage_door), Command("GarageDoorUpCommand")
        { }

        void execute(void) override
        {
            garage_door_->up();
        }

        void undo(void) override
        {
            garage_door_->down();
        }

    protected:
        GarageDoor* garage_door_;
};

class GarageDoorDownCommand :
    public Command
{
    public:
        GarageDoorDownCommand(GarageDoor* garage_door):
            garage_door_(garage_door), Command("GarageDoorDownCommand")
        { }

        void execute(void) override
        {
            garage_door_->down();
        }

        void undo(void) override
        {
            garage_door_->up();
        }

    protected:
        GarageDoor* garage_door_;
};

#endif

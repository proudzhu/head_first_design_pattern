#ifndef GARAGE_DOOR_H
#define GARAGE_DOOR_H

class GarageDoor
{
    public:
        void up(void)
        {
            std::cout << "GarageDoor up" << std::endl;
        }

        void down(void)
        {
            std::cout << "GarageDoor down" << std::endl;
        }

        void stop(void)
        {
            std::cout << "GarageDoor stop" << std::endl;
        }

        void lightOn(void)
        {
            std::cout << "GarageDoor lightOn" << std::endl;
        }

        void lightOff(void)
        {
            std::cout << "GarageDoor lightOff" << std::endl;
        }
};

class GarageDoorOpenCommand :
    public Command
{
    public:
        GarageDoorOpenCommand(GarageDoor* garage_door) {
            garage_door_ = garage_door;
        }

        void execute(void) const override
        {
            garage_door_->up();
        }

    protected:
        GarageDoor* garage_door_;
};

#endif

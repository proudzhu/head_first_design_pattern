#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include "Command.h"

class Light
{
    public:
        void on(void)
        {
            std::cout << "Light on" << std::endl;
        }

        void off(void)
        {
            std::cout << "Light off" << std::endl;
        }
};

class LightOnCommand :
    public Command
{
    public:
        LightOnCommand(Light* light) : light_(light) { }

        void execute() const override
        {
            light_->on();
        }

    protected:
        Light* light_;
};

#endif

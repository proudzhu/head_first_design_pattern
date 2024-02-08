#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <string>
#include "Command.h"

class Light
{
    public:
        Light(const std::string &l) : location(l) { }

        void on(void)
        {
            std::cout << location << " Light on" << std::endl;
        }

        void off(void)
        {
            std::cout << location << " Light off" << std::endl;
        }

    private:
        std::string location;
};

class LightOnCommand :
    public Command
{
    public:
        LightOnCommand(Light *light):
            light_(light), Command("LightOnCommand")
        { }

        void execute(void) override
        {
            light_->on();
        }

        void undo(void) override
        {
            light_->off();
        }

    private:
        Light *light_;
};

class LightOffCommand :
    public Command
{
    public:
        LightOffCommand(Light *light):
            light_(light), Command("LightOffCommand")
        { }

        void execute(void) override
        {
            light_->off();
        }

        void undo(void) override
        {
            light_->on();
        }

    private:
        Light *light_;
};

#endif

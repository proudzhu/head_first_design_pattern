#ifndef SIMPLE_REMOTE_CONTROL_H
#define SIMPLE_REMOTE_CONTROL_H

#include <memory>
#include "Command.h"

class SimpleRemoteControl
{
    public:
        SimpleRemoteControl(void) { }

        void setCommand(Command* command)
        {
            slot_ = command;
        }

        void buttonWasPressed(void)
        {
            slot_->execute();
        }

    protected:
        Command* slot_;
};

#endif

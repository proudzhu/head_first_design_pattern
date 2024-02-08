#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <array>
#include <iostream>
#include <cstdint>
#include "Command.h"

#define MAX_COMMAND_NUM (7)

class RemoteControl
{
    public:
        RemoteControl(void)
        {
            Command *noCommand = new NoCommand();
            for (auto i = 0; i < MAX_COMMAND_NUM; i++) {
                onCommands_[i] = noCommand;
                offCommands_[i] = noCommand;
            }
            undoCommand_ = noCommand;
        }

        void setCommand(uint32_t slot, Command *onCommand, Command *offCommand)
        {
            onCommands_[slot] = onCommand;
            offCommands_[slot] = offCommand;
        }

        void onButtonWasPushed(uint32_t slot)
        {
            onCommands_[slot]->execute();
            undoCommand_ = onCommands_[slot];
        }

        void offButtonWasPushed(uint32_t slot)
        {
            offCommands_[slot]->execute();
            undoCommand_ = offCommands_[slot];
        }

        void undoButtonWasPushed(void)
        {
            undoCommand_->undo();
        }

        friend std::ostream& operator<< (std::ostream& stream, const RemoteControl &control);

    private:
        std::array<Command*, MAX_COMMAND_NUM> onCommands_;
        std::array<Command*, MAX_COMMAND_NUM> offCommands_;
        Command *undoCommand_;
};

std::ostream &operator<< (std::ostream &os, const RemoteControl &control)
{
    os << "\n------ Remote Control ------\n";
    for (uint32_t i = 0; i < MAX_COMMAND_NUM; i++) {
       os << "[slot " << i << "] " << control.onCommands_[i]->getCommandName() << " " << control.offCommands_[i]->getCommandName() << "\n";
    }

    return os;
}

#endif

#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H

#include <vector>
#include <ranges>
#include "Command.h"

class MacroCommand :
    public Command
{
    public:
        MacroCommand(std::vector<Command *> &commands):
            commands_(commands), Command("MacroCommand")
        {}

        void execute(void) override
        {
            for (auto cmd : commands_) {
                cmd->execute();
            }
        }

        void undo(void) override
        {
            for (auto cmd : std::ranges::views::reverse(commands_)) {
                cmd->undo();
            }
        }

    private:
        std::vector<Command *> &commands_;
};

#endif

#ifndef COMMAND_H
#define COMMAND_H

class Command
{
    public:
        virtual ~Command() = default;
        virtual void execute() const = 0;
};

class NoCommand :
    public Command
{
    public:
        void execute(void) { }
};

#endif

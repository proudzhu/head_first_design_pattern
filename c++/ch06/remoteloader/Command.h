#ifndef COMMAND_H
#define COMMAND_H

class Command
{
    public:
        Command(std::string name): name_(name) { }
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;
        std::string getCommandName() { return name_; };
    protected:
        std::string name_;
};

class NoCommand :
    public Command
{
    public:
        NoCommand(void) : Command("NoCommand") { }

        void execute(void) override { }
        void undo(void) override { }
};

#endif

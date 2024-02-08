#ifndef CEILING_FAN_H
#define CEILING_FAN_H

#include <string>

typedef enum
{
    CEILING_FAN_SPEED_OFF = 0,
    CEILING_FAN_SPEED_LOW,
    CEILING_FAN_SPEED_MEDIUM,
    CEILING_FAN_SPEED_HIGH,
} CEILING_FAN_SPEED;

class CeilingFan
{
    public:
        CeilingFan(const std::string &l) : location(l) { }

        void high(void)
        {
            speed_ = CEILING_FAN_SPEED_HIGH;
            std::cout << location << " CeilingFan high" << std::endl;
        }

        void medium(void)
        {
            speed_ = CEILING_FAN_SPEED_MEDIUM;
            std::cout << location << " CeilingFan medium" << std::endl;
        }

        void low(void)
        {
            speed_ = CEILING_FAN_SPEED_LOW;
            std::cout << location << " CeilingFan low" << std::endl;
        }

        void off(void)
        {
            speed_ = CEILING_FAN_SPEED_OFF;
            std::cout << location << " CeilingFan off" << std::endl;
        }

        CEILING_FAN_SPEED getSpeed(void)
        {
            return speed_;
        }

        void setSpeed(CEILING_FAN_SPEED speed)
        {
            switch (speed) {
                case CEILING_FAN_SPEED_OFF:
                    off();
                    break;
                case CEILING_FAN_SPEED_LOW:
                    low();
                    break;
                case CEILING_FAN_SPEED_MEDIUM:
                    medium();
                    break;
                case CEILING_FAN_SPEED_HIGH:
                    high();
                    break;
                default:
                    std::cout << "Invalid pre speed " << speed << std::endl;
            }
        }

    private:
        std::string location;
        CEILING_FAN_SPEED speed_;
};

class CeilingFanHighCommand :
    public Command
{
    public:
        CeilingFanHighCommand(CeilingFan *fan):
            fan_(fan), Command("CeilingFanHighCommand")
        { }

        void execute(void) override
        {
            prev_speed_ = fan_->getSpeed();
            fan_->high();
        }

        void undo(void) override
        {
            fan_->setSpeed(prev_speed_);
        }

    private:
        CeilingFan *fan_;
        CEILING_FAN_SPEED prev_speed_;
};

class CeilingFanMediumCommand :
    public Command
{
    public:
        CeilingFanMediumCommand(CeilingFan *fan):
            fan_(fan), Command("CeilingFanMediumCommand")
        { }

        void execute(void) override
        {
            prev_speed_ = fan_->getSpeed();
            fan_->medium();
        }

        void undo(void) override
        {
            fan_->setSpeed(prev_speed_);
        }

    private:
        CeilingFan *fan_;
        CEILING_FAN_SPEED prev_speed_;
};

class CeilingFanLowCommand :
    public Command
{
    public:
        CeilingFanLowCommand(CeilingFan *fan):
            fan_(fan), Command("CeilingFanLowCommand")
        { }

        void execute(void) override
        {
            prev_speed_ = fan_->getSpeed();
            fan_->low();
        }

        void undo(void) override
        {
            fan_->setSpeed(prev_speed_);
        }

    private:
        CeilingFan *fan_;
        CEILING_FAN_SPEED prev_speed_;
};

class CeilingFanOffCommand :
    public Command
{
    public:
        CeilingFanOffCommand(CeilingFan *fan):
            fan_(fan), Command("CeilingFanOffCommand")
        { }

        void execute(void) override
        {
            prev_speed_ = fan_->getSpeed();
            fan_->off();
        }

        void undo(void) override
        {
            fan_->setSpeed(prev_speed_);
        }

    private:
        CeilingFan *fan_;
        CEILING_FAN_SPEED prev_speed_;
};

#endif

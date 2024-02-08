#ifndef STEREO_H
#define STEREO_H

#include <string>

class Stereo
{
    public:
        Stereo(const std::string &l) : location(l) { }

        void on(void)
        {
            std::cout << location << " Stereo on" << std::endl;
        }
        
        void off(void)
        {
            std::cout << location << " Stereo off" << std::endl;
        }

        void setCD(void)
        {
            std::cout << location << " Stereo set CD" << std::endl;
        }

        void setDVD(void)
        {
            std::cout << location << " Stereo set DVD" << std::endl;
        }

        void setRadio(void)
        {
            std::cout << location << " Stereo set Radio" << std::endl;
        }

        void setVolume(uint32_t vol)
        {
            vol_ = vol;
            std::cout << location << " Stereo set Volume " << vol_ << std::endl;
        }

    private:
        std::string location;
        uint32_t vol_;
};

class StereoOnWithCDCommand :
    public Command
{
    public:
        StereoOnWithCDCommand(Stereo *stereo):
            stereo_(stereo), Command("StereoOnWithCDCommand")
        { }

        void execute(void) override
        {
            stereo_->on();
            stereo_->setCD();
            stereo_->setVolume(11);
        }

        void undo(void) override
        {
            stereo_->off();
        }

    private:
        Stereo *stereo_;
};

class StereoOffCommand :
    public Command
{
    public:
        StereoOffCommand(Stereo *stereo):
            stereo_(stereo), Command("StereoOffCommand")
        { }

        void execute(void) override
        {
            stereo_->off();
        }

        void undo(void) override
        {
            stereo_->on();
        }

    private:
        Stereo *stereo_;
};

#endif

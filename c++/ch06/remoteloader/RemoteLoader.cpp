#include "RemoteControl.h"
#include "Light.h"
#include "CeilingFan.h"
#include "GarageDoor.h"
#include "Stereo.h"
#include "MacroCommand.h"

int main(int argc, char **argv)
{
    auto remoteControl = new RemoteControl;

    auto livingRoomLight = new Light("Living Room");
    auto kitchenLight = new Light("Kitchen");
    auto ceilingFan = new CeilingFan("Living Room");
    auto garageDoor = new GarageDoor("");
    auto stereo = new Stereo("Living Room");

    auto livingRoomLightOn = new LightOnCommand(livingRoomLight);
    auto livingRoomLightOff = new LightOffCommand(livingRoomLight);
    auto kitchenLightOn = new LightOnCommand(kitchenLight);
    auto kitchenLightOff = new LightOffCommand(kitchenLight);

    auto ceilingFanHigh = new CeilingFanHighCommand(ceilingFan);
    auto ceilingFanMedium = new CeilingFanMediumCommand(ceilingFan);
    auto ceilingFanLow = new CeilingFanLowCommand(ceilingFan);
    auto ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

    auto garageDoorUp = new GarageDoorUpCommand(garageDoor);
    auto garageDoorDown = new GarageDoorDownCommand(garageDoor);

    auto stereoOnWithCD = new StereoOnWithCDCommand(stereo);
    auto stereoOff = new StereoOffCommand(stereo);

    remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl->setCommand(2, ceilingFanHigh, ceilingFanOff);
    remoteControl->setCommand(3, stereoOnWithCD, stereoOff);

    std::cout << *remoteControl << "\n";

    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    remoteControl->onButtonWasPushed(1);
    remoteControl->offButtonWasPushed(1);
    remoteControl->onButtonWasPushed(2);
    remoteControl->offButtonWasPushed(2);
    remoteControl->onButtonWasPushed(3);
    remoteControl->offButtonWasPushed(3);

    // undo
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    std::cout << *remoteControl << "\n";
    remoteControl->undoButtonWasPushed();

    remoteControl->offButtonWasPushed(0);
    remoteControl->onButtonWasPushed(0);
    std::cout << *remoteControl << "\n";
    remoteControl->undoButtonWasPushed();

    // fan undo
    remoteControl->setCommand(0, ceilingFanMedium, ceilingFanOff);
    remoteControl->setCommand(1, ceilingFanHigh, ceilingFanOff);

    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    std::cout << *remoteControl << "\n";
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPushed(1);
    std::cout << *remoteControl << "\n";
    remoteControl->undoButtonWasPushed();

    // macro command
    std::vector<Command *> partyOn = {livingRoomLightOn, stereoOnWithCD};
    std::vector<Command *> partyOff = {livingRoomLightOff, stereoOff};

    auto partyOnMacro = new MacroCommand(partyOn);
    auto partyOffMacro = new MacroCommand(partyOff);

    remoteControl->setCommand(0, partyOnMacro, partyOffMacro);

    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    std::cout << *remoteControl << "\n";
    remoteControl->undoButtonWasPushed();

    return 0;
}
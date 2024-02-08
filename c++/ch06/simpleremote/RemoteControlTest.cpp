#include <memory>
#include "Light.h"
#include "GarageDoor.h"
#include "SimpleRemoteControl.h"

int main(int argc, char **argv)
{
    auto remote = new SimpleRemoteControl;
    auto light = new Light;
    auto garageDoor = new GarageDoor;
    auto lightOn = new LightOnCommand(light);
    auto garageOpen = new GarageDoorOpenCommand(garageDoor);

    remote->setCommand(lightOn);
    remote->buttonWasPressed();
    remote->setCommand(garageOpen);
    remote->buttonWasPressed();

    return 0;
}

#include <iostream>

#include "Raychel/Raychel.h"
#include "Raychel/Engine/Raymarchable/sdObjects.h"

using namespace Raychel;

int main(int argc, char** argv)
{
    Logger::log("Hello, World!\n");

    IRaymarchable* sphere = new SdSphere{ObjectData{Transform{}}, 1.0};

    return 0;
}
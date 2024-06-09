#pragma once
#include "LettuceEngine/MessageSystem/MessageBase.h"

class EngineReady : public MessageBase {

};

class EngineHalting : public MessageBase {};
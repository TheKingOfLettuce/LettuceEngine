#include "Components/RandomVelocity.h"
#include "Components/ComponentFactory.h"
REGISTER(RandomVelocity);

using json = nlohmann::json;
using LettuceEngine::Math::Vector2;

RandomVelocity::RandomVelocity() : Component() {}

RandomVelocity::~RandomVelocity() {}

Vector2 RandomVelocity::GetVelocity() const {
    return _velocity;
}

float RandomVelocity::GetVelocityScale() const {
    return _velocityScale;
}

void RandomVelocity::SetVelocity(Vector2 val) {
    val.Normalize();
    _velocity = val;
}

void RandomVelocity::SetVelocityScale(float scale) {
    _velocityScale = scale;
}

void RandomVelocity::SaveToJson(json& j) {
    Component::SaveToJson(j);
    j["velocity"] = _velocity;
    j["scale"] = _velocityScale;
}

void RandomVelocity::LoadFromJson(const json& data) {
    SetVelocity(data.at("velocity"));
    SetVelocityScale(data.at("scale"));
    Component::LoadFromJson(data);
}

void RandomVelocity::Update(UpdateMessage* message) {
    Vector2 pos = _velocity * (message->GetTimeDelta() * _velocityScale);
    pos += _lettuce->Position();
    if (pos.X >= 600) {
        pos.X = 0;
    }
    else if (pos.X <= 0) {
        pos.X = 600;
    }
    if (pos.Y >= 600) {
        pos.Y = 0;
    }
    else if (pos.Y <= 0) {
        pos.Y = 600;
    }

    _lettuce->SetPosition(pos);
}

#pragma once
#include <string>
#include "LettuceObject.h"
#include "CollisionSystem/CollisionSystem2D.h"

namespace LettuceEngine {
    class Engine {
        public:
            static void SetWindowSize(unsigned int width, unsigned int height);
            static void SetWindowName(std::string name);
            static void SetWindowFps(unsigned int fps);
            static void SetCollisionSize(LettuceEngine::Math::Vector2 size);

            static Collision2DQuadTree* CollisionSystem();
            static bool IsRunning();

            static void StopWindow();
            static void LoadObject(LettuceObject* obj);
            static void StartMainLoop();

            static void WaitForMainLoopToExit();
    };
}
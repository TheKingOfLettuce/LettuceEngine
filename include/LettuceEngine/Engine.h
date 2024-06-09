#pragma once
#include <string>
#include "LettuceEngine/LettuceObject.h"
#include "LettuceEngine/CollisionSystem/CollisionSystem2D.h"

namespace LettuceEngine {
    class Engine {
        public:
            static void SetWindowSize(unsigned int width, unsigned int height);
            static void SetWindowName(std::string name);
            static void SetWindowFps(unsigned int fps);
            static void SetCollisionSize(LettuceEngine::Math::Vector2 size);

            static LettuceEngine::Math::Vector2 GetWindowSize();
            static unsigned int GetWindowWidth();
            static unsigned int GetWindowHeight();

            static void ToggleRaylibLogs(bool flag);

            static Collision2DQuadTree* CollisionSystem();
            static bool IsRunning();

            static void StopWindow();
            static void LoadObject(LettuceObject* obj);
            static void StartMainLoop();
            static void MainLoop();

            static void WaitForMainLoopToExit();
    };
}
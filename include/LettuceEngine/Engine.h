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
            static void SetCollisionSize(LettuceEngine::Math::Vector2 size, int maxObjects = 4);

            static LettuceEngine::Math::Vector2 GetWindowSize();
            static unsigned int GetWindowWidth();
            static unsigned int GetWindowHeight();

            static void ToggleRaylibLogs(bool flag);

            static Collision2DQuadTree* CollisionSystem();
            static bool IsRunning();

            static bool IsDebugView();
            static void SetDebugView(bool flag);

            static void LoadObject(LettuceObject* lettuce);
            static void RemoveObject(LettuceObject* lettuce);

            static void StopWindow();
            static void StartMainLoop();

            static void WaitForMainLoopToExit();

        private:
            static bool _isDebugView;
            static void MainLoop();
    };
}
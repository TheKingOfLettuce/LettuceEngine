#pragma once
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "LettuceObject.h"
#include "CollisionSystem/CollisionSystem2D.h"
#include "Input/InputSystem.h"

namespace LettuceEngine {
    class Engine {
        public:
            Engine();
            ~Engine();

            void SetWindowSize(unsigned int width, unsigned int height);
            void SetWindowName(std::string);
            void SetWindowFps(unsigned int fps);

            static Engine* GetInstance();
            Collision2DQuadTree* CollisionSystem();
            bool IsRunning();

            void StopWindow();
            void LoadObject(LettuceObject* obj);
            void StartMainLoop();

            void WaitForMainLoopToExit();

        private:
            static Engine* _instance;
            unsigned int _windowWidth;
            unsigned int _windowHeight;
            std::string _windowName;
            unsigned int _fps;
            LettuceObject* _root;
            Collision2DQuadTree* _collisionSystem;
            InputSystem _input;
            std::thread _loopThread;
            bool _isRunning;
            
            void MainLoop();
            void RenderStep();
            void UpdateStep();
    };
}
#include "Engine.h"
#include "Raylib/raylib.h"
#include "MessageSystem/MessageBus.h"
#include "MessageSystem/Messages/GameLoopMessages.h"
#include "MessageSystem/Messages/EngineMessages.h"
#include "Logging/Log.h"
#include <stdexcept>
#include <mutex>
#include <thread>
#include "Assets/AssetManager.h"
#include "Input/InputSystem.h"

using LettuceEngine::Engine;
using LVector2 = LettuceEngine::Math::Vector2;
using LettuceEngine::CollisionSystem::AABB;

static unsigned int _windowWidth;
static unsigned int _windowHeight;
static std::string _windowName;
static unsigned int _fps;
static bool _isRunning;
static std::thread _loopThread;
static LettuceEngine::InputSystem _input = LettuceEngine::InputSystem();
static LettuceObject* _root = new LettuceObject();
static Collision2DQuadTree* _collisionSystem = new Collision2DQuadTree(AABB(LVector2(1, 1), LVector2(1, 1)));

void UpdateStep() {
    UpdateMessage* updateMessage = new UpdateMessage(GetFrameTime());
    _root->Update(updateMessage);
    MessageBus::Publish(updateMessage);
}

void RenderStep() {
    ::BeginDrawing();
    ::ClearBackground(GRAY);
    RenderMessage* renderMessage = new RenderMessage();
    _root->Render(renderMessage);
    _collisionSystem->Render(renderMessage);
    MessageBus::Publish(renderMessage);
    ::EndDrawing();
}

void MainLoop() {
    Log::Info("Initializing main window");
    ::SetTargetFPS(_fps);
    ::InitWindow(_windowWidth, _windowHeight, _windowName.data());
    Log::Info("Window Initialized");
    MessageBus::Publish(new EngineReady());
    Log::Info("Starting main loop");
    while (!::WindowShouldClose() && _isRunning) {
        _input.GatherInput();
        _input.GatherClickables();
        UpdateStep();
        RenderStep();
    }
    MessageBus::Publish(new EngineHalting());
    AssetManager::UnloadAllData();
    ::CloseWindow();
    _isRunning = false;
}

void Engine::SetWindowSize(unsigned int width, unsigned int height) {
    _windowWidth = width;
    _windowHeight = height;
}

void Engine::SetWindowName(std::string name) {
    _windowName = name;
}

void Engine::SetWindowFps(unsigned int fps) {
    _fps = fps;
    if (_isRunning)
        ::SetTargetFPS(_fps);
}

void Engine::LoadObject(LettuceObject* obj) {
    _root->AddChild(obj);
}

Collision2DQuadTree* Engine::CollisionSystem() {
    return _collisionSystem;
}

bool Engine::IsRunning() {
    return _isRunning;
}

void Engine::StartMainLoop() {
    _isRunning = true;
    _loopThread = std::thread(&MainLoop);
}

void Engine::StopWindow() {
    _isRunning = false;
    _loopThread.join();
}

void Engine::WaitForMainLoopToExit() {
    if (!_isRunning) return;

    _loopThread.join();
}

void Engine::SetCollisionSize(LVector2 size) {
    Log::Info("Changing collision size to " + size.ToString());
    std::unordered_set<Collider2D*>* objs = _collisionSystem->GetAllObjects();
    delete _collisionSystem;
    _collisionSystem = new Collision2DQuadTree(AABB(size, size));
    while (!objs->empty()) {
        Collider2D* obj = objs->begin().operator*();
        objs->erase(obj);
        if (!_collisionSystem->Insert(obj))
            Log::Warning("Failed to insert collider into new input size");
    }
    delete objs;
}
#include "LettuceEngine/Engine.h"
#include "Raylib/raylib.h"
#include "LettuceEngine/MessageSystem/MessageBus.h"
#include "LettuceEngine/MessageSystem/Messages/GameLoopMessages.h"
#include "LettuceEngine/MessageSystem/Messages/EngineMessages.h"
#include "LettuceEngine/Logging/Log.h"
#include <stdexcept>
#include <mutex>
#include <thread>
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
#include "LettuceEngine/Input/InputSystem.h"
#include <stack>

using LettuceEngine::Engine;
using LVector2 = LettuceEngine::Math::Vector2;
using LettuceEngine::CollisionSystem::AABB;

static unsigned int _windowWidth;
static unsigned int _windowHeight;
static std::string _windowName;
static unsigned int _fps;
static bool _isRunning = false;
static std::thread _loopThread;
static LettuceEngine::InputSystem _input = LettuceEngine::InputSystem();
static LettuceObject* _root = new LettuceObject();
static Collision2DQuadTree* _collisionSystem = new Collision2DQuadTree(AABB(LVector2(1, 1), LVector2(1, 1)));
static std::stack<LettuceObject*> _deleteStack = std::stack<LettuceObject*>();

void UpdateStep() {
    UpdateMessage* updateMessage = new UpdateMessage(GetFrameTime());
    _root->Update(updateMessage);
    MessageBus::Publish(updateMessage);
    while (!_deleteStack.empty()) {
        LettuceObject* lettuce = _deleteStack.top();
        _deleteStack.pop();
        if (lettuce->GetParent() != nullptr)
            lettuce->GetParent()->RemoveChild(lettuce);
        delete lettuce;
    }
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

void Engine::MainLoop() {
    Log::Info("Initializing main window");
    ::SetTargetFPS(_fps);
    ::InitWindow(_windowWidth, _windowHeight, _windowName.c_str());
    Log::Info("Window Initialized");
    // load raylib data that required GPU access
    RaylibAssetManager::LoadAllAssetManagerGPUData();
    MessageBus::Publish(new EngineReady());
    Log::Info("Starting main loop");
    while (!::WindowShouldClose() && _isRunning) {
        _input.GatherInput();
        _input.GatherClickables();
        UpdateStep();
        RenderStep();
    }
    MessageBus::Publish(new EngineHalting());
    // Unload Raylib data that cannot persist after CloseWindow()
    RaylibAssetManager::UnloadAllAssetManagerGPUData();
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

LVector2 Engine::GetWindowSize() {
    return LVector2(_windowWidth, _windowHeight);
}

unsigned int Engine::GetWindowWidth() {
    return _windowWidth;
}

unsigned int Engine::GetWindowHeight() {
    return _windowHeight;
}

void Engine::SetWindowFps(unsigned int fps) {
    _fps = fps;
    if (_isRunning)
        ::SetTargetFPS(_fps);
}

void NoRaylibLog(int msgType, const char* text, va_list args) {return;}

void Engine::ToggleRaylibLogs(bool flag) {
    if (flag)
        ::SetTraceLogCallback(Log::CustomRayLibLog);
    else
        ::SetTraceLogCallback(NoRaylibLog);
}

void Engine::LoadObject(LettuceObject* obj) {
    _root->AddChild(obj);
}

void Engine::RemoveObject(LettuceObject* obj) {
    _deleteStack.push(obj);
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

void Engine::SetCollisionSize(LVector2 size, int maxObjects) {
    Log::Info("Changing collision size to " + size.ToString());
    std::unordered_set<Collider2D*>* objs = _collisionSystem->GetAllObjects();
    delete _collisionSystem;
    _collisionSystem = new Collision2DQuadTree(AABB(size, size), maxObjects);
    while (!objs->empty()) {
        Collider2D* obj = objs->begin().operator*();
        objs->erase(obj);
        if (!_collisionSystem->Insert(obj))
            Log::Warning("Failed to insert collider into new input size");
    }
    delete objs;
}

bool Engine::IsDebugView() {
    return _isDebugView;
}

void Engine::SetDebugView(bool flag) {
    _isDebugView = flag;
}

bool Engine::_isDebugView = false;
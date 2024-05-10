#include "Engine.h"
#include "Raylib/raylib.h"
#include "MessageSystem/MessageBus.h"
#include "MessageSystem/Messages/GameLoopMessages.h"
#include "MessageSystem/Messages/EngineMessages.h"
#include "Logging/Log.h"
#include <stdexcept>
#include "Assets/AssetManager.h"

using LettuceEngine::Engine;

Engine* Engine::_instance = nullptr;

Engine::Engine() {
    if (_instance != nullptr) {
        throw std::logic_error(std::string("Instance of Engine already exists, cannot create new one."));
    }
    _instance = this;
    _root = new LettuceObject();
    _collisionSystem = new Collision2DQuadTree(LettuceEngine::CollisionSystem::AABB(LettuceEngine::Math::Vector2(300, 300), LettuceEngine::Math::Vector2(300, 300)));
    _input = InputSystem();
    SetTraceLogCallback(Log::CustomRayLibLog);
    _isRunning = false;
}

Engine::~Engine() {
    delete _root;
    if (_instance == this) {
        _instance = nullptr;
    }
}

Engine* Engine::GetInstance() {
    return _instance;
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
    _loopThread = std::thread(&Engine::MainLoop, this);
}

void Engine::MainLoop() {
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

void Engine::UpdateStep() {
    UpdateMessage* updateMessage = new UpdateMessage(GetFrameTime());
    _root->Update(updateMessage);
    MessageBus::Publish(updateMessage);
}

void Engine::RenderStep() {
    ::BeginDrawing();
    ::ClearBackground(GRAY);
    RenderMessage* renderMessage = new RenderMessage();
    _root->Render(renderMessage);
    _collisionSystem->Render(renderMessage);
    MessageBus::Publish(renderMessage);
    ::EndDrawing();
}

void Engine::StopWindow() {
    _isRunning = false;
    _loopThread.join();
}

void Engine::WaitForMainLoopToExit() {
    if (!_isRunning) return;

    _loopThread.join();
}
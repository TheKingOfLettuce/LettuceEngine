# The Lettuce Engine

*Behold, I present onto thee into our noble Lettuce Kingdom*

## Introduction
The Lettuce Engine, a game engine wrapper around [raylib](https://github.com/raysan5/raylib). A huge amount of credit goes towards raylib and its contributors, it does a lot of the heavy lifting. This engine serves as a way to design applications or games within a framework, while leveraging the easy and power of raylib.

By no means is this a finished product, and I can almost guarantee it won't be something that is ever finished. But hey, at least I have a readme.

## Design Thought

### LettuceObjects
There is this concept of a `LettuceObject`. It is meant to serve as baseline for everything involved with the engine. It represents a thing within a space. Currently only 2D supported. This is where you will find properties like its position, rotation, scale. But most importantly, it also contains children `LettuceObjects` allowing you to nest as many children as you'd like. `LettuceObject` also contains `Components` which add behaviors to the things in space

### Components
As mentioned above, `Components` are what give things behavior within engine, such as rendering, collision, or even movement. There can be as many `Components` as you'd like on your `LettuceObject` including multiple of the same `Component`. The engine will come with some predefined `Components` to for some of the more needed behavior, such as a `Collider2D` component for collision, or a `TextArea` component for displaying and formatting text. But the idea is that `Component` is extensible and will allow for whatever behavior is desired.

### MesssageBus
The engine will come with a static utility called the `MessageBus` and can serve as the main form of communication within the full system. Engine messages, update messages, rendering messages, or even custom messages can be subscribed to, allowing for even more behavior when certain events happen.

### JSON Serialization
The main way `LettuceObjects` and `Components` save is via JSON. A `LettuceObject` will save everything about the object, including its components and its children. It saves to a JSON file, allowing you to restore an object to its full construction. There are provided `ComponentFactory` functions to register your custom `Component` to the save system.

## Building
`Makefile`. It has two commands. 
- `BuildStaticLib` which will build the `LettuceEngine.Lib`, which creates two folders, `bin/` for the library and `obj/` for the object files.
- `clean` which will delete the `bin/` and `obj/` folders

## Development
I primarily used VSCode during development and have made a simple and primitive `tasks.json` for the above `Makefile` commands. 

## Testing
[Catch2](https://github.com/catchorg/Catch2/tree/devel) is the testing framework used for LettuceEngine.

The following have unit tests written for them:
- AABB
- CallbackHandler
- CollisionSystem2D
- Color
- Component
- LettuceObject
- LinkedList
- MessageBus
- MessageHandler
- Vector2
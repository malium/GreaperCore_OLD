# Greaper Core

Is the base library for all the other Greaper projects, it's a library which provides all the needed functionality to create applications,
by lying between the application and the OS, and provides a set of tools for making easier the development using c++.
These set of tools, are inspired by how other languages aproach different problems and my own experience programming.
Right now it only supports Windows 64bits, in the future may support other OSs, such as some linux or unix variants.

## Greper: What is it? (Q&A)

For long time I've been programming game using several game engines, and other non game related projects, and I have managed to create a set of tools that I almost always use
when I program, therefore it came to me, as other people have done, to create a framework, where it will focused on creting applications and on top of it a set of libraries that
will make a graphics engine. Therefore,

- Is Greaper a game engine?
No.
- Is Greaper a graphics framework?
No.
- What Greaper is then?
Well not an easy answer, but to sum up, a set of utilities and a base framework to create almost any type of application, where the main target will be real time applications,
but not exclusively.

## Current Status

Right now I'm working on a Game and finishing my studies at the same time, that's why the Greaper project will grow slowly, as I can only work on it when I have time,
the good thing is that many of the things I want into Greaper are already done in some previous projects of mine, therefore many things I integrate will have been already tested
and only needed to adapt to this new ecosystem.

## What is included? (Features)

- Set of tools that provide easy access to information about the basic types, and specialized functions.
- PHAL, a Platform and Hardware Abstraction Layer, a set of tools that detects the Compiler, OS and information about the hardware and provide easy ways of branching the code if the target platform or hardware supports it.
- Easy way of handling Assertions.
- Set of preprocessor definitions in order to solve different platform in a single statement.
- Abstraction of the typical multithread classes and utilities with more debug information, for example, knowing what thread are colliding and report the collision.
- ModuleSystem that will handle types, factories and CVars from them, this system uses a protocol that all modules must follow in order to work properly.
- CommandSystem, that will manage a console and a way to send commands and handle them.
- Two types of Event handling, an instant one, class contains an Event object that manages a list of listeners, and a deferred one, theres a system that sends the triggered events to different listeners which subscribe to an EventID.
- DeferredCalls System that let's you make a call deferred in time (or frames on a realtime application).
- FileSystem abstraction that enables the addition of virtual filesystems (like a container, zip, 7z...).
- TaskManager that handles small tasks distributed in a number of background threads.
- WorkerThread spawner in order to enable background long tasks.
- ReflectionManager that will store all the type definitions even from the plugins or external libs, via manual reflection.
- SerializationManager that using the ReflectionManager will de/serialize types into different formats.
- TimeManager that provide time information and frame information for realtime applications.
- WindowManager providing multiple window management and enabling input pooling and rendering.
- InputManager that will hook to the created windows enabling input pooling and manipulation.
- CVarManager, that will store "ConsoleVariables" or global variables that when they are modified trigger an event to its listeners, to react to that change.

## Is Greaper Open Source? (Licensing)

Well I have meditated this question a thousand times, I've tried to create a private implementation and an open interface to interact with, but then I thought that
maybe this project is too big for a single person, therefore I finally reach the point where I'm decided to make it open source, in order to create a communtiy around this
project.

## Wanna collaborate?

Hey you! I would be really thankfull if that's your willing! But think that Greaper is a very big project and touching a little thing may cascade in a set of unwilling effects,
that does not mean that you shouldn't collaborate! My point here is that this project might be a bit scary to modify for a new user. Even though all help is welcomed.
This project has a code format and guidelines that have be followed in order to mantain consistency.

## Contact

Have you found a bug? open a ticket on github or
Contact me: marcossanchez405@gmail.com

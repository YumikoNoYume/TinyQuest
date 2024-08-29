# Tiny Quest
In this project I tried to not only make a simple game with several quests, but also write my own simple game engine.

![Look at this!](./screenshots/game_screenshot1.png)
![And this!](./screenshots/game_screenshot2.png)

### How to build
```
$ conan install . --build=missing
$ cmake --preset conan-default
$ cmake --build .\build\ --config Release
```

### How to run
```
$ TinyQuest.exe path_to_res/_folder
```
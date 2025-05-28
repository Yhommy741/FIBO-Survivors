 FIBO-Survivors

A fast-paced 2D survival shooter game developed in **C++17** using **SFML 3.0.1**.

## 🧭 Overview

**FIBO-Survivors** is an action-packed survival game where you control a hero battling endless waves of monsters. Use smooth controls, animated sprites, and fast-paced projectile combat to survive as long as possible. Track your survival time and health as you fight for a high score.

---

## 📚 Table of Contents

- [🗂️ Project Structure](#project-structure)
- [🛠️ Prerequisites](#prerequisites)
- [🏗️ Build Instructions](#build-instructions)
- [🕹️ How to Play](#how-to-play)
- [🎯 Controls](#controls)



## 🗂️ Project Structure

```
FIBO-Survivors/
├── src/ # Source code files
│ ├── main.cpp # Entry point
│ ├── game.h / .cpp # Main game loop and state management
│ ├── entity.h / .cpp # Generic base class for all entities
│ ├── player.h / .cpp # Player logic and controls
│ ├── monster.h / .cpp # Enemy AI and behavior
│ ├── bullet.h / .cpp # Projectile logic
│ ├── map.h / .cpp # Game map / background rendering
│ ├── hpbar.h / .cpp # Health bar UI
│ ├── ui.h / .cpp # UI elements (Game Over, etc.)
├── assets/ # Sprites, animations, sounds, fonts, etc.
│ └── UI/GameOver/ # Game Over image assets
└── README.md # Project documentation
```

---

## 🛠️ Prerequisites

- A C++17-compatible compiler
- [SFML 3.0.1](https://www.sfml-dev.org/download.php) properly installed
- [Visual Studio 2019 or later](https://visualstudio.microsoft.com/) (or CMake + Makefile for Linux/macOS)

---

## 🏗️ Build Instructions

1. **Clone the repository**
   ```bash
   git clone https://github.com/Yhommy741/FIBO-Survivors
   cd FIBO-Survivors
   ```

2. **Open the project**
   - For Visual Studio: Open the `.sln` file
   - For CMake: Set up the `CMakeLists.txt` if needed

3. **Build the project**
   - In Visual Studio: `Build > Build Solution` (or press `F7`)
   - Or via CLI if using Make/CMake

4. **Run the game**
   - In Visual Studio: Press `F5`
   - Or run the compiled binary manually

---

## 🕹️ How to Play

1. **Start** the game — the player character will spawn in the center.
2. **Move** using the keyboard (`W`, `A`, `S`, `D`).
3. **Aim** with your mouse — bullets auto-fire toward the mouse.
4. **Survive** against waves of monsters spawning from all directions.
5. **Game Over** occurs when the player's health reaches zero.
6. **Enjoy The Game**

---

## 🎯 Controls

| Key        | Action               |
|------------|----------------------|
| **W**      | Move Up              |
| **A**      | Move Left            |
| **S**      | Move Down            |
| **D**      | Move Right           |
| **Mouse**  | Aim bullets (auto-fire) |


Enjoy surviving In FIBO! 👾🔥
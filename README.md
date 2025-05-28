 ⬜🟧FIBO-Survivors🟧⬜

A Pixel 2D survival shooter game developed in **C++17** using **SFML 3.0.1**.

Developed by FRAB11 Group 15

	-	นายจักพรรณ	ศรีรอดบาง		67340500005
	-	นายสยมภู		ทองเนื้อแปด		67340500044
	-	นายภิรภัทร	กล่อมจิต			67340500061
	-	นายธนากร	เจริญพงษ์พินิจ		67340500071



https://github.com/user-attachments/assets/52c7ecc1-d8ed-405a-a959-f23d0f4c4e78


## 🧭 Overview 🧭

**FIBO-Survivors** เป็นเกมที่ประยุกต์การใช้ OOP จากวิชา FRA142/143 โดยเป็นเกมแนวยิงเอาชีวิตรอดแบบ 2D ที่ผู้เล่นจะต้องต่อสู้กับมอนสเตอร์ที่เกิดขึ้นแบบสุ่มบนแผนที่ โดยผู้เล่นสามารถเคลื่อนที่ได้ 4 ทิศทางและยิงกระสุนไปยังทิศทางที่เล็งด้วยเมาส์ เกมนี้ถูกพัฒนาด้วย C++17 และใช้ SFML 3.0.1 สำหรับกราฟิกและการจัดการอินพุต

---

## 📚 Table of Contents 📚

- [✅ Functional Requirements]
- [✅ Non-Functional Requirements]
- [🛠️ Prerequisites]
- [🏗️ Build Instructions]
- [🕹️ How to Play]
- [🎯 Controls]

## ✅ Functional Requirements ✅

•	2D Game
	เกมจะมีมุมมองแบบ 2D โดยใช้กราฟิกแบบพิกเซลอาร์ต

•	Player Movement
	ผู้เล่นสามารถเคลื่อนที่ได้ 4 ทิศทาง (ขึ้น, ลง, ซ้าย, ขวา) ด้วยปุ่ม W, A, S, D

•	Aiming and Shooting Bullets
	ผู้เล่นสามารถเล็งไปทิศทางใดก็ได้ด้วยเมาส์ กระสุนจะถูกยิงออกจากตำแหน่งของผู้เล่นไปยังตำแหน่งของเมาส์โดยอัตโนมัติ

•	Monster Spawning and Behavior
	มอนสเตอร์จะเกิดแบบสุ่มบนแผนที่ในช่วงเวลาที่กำหนด และจะเคลื่อนที่เข้าหาผู้เล่น

•	Collision Checker
	ตรวจสอบการชนระหว่างกระสุนและมอนสเตอร์ หากกระสุนชนมอนสเตอร์ มอนสเตอร์จะถูกทำลายและหายไป
	และหากมอนสเตอร์ชนผู้เล่น ผู้เล่นจะได้รับความเสียหาย

•	Player Health Bar
	พลังชีวิตปัจจุบันของผู้เล่นจะแสดงเป็นแถบพลังชีวิตเหนือตัวละครผู้เล่น

•	Timer
	แสดงเวลาที่ผู้เล่นเอาชีวิตรอดในเกมได้ในเกม โดยนับเป็นวินาที

•	Game Over Condition
	เมื่อพลังชีวิตของผู้เล่นเหลือศูนย์ เกมจะจบลงและแสดงหน้าจอ Game Over ผู้เล่นไม่สามารถเล่นต่อได้หลังจากนี้

•	Game Loop
	เกมจะทำงานในลูปอย่างต่อเนื่อง เพื่อเรนเดอร์กราฟิก, อัพเดตตำแหน่งของผู้เล่น, มอนสเตอร์ ,กระสุน และโลจิกเกมต่างๆ

•	OOP 
	เขียนโค้ดด้วยหลักการ OOP โดยมีคลาสสำหรับผู้เล่น, มอนสเตอร์, กระสุน, แผนที่ และ UI ต่างๆ


## ✅ Non-Functional Requirements ✅

•	Performance
	เกมรันได้อย่างน้อย 60 เฟรมต่อวินาที การรับอินพุต การเคลื่อนไหว และการแสดงผลต้องลื่นไหล

•	Portability
	เกมต้องสามารถคอมไพล์และรันบน Windows ด้วย Visual Studio 2019 ขึ้นไป และรองรับ C++17 กับ SFML 3.0.1

•	Usability
	การควบคุมต้องเข้าใจง่ายและตอบสนองดี UI มองเห็นได้ชัดเจนและเข้าใจง่าย

•	Reliability
	ไม่มี Bug ที่ทำให้เกมค้างหรือแครช เกมต้องทำงานได้อย่างต่อเนื่องโดยไม่มีปัญหาใดๆ

•	Maintainability
	โค้ดต้องถูกจัดระเบียบเป็นโมดูล อย่างชัดเจน มีคอมเมนต์และสามารถขยายฟีเจอร์หรือแก้ไขบั๊กได้ง่าย

•	Resource Management
	เกมต้องบริหารจัดการหน่วยความจำและ resource อย่างมีประสิทธิภาพ โหลด asset เมื่อจำเป็นและไม่เกิด memory leak


## 🗂️ Project Structure 🗂️

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
หน้าที่ของแต่ละคลาส
•	main.cpp
	•	โปรแกรมหลัก สร้างและรันอ็อบเจกต์ Game

•	game.h / game.cpp
	•	จัดการลูปหลักของเกม (Game Loop)
	•	ควบคุมสถานะเกม (เช่น กำลังเล่น, จบเกม)
	•	ประสานงานระหว่างอ็อบเจกต์ต่างๆ เช่น ผู้เล่น, มอนสเตอร์, กระสุน, UI

•	entity.h / entity.cpp
	•	คลาสพื้นฐาน (Base Class) สำหรับสิ่งที่มีอยู่ในเกม (Player, Monster, Bullet)
	•	กำหนดคุณสมบัติร่วม เช่น ตำแหน่ง, การวาด, การอัปเดตสถานะ

•	player.h / player.cpp
	•	จัดการตรรกะของผู้เล่น เช่น การเคลื่อนที่, การยิงกระสุน, การรับความเสียหาย
	•	รับอินพุตจากคีย์บอร์ดและเมาส์

•	monster.h / monster.cpp
	•	จัดการมอนสเตอร์ เช่น การเกิด, การเคลื่อนที่เข้าหาผู้เล่น, การรับความเสียหาย
	•	มี AI ง่ายๆ ให้มอนสเตอร์ไล่ผู้เล่น

•	bullet.h / bullet.cpp
	•	จัดการกระสุน เช่น การเคลื่อนที่, การตรวจสอบชนกับมอนสเตอร์
	•	ลบกระสุนเมื่อชนหรือออกนอกจอ

•	map.h / map.cpp
	•	วาดฉากหลังหรือแผนที่ของเกม
	•	อาจมีการจัดการกับขอบเขตหรืออุปสรรคในแผนที่

•	hpbar.h / hpbar.cpp
	•	แสดงแถบพลังชีวิตของผู้เล่นบนหน้าจอ
	•	อัปเดตค่าตามพลังชีวิตปัจจุบัน

•	ui.h / ui.cpp
	•	จัดการ UI อื่นๆ เช่น หน้าจอ Game Over, ตัวจับเวลา, คะแนน ฯลฯ

---

## 🛠️ Prerequisites 🛠️

- A C++17-compatible compiler
- [SFML 3.0.1](https://www.sfml-dev.org/download.php) properly installed
- [Visual Studio 2019 or later](https://visualstudio.microsoft.com/) (or CMake + Makefile for Linux/macOS)

---

## 🏗️ Build Instructions 🏗️

1. **Clone the repository**
   ```bash
   git clone https://github.com/Yhommy741/FIBO-Survivors
   cd FIBO-Survivors
   ```

2. **Open the project**
   - For Visual Studio: Open the `.sln` file

3. **Build the project**
   - In Visual Studio: `Build > Build Solution` (or press `F7`)

4. **Run the game**
   - In Visual Studio: Press `F5`
   - Or run the on .exe file after building the project

---

## 🕹️ How to Play 🕹️

1. **Start** the game — the player character will spawn in the center.
2. **Move** using the keyboard (`W`, `A`, `S`, `D`).
3. **Aim** with your mouse — bullets auto-fire toward the mouse.
4. **Survive as long as possible** against waves of monsters spawning from all directions.
5. **Game Over** occurs when the player's health reaches zero.
6. **Enjoy The Game**

---

## 🎯 Controls 🎯

| Key        | Action               |
|------------|----------------------|
| **W**      | Move Up              |
| **A**      | Move Left            |
| **S**      | Move Down            |
| **D**      | Move Right           |
| **Mouse**  | Aim bullets (auto-fire) |


Enjoy surviving In FIBO! 👾🔥🔥

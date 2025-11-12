# Smart IoT Robot Car with Bluetooth, Voice Control & Obstacle Avoidance

This project is an IoT-based autonomous robot car that can operate in **three different modes**:
1. **Manual Bluetooth Control Mode**
2. **Voice Control Mode**
3. **Obstacle Avoidance (Autonomous) Mode**

The robot uses an **HC-SR04 ultrasonic sensor** mounted on a **servo motor** to scan the environment and avoid obstacles. It can also be remotely controlled using a **Bluetooth mobile application**, including **voice commands**.

---

## 🚀 Features

| Feature | Description |
|--------|-------------|
| Manual Control | Control the robot using Bluetooth buttons (Forward, Back, Left, Right, Stop). |
| Voice Mode | Speak commands like "Forward", "Left", "Stop" which are interpreted as signals. |
| Auto Mode | Robot automatically avoids obstacles using ultrasonic sensing. |
| Mode Switching | Switch between modes using Bluetooth commands (`M`, `V`, `A`). |
| Servo Scanning | Servo rotates to check left and right distance when avoiding obstacles. |

---

## 🧠 Mode Switching Commands

| Command from Bluetooth | Mode |
|-----------------------|------|
| `M` | Manual Mode (Bluetooth Control) |
| `V` | Voice Control Mode |
| `A` | Auto Mode (Obstacle Avoidance) |

---

## 🎮 Manual Control (When in Manual Mode)

| Command | Action |
|--------|--------|
| `U` | Move Forward |
| `D` | Move Backward |
| `L` | Turn Left |
| `R` | Turn Right |
| `S` | Stop |

---

## 🎤 Voice Control Commands (When in Voice Mode)

| Symbol Received | Action |
|----------------|--------|
| `^` | Forward |
| `-` | Backward |
| `<` | Left |
| `>` | Right |
| `*` | Stop |

> These symbols are automatically sent by the **Bluetooth Voice Command App**.

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|----------|
| Arduino UNO | 1 |
| L293D / AFMotor Motor Driver Shield | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| Servo Motor (SG90 or MG995) | 1 |
| DC Motors (BO Motors or TT Motors) | 4 |
| HC-05 Bluetooth Module | 1 |
| Battery Pack (Recommended: 7.4V Li-ion or LiPo) | 1 |
| Chassis | 1 |

---

## 🔌 Circuit / Wiring Notes

- **Do NOT** power the servo directly from Arduino **5V** if motors are running.
- Use a **separate 7.4V battery pack** for motors and servo.
- **Common GND is required**: connect grounds of Arduino, driver, Bluetooth, and servo together.

---

## 🧱 Arduino Libraries Required

```text
AFMotor (for Motor Shield)
Servo.h

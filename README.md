# Microwave Oven Controller – Embedded Systems Project

This project implements a fully functional **Microwave Oven Controller** using a **PIC16F877A microcontroller**, developed and simulated in **PICSimLab** as part of my Embedded Systems Internship at **Emertxe**.

The system provides a complete user interface using an LCD and keypad, supports multiple cooking modes, handles time and temperature settings, performs pre-heating for convection mode, and controls heater and cooler in real time.

---

## 🛠 Tools & Technologies

- Microcontroller: PIC16F877A  
- IDE: MPLAB X IDE  
- Compiler: XC8  
- Simulator: PICSimLab (PICGenios Board)  
- Display: HD44780 16x4 LCD  
- Input: 4x4 Matrix Keypad  
- Sensor: LM35 Temperature Sensor  

---

## ⚙️ Features

- Power ON welcome screen  
- Mode selection menu:
  - Micro  
  - Grill  
  - Convection  
  - Start  
- Time setting using keypad (MM:SS format)  
- Temperature setting for Convection mode  
- Automatic pre-heating in Convection mode  
- Start / Pause / Resume / Stop operations  
- Real-time countdown timer display  
- Heater and cooler control using relays  
- End message displayed on completion  

---

## 🔄 Working Flow

The complete working sequence of the system is as follows:

1. **Power ON**
   - LCD displays:  
     `Powering ON Microwave Oven`

2. **Mode Selection**
   - User selects one of the following modes:
     - 1. Micro  
     - 2. Grill  
     - 3. Convection  
     - 4. Start  

3. **Time Setting**
   - User enters the cooking time using the keypad in **MM:SS** format.

4. **Temperature Setting (Convection Mode Only)**
   - User sets the required temperature in **°C**.

5. **Pre-heating Stage (Convection Mode Only)**
   - System performs pre-heating before starting the main cooking timer.

6. **Cooking Running**
   - Countdown timer is displayed on the LCD.
   - Heater and cooler are controlled automatically based on mode and temperature.

7. **Completion**
   - At the end of the timer, the system displays:  
     `Time Up – Enjoy Your Meal`

---

## 📸 Screenshots

The `screenshots/` folder contains images of the following stages:

1. Power ON screen  
2. Mode selection menu  
3. Time setting screen  
4. Temperature setting screen  
5. Pre-heating stage  
6. Cooking running (countdown)  

These screenshots demonstrate the complete functional flow of the system.

---

## ▶️ How to Run the Project

1. Open the project in **MPLAB X IDE**  
2. Build the project using **XC8 compiler**  
3. Load the generated `.hex` file into **PICSimLab**  
4. Select:
   - Board: PICGenios  
   - Microcontroller: PIC16F877A  
5. Select LCD type: **HD44780 16x4**  
6. Run the simulation and operate using the keypad  

---

## 📁 Project Structure

- `Microoven.X/` – MPLAB X project source code  
- `production/` – Generated HEX file  
- `screenshots/` – Output screenshots of each stage  
- `README.md` – Project documentation  

---

## 👤 Author

**Likhith Gowda H R**  
Embedded Systems Intern  
Emertxe – Embedded Systems Training Institute  

---

## 📌 Note

This project was developed to gain hands-on experience in:

- Embedded C programming  
- LCD interfacing  
- Keypad interfacing  
- Timer-based state machines  
- Real-time control using microcontrollers  


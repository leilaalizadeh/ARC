# ARC

My solutions for the Computer Architectures (ARC) lab exams at PoliTO, from 2022 to 2026.

The code is in C and ARM assembly for the LandTiger board (LPC1768) and runs in Keil µVision.

## Folders

Each year has its own folder, and each exam inside it is named by date (for example `20250129-A`). A, B and C are different versions of the same exam. Some exams also have the exam text or the correction as a PDF.

Every exam has a `Template` folder with the full Keil project:

- `Main.c`: main code of the solution
- `MY_CODE.s`: assembly part
- `Button`, `LED`, `joystick`, `Timer`, `RIT`, `ADC`, `DAC`, `GLCD`, `TouchPanel`: libraries for the board peripherals
- `PDF`: LPC17xx manual and board schematics

## How to run

Open `Template/Template.uvprojx` in Keil µVision, build it, and run it on the board or in the simulator.

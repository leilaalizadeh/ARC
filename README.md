# ARC - Architecture Exams

Solutions to the Computer Architectures (ARC) lab exams at Politecnico di Torino, from 2022 to 2026. The code is written in C and ARM assembly for the LandTiger board (NXP LPC1768, ARM Cortex-M3) and runs in Keil µVision.

## Repository structure

```
ARC/
├── 2022/
│   ├── Template/          # Base project with all peripheral libraries
│   ├── 20220204-A/
│   ├── 20220204-B/
│   └── ...
├── 2023/
├── 2024/
├── 2025/
└── 2026/
```

Each exam folder is named after the exam date (`YYYYMMDD`). A, B and C are different versions of the same exam. Every folder has the full Keil project inside `Template/`, and some also have the exam text or the correction as a PDF.

## Project layout

| Folder / file | Content |
|---|---|
| `Main.c`, `Main.h` | Main code of the solution |
| `MY_CODE.s` | Assembly part of the exam |
| `Button/`, `LED/`, `joystick/` | Buttons, LEDs and joystick |
| `Timer/`, `RIT/` | Timers and RIT |
| `ADC/`, `DAC/` | Potentiometer (ADC) and speaker (DAC) |
| `GLCD/`, `TouchPanel/` | LCD screen and touch panel |
| `SVC/` | SVC handler |
| `PDF/` | LPC17xx manual and board schematics |

## How to run

1. Install Keil µVision 5 with the LPC1700 device pack.
2. Open `Template/Template.uvprojx` from any exam folder.
3. Build it (F7) and run it on the board or in the simulator.

## Contact

Leila Alizadeh  
If you have any questions, email me at alizadehleila94@gmail.com

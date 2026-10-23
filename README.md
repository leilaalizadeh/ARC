# ARC – Architecture Exams

Solutions to past **Computer Architectures (ARC)** lab exams at Politecnico di Torino, written in C and ARM assembly for the **LandTiger board (NXP LPC1768, ARM Cortex-M3)** using **Keil µVision**.

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

Each exam folder is named after the exam date (`YYYYMMDD`, with `-A`/`-B`/`-C` for different versions of the same session) and contains a complete Keil project in `Template/`. Some folders also include the exam text or a correction as PDF.

## Project layout

Each `Template/` project includes:

| Folder / file | Content |
|---|---|
| `Main.c`, `Main.h` | Exam solution entry point |
| `MY_CODE.s` | ARM assembly part of the exam |
| `Button/`, `LED/`, `joystick/` | GPIO peripherals and interrupt handlers |
| `Timer/`, `RIT/` | Timers and Repetitive Interrupt Timer |
| `ADC/`, `DAC/` | Analog input (potentiometer) and output (speaker) |
| `GLCD/`, `TouchPanel/` | LCD display and touch screen |
| `SVC/` | Supervisor call handler |
| `PDF/` | LPC17xx user manual and board schematics |

## Getting started

1. Install [Keil µVision 5](https://www.keil.arm.com/) with the LPC1700 device pack.
2. Open `Template/Template.uvprojx` from any exam folder.
3. Build the project (F7) and run it on the LandTiger board or in the simulator.

## Author

[Leila Alizadeh](https://github.com/leilaalizadeh)

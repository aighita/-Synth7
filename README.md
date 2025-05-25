<div align='center'>
  <h1>µSynth7</h1>
</div>

**µSynth7** is a compact digital synthesizer built around an ESP32 microcontroller. The project offers an intuitive interface for playing musical notes and includes a sequencer for automated playback. It's ideal for musical experimentation and educational purposes.

## 🔧 Features

- **7 capacitive touch buttons**: Correspond to musical notes in a Nashville number system key.
- **Analog joystick**: Transpose octave.
- **PWM buzzer**: For generating audio output.
- **16x2 I2C LCD display**: Provides real-time feedback on mode and parameters.
- **Operating modes**: Automatic sequencer with tempo and pitch control

## 🛠️ Required Hardware

- [ESP32 DevKit V1](https://www.optimusdigital.ro/ro/placi-avr/4561-placa-esp32-devkit-v1.html)
- 7x touch buttons
- 1x analog joystick
- 1x passive buzzer
- 1x 16x2 I2C LCD
- Breadboards and jumper wires

## 🔌 Wiring

| COMPONENT             | ESP32 PIN                    |
|-----------------------|------------------------------|
| Butoane Note (C)      | GPIO 4/5/13/14/27/32/33      |
| Buton Opțiuni         | GPIO 19                      |
| Joystick X/Y          | GPIO 34/35                   |
| Buzzer PWM            | GPIO 18                      | 
| LCD SDA/SCL           | GPIO 21/22                   |

## 💻 Software

This project is written in C++ using the Arduino framework. It follows a modular codebase, making it easy to understand and extend.

### Project Structure

- `uSynth7.ino`: Main program loop and system initialization
- `Buttons.h / Buttons.cpp`: Handles note button inputs
- `Joystick.h / Joystick.cpp`: Reads analog joystick input
- `DisplayManager.h / DisplayManager.cpp`: Manages LCD updates
- `Sequencer.h / Sequencer.cpp`: Logic for step sequencing notes
- `Options.h / Options.cpp`: Manages user options and modes
- `Degree.h`: Defines note frequencies and names

## 🚀 Usage

1. **Assemble the hardware** as per the schematic (see Wiring section).
2. **Setup software**:
   - Open the project in Arduino IDE
   - Select your ESP32 board and COM port
   - Upload the sketch
3. **Interact**:
   - Tap buttons to play notes
   - Use the options button + note button to update options
   - Use JoyStick to transpose octave
   - Watch the LCD for feedback

Developed by [aighita](https://github.com/aighita)
# Changelog

All notable changes to this project will be documented in this file.

This project follows a **versioned hardware + firmware** model.

---

## [1.0.0] - 2026-01-11
### 🎉 Initial Public Release

#### ✨ Features
- Infrared remote control to turn PC ON and OFF
- Smart shutdown protection logic:
  - 1 press to power ON when PC is OFF
  - 3 presses within 5 seconds to power OFF when PC is ON
- Standby operation using ATX 5VSB
- Full electrical isolation using PC817 optocoupler
- IR protocol identification tool (`IRTest`)
- Support for physical IR remotes and Xiaomi Mi Remote app

#### 🔧 Hardware
- Arduino Nano powered from 5VSB
- VS1838B IR receiver
- PC817 optocoupler for PWR_SW isolation
- Dedicated PC ON/OFF status input
- Designed for standard ATX motherboards

#### 🖨️ PCB
- Custom PCB designed in EasyEDA
- Ground plane implementation
- Proper optocoupler isolation
- Correct IR receiver positioning
- Dedicated connectors for ATX, PWR_SW and IR module

#### 📄 Documentation
- Complete technical documentation in PDF
- Wiring diagrams and schematics
- Repository structured for firmware, PCB and documentation

---

## [Unreleased]
### 🚧 Planned Improvements
- ESP32 version with Wi-Fi support
- Home Assistant integration
- Web interface for configuration
- Android application with direct IR control
- Additional safety and debounce filters

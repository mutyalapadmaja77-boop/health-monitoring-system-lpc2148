# health-monitoring-system-lpc2148
Embedded systems project using LPC2148 microcontroller to monitor pulse rate and temperature in real time, displaying health status on an LCD and triggering LED alerts for abnormal conditions.
# Smart Health Monitoring System using LPC2148

## Overview
The Smart Health Monitoring System is an embedded systems project developed using the LPC2148 microcontroller. The system monitors vital health parameters such as pulse rate and temperature in real time. Pulse data is acquired through an ADC-connected pulse sensor, while temperature values are entered using a 4x4 keypad. The measured values are displayed on a 16x2 LCD, and an LED-based alert system is activated whenever abnormal conditions are detected.

## Objectives
- Monitor pulse rate in real time using an analog pulse sensor.
- Accept temperature input through a keypad interface.
- Display health status on an LCD screen.
- Provide visual alerts for abnormal health conditions.
- Demonstrate sensor interfacing and peripheral integration using LPC2148.

## Features
- Real-time pulse rate monitoring.
- Temperature input through a 4x4 keypad.
- ADC interfacing with pulse sensor.
- 16x2 LCD display for health status.
- LED-based emergency alert system.
- Classification of readings as LOW, NORMAL, or HIGH.
- Implemented using Embedded C on LPC2148.

## Hardware Components
- LPC2148 Development Board
- Pulse Sensor
- 16x2 LCD Display
- 4x4 Matrix Keypad
- LEDs
- Power Supply

## Software Tools
- Embedded C
- Keil µVision
- Proteus Design Suite

## System Architecture

### LCD Interface
- RS → P0.16
- RW → P0.17
- EN → P0.18
- D4 → P0.19
- D5 → P0.20
- D6 → P0.21
- D7 → P0.22

### Pulse Sensor
- Sensor Output → P0.28 (AD0.1)

### LEDs
- P1.16 to P1.23

### Keypad
- Rows → P1.24 to P1.27
- Columns → P1.28 to P1.31

## Working Principle

### Pulse Monitoring
- The pulse sensor generates an analog signal.
- LPC2148 ADC converts the signal into digital values.
- BPM is calculated and classified as:
  - LOW (< 60 BPM)
  - NORMAL (60–100 BPM)
  - HIGH (> 100 BPM)

### Temperature Monitoring
- User enters temperature using the keypad.
- The entered value is processed and displayed as:
  - LOW (< 36°C)
  - NORMAL (36–37°C)
  - HIGH (> 37°C)

### Alert Mechanism
- LEDs blink when:
  - BPM > 100, or
  - Temperature > 37°C
- LEDs remain OFF under normal conditions.

## Results
The system successfully performs:
- Real-time pulse rate monitoring.
- Temperature acquisition through keypad input.
- LCD-based health status display.
- LED-based alert generation.
- Hardware and Proteus simulation validation.

## Project Outcomes
- Learned ADC interfacing with LPC2148.
- Implemented LCD and keypad interfacing.
- Developed real-time monitoring logic using Embedded C.
- Integrated multiple peripherals into a single embedded application.

## Challenges Faced
- ADC value fluctuations.
- Keypad debouncing issues.
- LCD timing synchronization.
- Port configuration errors.

## Solutions Implemented
- Added delays for stable ADC readings.
- Improved keypad scanning logic.
- Corrected LCD initialization sequence.
- Verified hardware connections and port mappings.

## Future Enhancements
- Add temperature sensor for automatic measurement.
- Integrate wireless communication for remote monitoring.
- Store health records using external memory.
- Develop IoT-based cloud monitoring capabilities.

## Author
Padmaja

## References
1. LPC2148 Datasheet
2. Keil µVision Documentation
3. LPC2148 User Manual
4. Microcontrollers and Interfacing Laboratory Manual
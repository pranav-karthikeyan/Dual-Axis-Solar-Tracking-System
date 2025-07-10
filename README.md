# Automated Dual-Axis Solar Tracking System

---
## Contributors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/USPraveenkumar">
        <img src="https://avatars.githubusercontent.com/u/115538058?v=4" width="100" height="100" style="border-radius:50%;" alt="Praveenkumar US"/>
        <br />
        <sub><b>Praveenkumar U S</b><br/>CB.EN.U4ELC22056</sub>
      </a>
    </td>
    <td align="center">
      <img src="https://github.com/adityathannasiappan.png?size=100" width="100" height="100" style="border-radius:50%;" alt="Aditya Thannasiappan"/>
      <br />
      <sub><b>Aditya Thannasiappan</b><br/>CB.EN.U4ELC22061</sub>
    </td>
    <td align="center">
      <a href="https://github.com/KRISSHANTH-R">
        <img src="https://avatars.githubusercontent.com/u/175583154?v=4" width="100" height="100" style="border-radius:50%;" alt="Krisshanth R"/>
        <br />
        <sub><b>Krisshanth R</b><br/>CB.EN.U4ELC22021</sub>
      </a>
    </td>
        <td align="center">
      <a href="https://github.com/pranav-karthikeyan">
        <img src="https://avatars.githubusercontent.com/u/73694914?v=4" width="100" height="100" style="border-radius:50%;" alt="Pranav Karthikeyan"/>
        <br />
        <sub><b>Pranav Karthikeyan</b><br/>CB.EN.U4ELC22062</sub>
      </a>
    </td>
  </tr>
</table>

---

## Institution

**Department of Electrical and Electronics Engineering**  
**Amrita School of Engineering,**  
**Amrita Vishwa Vidyapeetham,**  
**Coimbatore - 641112**  
*March 2025*

---

## Project Overview

This is a 5-month project undertaken as part of the course **"19EEE381 - Open Lab"** in the B.Tech Electrical and Computer Engineering (ELC) program.

---

## Project Description

The **Automated Solar Tracking System** is a cutting-edge solution designed to maximize solar energy harvesting by dynamically tilting solar panels to follow the sun's movement.

Traditional fixed solar panel mounts suffer from inefficiencies as they cannot adjust to the changing position of the sun throughout the day. This project implements a **dual-axis solar tracker** that adjusts both the azimuth and elevation angles of the solar panel using two servo motors.

The system relies on four Light Dependent Resistor (LDR) sensors to measure light intensity from different directions, feeding this data into an ESP32 microcontroller which calculates optimal panel orientation.

Power metrics such as voltage, current, and power consumption are monitored using the CJMCU-219 INA219 sensor and displayed on an OLED screen for local feedback.

Remote monitoring is enabled through the **Blynk IoT platform**, allowing real-time performance tracking and historical data access.

Experimental results demonstrate improved energy efficiency compared to stationary solar panels by maintaining optimal sun exposure throughout the day.

---

## Introduction

Solar power is a dominant, sustainable energy source, but static panels cannot follow the sun’s movement, limiting efficiency.

Our **dual-axis solar tracker** overcomes this by using two servo motors to adjust panel orientation horizontally (azimuth) and vertically (elevation) based on light intensity data from LDR sensors.

The ESP32 microcontroller processes sensor input to direct these adjustments while monitoring power through the INA219 sensor. Data is displayed locally and transmitted remotely via Blynk.

---

## Problem Statement

Fixed solar panels only optimize sunlight absorption during limited periods when the sun is directly facing the panel. As the sun moves, these panels lose efficiency and produce less energy.

Environmental factors like dust, shading, and temperature further degrade output.

The project aims to develop an automated tracking system that constantly orients the panel toward the sun, maximizing energy intake and improving overall solar power generation.

Key challenges include synchronization of servo motors, real-time data processing, system stability, and balancing power consumption against net energy gain.

---

## Future Scope

- Scaling down the system for cost-effective mass deployment  
- Integration of advanced weather prediction to pre-emptively adjust panel position  
- Expanding IoT capabilities for more sophisticated remote monitoring and control

---

*This project showcases the powerful synergy between embedded systems and IoT technology in optimizing renewable energy solutions.*

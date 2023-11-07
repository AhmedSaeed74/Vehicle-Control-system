# Vehicle Control System 

## Description

Welcome to the Vehicle Control System, an implementation of a user-driven program that simulates vehicle control and sensor readings with various functionalities. This system provides you with control over the vehicle's engine, as well as settings for traffic light color, room temperature, and engine temperature. It offers a convenient interface to interact with the vehicle's operations and sensors.

## Features

- **Engine Control:** You can turn the vehicle engine on and off.
- **Real-time Updates:** The system provides real-time updates on the vehicle's state.
- **Sensor Simulation:** While the engine is on, the system simulates sensor readings, allowing you to set values for traffic light color, room temperature, and engine temperature.
- **Traffic Light-based Speed Control:** The system adjusts the vehicle's speed based on the selected traffic light color.
- **Temperature-based Actions:** Depending on room and engine temperature readings, the system controls the AC and engine temperature controller.
- **User-Friendly Menu:** The menu allows you to select options easily and see the impact on the vehicle's state.
- **Bonus Requirement:** The code can be customized using a preprocessor directive to enable or disable specific features related to the "Engine Temperature Controller."

## Usage

1. **Compile the Code:** To use the Vehicle Control System, compile the provided C code and upload it to your microcontroller.

2. **Run the Program:** After uploading the code, run the application. The system will display the available options for engine control and sensor settings.

3. **Interaction:** Interact with the system by choosing options such as turning on the engine, setting sensor values, and more.

4. **Real-time Updates:** The system continuously updates and displays the current state of the vehicle.

## Bonus Option

You have the option to customize the system by using the `#define WITH_ENGINE_TEMP_CONTROLLER` preprocessor directive. When enabled (set to 1), this directive activates specific code segments related to the "Engine Temperature Controller" feature. You can configure this directive to tailor the system to your preferences.

This project provides an engaging and interactive way to explore vehicle control and sensor simulations. Enjoy your experience!

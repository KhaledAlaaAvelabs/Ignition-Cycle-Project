# Ignition-Cycle-Project

FSM application will have 6 states are (Ignition OFF – Maintain speed – Increase speed – Decrease speed – Brake – Fire Air Bag).

Transitions between FSM states depend on distance values that comes from sensor reading that represents as Duty cycle in the range of 0% to 100% with frequency 6.7 KHz for the ultrasonic sensor.

Transmit the current state command (1 byte) and distance value (1 byte) to SLAVE through UART then display it on the terminal on the other node.

All the states send command and distance to SLAVE except “Fire Air Bag” send command ONLY.

Ignition remains OFF until DIO pin changes his idle state, once that changes so Ignition is now ON and Ignition OFF will transition to state based on distance.
Ranges of states :
Maintain speed (160 -> 90), Increase speed (255 -> 160), Decrease speed (90 -> 20), Brake (20 -> 5), Fire Air Bag (5-> 0).

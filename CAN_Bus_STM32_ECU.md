# Reading out ECU CAN bus using a STM32FXXX device (tested on STM32F429-Discovery)

# The problem
configuring the SJW, BS1, BS2 and Prescaler to achieve a desired baudrate and the Sample Point to be a correct value
for different CAN higher-layers (J1939, CANOpen, etc.)

# The solution
I did not find any suitable reference that says what is the best sampling point for different protocols, so I decided to test each
possible sample point, see if one of them works, and then choose it as the right solution.

The equation of CAN bus baudrate for STM32 MCUs is:
** Baudrate = APB1Clock / (Prescaler * (SJW + BS1 + BS2)) **


If you are not getting any CAN frames and you think it's because of your baudrate, then by pressing a button (firing up an external interrupt), CANWorker class will find another combiniation of SJW, BS1, BS2 and Prescaler, you need to wait a second or two, if nothing received yet, press the button again until you get CAN frames.

This example is inspired from the STM Cube's examples (STM324xG_EVAL/Examples/CAN/CAN_Networking).
The codes may not work right away, as it's just a gist not a repo. but the idea is pretty simple and codes are handy, it helped me getting data from a Renault Kerax and a Mercedes Axor.

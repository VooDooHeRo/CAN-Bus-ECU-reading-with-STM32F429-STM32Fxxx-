# Reading out ECU data using a STM32FXXX device (tested on STM32F429-Discovery)

# The problem
configuring the SJW, BS1, BS2 and Prescaler to achieve a desired baudrate and the Sample Point to be a correct value
for different CAN higher-layers (J1939, CANOpen, etc.)

# The solution
I did not find any suitable reference that says what is the best sampling point for different protocols, so I decided to test each
possible sample point, see if one of them works, and then choose it as the right solution.
The equation of CAN bus baudrate for STM32 MCUs is:
Baudrate = APB1Clock / (Prescaler * (SJW + BS1 + BS2))


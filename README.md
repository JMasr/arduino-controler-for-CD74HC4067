# Arduino 17-Channel Relay Control using CD74HC4067 and Pin-8

This repository contains an Arduino sketch for controlling a 17-channel relay using the CD74HC4067 multiplexer chip and Pin-8. The code allows you to control one relay at a time through serial commands. 

## Features

- Controls up to 17 relay channels using the CD74HC4067 multiplexer and an pin-8.
- Supports basic commands to activate specific relay channels.
- Includes a test function to sequentially activate all relays for testing purposes.
- Simple serial interface for sending commands.

## Hardware Requirements

- Arduino board (e.g., Uno, Mega, Nano)
- CD74HC4067 multiplexer chip
- 16-channel relay module
- Connecting wires

## Wiring Diagram

| Arduino Pin | CD74HC4067 Pin | Relay Module |
|-------------|----------------|--------------|
| 2           | SIG            |              |
| 7           | EN             |              |
| 3           | S0             |              |
| 4           | S1             |              |
| 5           | S2             |              |
| 6           | S3             |              |
| 8           |                | Relay 17     |

## Usage

1. Connect the Arduino board, CD74HC4067, and relay module as per the wiring diagram.
2. Upload the provided code to your Arduino board.
3. Open the Serial Monitor at a baud rate of 9600.
4. Use the following commands to control the relays:

   - **test**: Sequentially activates all relays for testing.
   - **0-15**: Activates the specified relay channel (e.g., sending `3` will activate relay 4).
   - **16**: Activates the additional relay controlled by `controlPlus` (`Pin-8`).

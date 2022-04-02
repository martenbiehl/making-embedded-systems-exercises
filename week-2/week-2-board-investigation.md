# Week 2 - Exercise 2: Investigate Project Boards

## Tasks

For each board, look at the datasheet and getting started information for the board. Draw the hardware block diagram for the board. For peripherals, note the communication paths (SPI, I2C, etc).

Look through the datasheet for the processor and other documents. Answer these questions:

- What kind of processor is it?
- How much Flash and RAM does it have? Any other memory types?
- Does it have any special peripherals? (List 3-5 that you find interesting.)
- If it has an ADC, what are the features?
- How much does the board cost vs what the processor costs? Is the processor in stock anywhere? (Try Digikey, Mouser, Octopart, Google, and so on.)

Look at one application note for this board.

## Task 1: Investigate the board intended for your final project

| Function             |     |
| -------------------- | --- |
| Processor            |     |
| Flash                |     |
| RAM                  |     |
| Other Memory         |     |
| Special Peripheral 1 |     |
| Special Peripheral 2 |     |
| Special Peripheral 3 |     |
| Special Peripheral 4 |     |
| Special Peripheral 5 |     |
| ADC                  |     |
| ADC features         |     |
| Board cost           |     |
| Processor cost       |     |
| Stock                |     |

---

**Further Notes:**

## Task 2: Investigate the board assigned to you: LEDMCUEVM-132

| Function             |                                                          |
| -------------------- | -------------------------------------------------------- |
| Processor            | 120 Mhz Arm Cortex M4F with FPU                          |
| Flash                | 1024KB                                                   |
| RAM                  | 256KB SRAM                                               |
| Other Memory         | EEPROM: 6KB, Internal ROM, External Peripheral Interface |
| Special Peripheral 1 | 10/100 Ethernet                                          |
| Special Peripheral 2 | USB 2.0 OTG                                              |
| Special Peripheral 3 | 8 UARTs                                                  |
| Special Peripheral 4 | QSSI, 2 CAN                                              |
| Special Peripheral 5 | 10 I2C, 4 PWM                                            |
| ADC                  | yes                                                      |
| ADC features         | 2 12-bit ADC, 2Msps, three comparator                    |
| Board cost           | Digikey: 131,67 USD, Mouser: 118,80 USD                  |
| Processor cost       |                                                          |
| Stock                | Digikey: 5, Mouser: 3, TI: 0                             |

---

**Further Notes:**

- SPI for up to 6 devices
- UART for LMM family devices
- CAN transceiver for UART for LMM family devices
- 4 pwm for dimming
- multiple GPIOs
- 5v power
- digital isolaters for all MSP432 signals
- standard CAN bus with a transceiver

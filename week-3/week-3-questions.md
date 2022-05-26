# Week 3 - Blinky Questions

## What are the hardware registers that cause the LED to turn on and off? (From the processor manual, don’t worry about initialization.)

Tracing the LED (LD3) through the files, I find:

`LD3_GPIO_Port GPIOG`
LD3 is in the GPIOG Port

`LD3_Pin GPIO_PIN_13`
LD3 is on Pin 13 there

`GPIOG ODR13`
`ODR 0x14`
In the debugger I can see this register (ODR = output data register) and see its value change according to the led value.

`GPIOG_BASE (AHB1PERIPH_BASE + 0x1800UL)`
This is the base adresse of the GPIOG Port

`AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)`
Which in turn is referencing the peripheral base adress

`PERIPH_BASE 0x40000000UL`
Which is this.

`GPIO_PIN_13 ((uint16_t)0x2000)`
This is the actual pin register address mask

Altogether this would mean that the adress of the LED is

```
Register = GPIOG_BASE + 0x14 & 0x2000

GPIOG_BASE = (AHB1PERIPH_BASE + 0x1800UL)
Register = AHB1PERIPH_BASE + 0x1800UL + 0x14 & 0x2000

AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
Register = PERIPH_BASE + 0x00020000UL + 0x1800UL + 0x14 & 0x2000

PERIPH_BASE 0x40000000UL
Register = 0x40000000UL + 0x00020000UL + 0x1800UL + 0x14 & 0x2000

Register = 0x40020000UL + 0x1800UL + 0x14 & 0x2000
Register = 0x40021800UL + 0x14 & 0x2000
Register = 0x40021814UL & 0x2000

0x2000 = 0b10000000000000
>> 13

```

## What are the registers that you read in order to find out the state of the button?

Tracing the Button (B1) through the files, I find:

`B1_GPIO_Port GPIOA`
B1 is in the GPIOA Port

`B1_Pin GPIO_PIN_0`
B1 is on Pin 0 there

`GPIOA IDR0` is PA0
`IDR 0x10`
In the debugger I can see this register (IDR = input data register) and see its value change according to the button value.

`GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)`
This is the base adresse of the GPIOA Port

`AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)`
Which in turn is referencing the peripheral base adress

`PERIPH_BASE 0x40000000UL`
Which is this.

`GPIO_PIN_0 ((uint16_t)0x0001)`
This is the actual pin register address mask

Altogether this would mean that the adress of the button is

```
Register = GPIOA_BASE + 0x10 & 0x0001

`GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)`
Register = AHB1PERIPH_BASE + 0x0000UL + 0x10 & 0x0001

`AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)`
Register = PERIPH_BASE + 0x00020000UL + 0x0000UL + 0x10 & 0x0001

PERIPH_BASE 0x40000000UL
Register = 0x40000000UL + 0x00020000UL + 0x0000UL + 0x10 & 0x0001

Register = 0x40020000UL + 0x0000UL + 0x10 & 00x0001
Register = 0x40020000UL + 0x10 & 0x0001
Register = 0x40020010UL & 0x0001

0x0001 = 0b00000000000001
>> 0

```

## Can you read the register directly and see the button change in a debugger or by printing out the value of the memory at the register’s address?

In the debugger in STM32CubeIDE I used the SFR view to look at these registers.

I can access the button register with with `volatile uint32_t button_value = ((*(uint32_t *)0x40020010UL) & 0x0001) >> 0;`

I can access the led register with `volatile uint32_t led_value = ((*(uint32_t *)0x40021814UL) & 0x2000) >> 13;`

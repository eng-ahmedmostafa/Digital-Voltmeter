# Digital-Voltmeter


In this project, I followed MISRA C guidelinesو using the ATMEGA32 microcontroller, which features a 10-bit ADC for precise voltage measurement. Since the microcontroller's ADC can only handle a maximum of 5V, a voltage divider circuit is implemented to scale down the input voltage to within this range.

The voltage divider uses two resistors to proportionally reduce the input voltage (up to 25V) to a 5V output. The microcontroller then multiplies this value by 5 in the software to display the actual input voltage on a 16x2 LCD screen. Key components include the ATMEGA32A microcontroller, an LCD for display, and various resistors and capacitors for circuit stability and noise reduction.

The circuit is designed with 8-bit communication between the LCD and the microcontroller, allowing for simpler control, though 4-bit communication can also be used. The ADC setup involves configuring registers to ensure accurate conversion, with the ADC operating in free-running mode at a lower clock frequency for improved accuracy.

The project covers essential ADC configurations, such as enabling the ADC feature, setting the reference voltage to 5V, selecting the input channel, and choosing an appropriate prescaler to control the ADC clock frequency. These settings ensure the voltmeter functions effectively, providing accurate voltage readings within the specified range.

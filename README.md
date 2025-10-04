# Esp32 C3 Phone V1.0
This is the project that I am most proud of, I have been working on this for a long time and I hope that everyone who sees this project thinks it is good.

This project will have many versions and probably different versions for different boards when I add WI-FI. There are a lot of comments in the code that make it easy to fix if you want to fix it to suit yourself.

In the Password program, you can add your own passwords and emails by changing the examples or adding more IF statements. It is very easy to do, all you need to do is duplicate the IF function in void password at the long comment and change the number in the "else if (NP == 1)" to the next number that is not already used like this

```cpp
else if (NP == 3) { // change the 3 to 4 if you want to add this two times in the code
    display.setCursor(0, 26);
    display.println("some@email.com");
    display.setCursor(0, 36);
    display.println("Test123#");
}
```




I hope everyone likes it! :D

### OLED 128x64 Display Wiring

| OLED Pin | Connects To | Description      |
|----------|------------|-----------------|
| VCC      | 5V (or 3.3V) | Power supply    |
| GND      | GND        | Ground          |
| SDA      | D8         | I2C Data line   |
| SCL      | D9         | I2C Clock line  |
### Button Wiring

| Button | Arduino Pin | Function                         |
|--------|------------|---------------------------------|
| Up     | D6         | Moves selection up               |
| Down   | D7         | Moves selection down             |
| Left   | D5         | Moves selection left / next      |
| Right  | D10        | Moves selection right / previous |
| OK     | D20        | Confirm / enter selection        |

### Functions/apps

* Calcylator 
* Game (My Spike game)
* Password saver
* Stopwatch
* More functions/apps are coming!

# Esp32 C3 Phone V2.0
This is the project that I am most proud of, I have been working on this for a long time and I hope that everyone who sees this project thinks it is good.

This project will have many versions and probably different versions for different boards when I add WI-FI. There are a lot of comments in the code that make it easy to fix if you want to fix it to suit yourself.

---
In the Password program , you can add your own passwords and emails by changing the examples or adding more IF statements. It is very easy to do, all you need to do is duplicate the IF function in void password at the long comment and change the number in the "else if (NP == 1)" to the next number that is not already used like this:

```cpp

if (NP == 0) {
    display.setCursor(0, 26);
    display.println("your@email.com");
    display.setCursor(0, 36);
    display.println("Password123!");
  } else if (NP == 1) {
    display.setCursor(0, 26);
    display.println("mine@email.com");
    display.setCursor(0, 36);
    display.println("CoolGuy2?");
  } else if (NP == 2) { // see how i have changed the number in the IF statement
    display.setCursor(0, 26);
    display.println("some@email.com");
    display.setCursor(0, 36);
    display.println("Test123#");
}
```
This works whith the Notes program it's literally the same thing just with notes.

---

If you want to change the pictures follow this totorial to make your own bitmaps: https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/

The pokemon pictures and the sunset i found on this website: https://codewalr.us/archive2.php?topic=649.30

And if you want to change the animations you can make your own or you can find other animations on: https://animator.wokwi.com/

You might need to change the button pins and to do that find line 21-25 and change the numbers to the pins you want to use and if you need to change the oled monitor pins go to line 68 and change the numbers to the pins you want to use.

The controles can be a litle difrent depending on the program so hear is the controles.

| App      | OK         |     Move        | EXTRA      |
|----------|------------|-----------------|------------|
| Menu     | Middle button/OK            | UP/DOWN/LEFT/RIGHT   | No Extra                |
| Calc     | Middle button/OK            | UP/DOWN/LEFT/RIGHT   | No Extra                |
| Game     | UP (Its Jump but it counts) | UP (Its Jump)        | DOWN = Back             |
| Pass     | Middle button/OK            | LEFT/RIGHT           | No Extra                |
| Stop     | Middle button/OK            | LEFT/RIGHT           | No Extra                |
| Pics     | Middle button/OK            | LEFT/RIGHT           | No Extra                |
| Test     | Middle button/OK            | UP/DOWN              | Middle button/OK = Stop |
| Vids     | Middle button/OK            | UP/DOWN              | No Extra                |
| Note     | Middle button/OK            | LEFT/RIGHT           | No Extra                |

---

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
* Game (My Spike game pls check it out on my profile)
* Password saver
* Stopwatch
* Pictures
* Reaction time game (High score coming soon)
* Videos/animations
* Notes (Changing notes from WI-FI coming soon only for Esp32 and other boards whith WI-FI)
* More functions/apps are coming!

---
I hope everyone likes it! :D

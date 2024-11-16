N64 Controller for Apple II
----------------------------

Connect your N64 to the Apple II game IO port

Connections:

      Arduino       N64
      --------     -----
       V3.3    -  Voltage
       Ground  -  Ground
       Pin 2   -  Data Pin

      Arduino          Apple II Game IO
      --------        ------------------
      Pin 5 (pwmX)  -  Pin 6  (X)
      Pin 6 (pwmY)  -  Pin 10 (Y)
      Pin 7         -  Pin 2  (Button 0)
      Pin 8         -  Pin 3  (Button 1)
      Ground        -  Pin 8


N64 controller pinout:
       _______
      /       \     1 - 3.3V
      | 1 2 3 |     2 - Data
      |_______|     3 - Ground

Apple 16-pin DIP socket (on the motherboard):

Pushbutton 3     9   |  *      *  |  8  Ground
Stick-1 Y        10  |  *      *  |  7  Stick-2 X
Stick-2 Y        11  |  *      *  |  6  Stick-1 X
Annunciator 3    12  |  *      *  |  5  /$C040 Strobe
Annunciator 2    13  |  *      *  |  4  Pushbutton 2
Annunciator 1    14  |  *      *  |  3  Pushbutton 1
Annunciator 0    15  |  *  __  *  |  2  Pushbutton 0
No Connection    16  |  * |  | *  |  1  +5V


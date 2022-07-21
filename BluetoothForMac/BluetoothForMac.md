# Bluetooth for the Mac Peeps

## 1. In processing, create a new file. In that file, paste the code below. Run it. Then, you'll see a list of your ports. Find the one that has ESP32. It should either start with "/dev/cu." or "/dev/tty.". Pick one.

```
import processing.serial.*;

Serial myPort;       

printArray(Serial.list());
```

## 2. Upload the code below to your ESP32. The code below is similar to the code given by Nick, but without the controls/codes for the LED and Button because we're just debugging right now to see if your ESP32 can receive data from processing through bluetooth. The code below will print whatever button you press in Processing (which is either w or s).

```
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)           //error catching
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; //declares the Bluetooth object


void setup() {

  Serial.begin(115200);
  SerialBT.begin("ESP32");  //begins Bluetooth Serial connection
  Serial.println("Started successfully.");

}

char readIn;

void loop() {
  
  if (SerialBT.available()) //if there are bytes available in the buffer
    readIn = char(SerialBT.read()); //read in one and store it in readIn

  Serial.println(readIn);
  delay(20);
}
```

## 3. Paste the code below in Processing. 

```
import processing.serial.*;  //imports library used for wireless comm with the HC-05
Serial myPort;               // declares Serial Port object from library
String Text;

void setup()
{
 size(900,1000);                         // create window of this size
 myPort=new Serial(this, "/dev/tty.ESP32test", 115200);  //COM port will likely be different, try different ones until it works (usually one of COM3-COM7)
 myPort.bufferUntil('\n');               //delays calling serialEvent unitl reaching '\n'
}

void serialEvent(Serial myPort){        //serialEvent is called whenever data is available
  Text = myPort.readStringUntil('\n');   //reads Serial.println() from Arduino
}

int state = 0;
int x = 0;
void draw()
{

  background(237,240,241);        // sets background to a color, parameters correspond to an RGB code
  fill(20,160,133);               // sets color we will use to fill shapes
  stroke(33);                     // sets color used for border around shapes
  strokeWeight(1);                // sets width of stroke when drawing shapes
  
  rect(x,700,50,50,10);           //creates a rectangle at x,y with size width,height
  x+=1;
  if (x == 800)
    x=0;
  
  fill(0);
  textSize(32);
  //text(Text, 400, 700);           //draws text at x,y
    
  if (state == 1) {
    myPort.write('w');            //writes to the Bluetooth Serial port
    state = 0;
  } else if (state == 2) {
    myPort.write('s');
    state = 0;
  }
  
}

void keyPressed() {               //called whenever a key is pressed, key is automatically set to the key that is pressed
  if(key == 'w')
    state = 1;
  else if (key == 's')
    state = 2;
}
```

### IMPORTANT: ***Make sure to change the port in the line:***

``` 
myPort=new Serial(this, "/dev/tty.ESP32test"
```
### ***Change "/dev/tty.ESP32test" to whatever your port from Step 1.***

## 4. Open the Serial Monitor of ESP32 in Arduino. Then, run processing. While processing is on, press 'w' or 's'. Letters should show up in the Serial Monitor of ESP32 in arduino. (See video below)


https://user-images.githubusercontent.com/70046331/180144227-a49f8b15-8553-4e80-acd3-c8b412c56ddc.mp4


<br>

## Still not working?
### 1. Try changing the port. Go to step 1 again. If you tried "/dev/cu.", try the one that begins with "/dev/tty." or vice versa.
### 2. Make sure you uploaded the ESP32 code from Step 2 to the ESP32 itself.
### 3. Make sure that the Serial Monitor is the one from ESP32. Check your ports in Arduino.
### 4. In the ESP32 Code from Step 2, change the string inside the function of the statement:
```
SerialBT.begin("ESP32");
```
(this statement is in the setup() code) into the whatever string follows "/dev/cu." or "/dev/tty." For example, in my mac, ESP32 is called "/dev/cu.ESP32test" so I changed the statement above to the statement below:

```
 SerialBT.begin("ESP32test");
```

## Still stuck? Contact the mentors!

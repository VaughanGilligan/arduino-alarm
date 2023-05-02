/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL4srzaodTO"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "-y01C3LAmwiEDjk2V5hNCfZeRkU3-tzd"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <Bridge.h>
#include <BlynkSimpleYun.h>

int ledPin = 13; // LED connected to digital pin 13
//int buttonPin = A1;
int buzzerPin = 8;

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  digitalWrite(13, value);
  while (value == 1)
  {
for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) 
    {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    analogWrite(buzzerPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    }

for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) 
   {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    analogWrite(buzzerPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}


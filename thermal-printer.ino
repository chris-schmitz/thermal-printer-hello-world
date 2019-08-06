#include "Adafruit_Thermal.h"
#include "paradowski_logo.h"
#include "light_inspiration.h"

// * Our printer needs the 9600 baude rate for communication.
// * Note that this is separte from the serial baude rate we use to write to
// * the serial monitor (different serial bus).
#define PRINTER_BAUDE_RATE 9600

#define button 2

// * Note that because we're working from a trinket M0 we don't need to use
// * SoftwareSerial, we can just use the built in hardware serial buses in the board.
// * That said, if we do switch to something else to run the printer (e.g. an ATTiny85),
// * we may need to use software serial. First spot to look in that case would be:
//
// ? "Examples from custom libraries/Adafruit_Thermal_printer_library/A_printertest.ino "
//
// * in the arduino examples
Adafruit_Thermal printer(&Serial1);

void setup()
{

    pinMode(button, INPUT);

    // * Leaving in for testing
    // while (!Serial)
    //   ;

    Serial.begin(9600);
    Serial.println("Starting up");

    Serial1.begin(PRINTER_BAUDE_RATE);
    Serial.println("Beginning printer");
    printer.begin();
}

bool printedReceipt = false;
uint8_t currentButtonState = 0;
uint8_t lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;

void loop()
{
    uint8_t buttonStatus = digitalRead(button);

    if (buttonStatus != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        currentButtonState = buttonStatus;

        if (printedReceipt == false && currentButtonState == LOW)
        {
            Serial.println("Printing ...");
            // printer.justify('C');
            // printer.doubleHeightOn();
            // printer.println(F("Kevin FUCKING Olson"));
            // printer.doubleHeightOff();
            // printer.println(F("*AEM Guru*"));

            // printer.printBitmap(light_inspiration_width, light_inspiration_height, light_inspiration_data);
            printer.printBitmap(paradowski_logo_width, paradowski_logo_height, paradowski_logo_data);
            printer.justify('L');
            // printer.println(F("Hello .... WORLD!!"));
            printer.println("\n\n");
            printer.boldOff();

            printedReceipt = true;
        }

        if (currentButtonState == HIGH)
        {
            printedReceipt = false;
        }
    }
    lastButtonState = buttonStatus;
}

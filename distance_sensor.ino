int TRIG_PIN = 27; /corresponds to P4.5 - attach the trigger pin of the ultrasonic sensor here
int ECHO_PIN = 26; /corresponds to P4.4 - attach the echo pin of the ultrasonic sensor here
int distance = 0; /initialise the distance

void setup() { /this section sets up the msp board

    pinMode(TRIG_PIN,OUTPUT); /set the trigger pin as an output pin (allows the distance sensor to send a pulse)
    pinMode(ECHO_PIN,INPUT); /set the echo pin as an input pin (allows the distance sensor to receive a pulse)
    Serial1.begin(9600); /this is for bluetooth communication via serial to a phone - it just initialises the UART (make sure the bluetooth device has the TXD connected to pin P3.3 and RXD to pin P3.2
    }

void loop() { /this is the main section of the code that runs continuously

    long duration, distance; /set the variables duration and distance to hold large integer values
    digitalWrite(TRIG_PIN, LOW); /switch the trig output to low (0V) through the ultrasonic sensor
    delay(1); / wait 1ms
    digitalWrite(TRIG_PIN, HIGH); /send a high (5V) pulse through the ultrasonic sensor
    delay(5); / wait 5ms (this is specified by the requirements in the ultrasonic sensor)
    digitalWrite(TRIG_PIN,LOW); /switch the trig output to low (0V) through the ultrasonic sensor

    duration = pulseIn(ECHO_PIN,HIGH); /calculate the duration between the trigger signal going out and the return signal coming in
    distance = (duration/2)/29.1; /calculate the distance based on the time difference - this distance formula is provided in the handbook for the ultrasonic sensor

    if (distance < 20) { /for this prototype, I programmed level detection solely using the distance sensor to show how one sensor can solve a big problem
						*/it is also possible to use this in tandem with the video detection to provide more information about distance to the user (however we did not have enough time in this demo)
      Serial1.println("Ascending stairs approaching: "); /the level set for the appropriate distance was done via testing. 
      Serial1.print(distance); /the camera is positioned at an angle facing downard, if the distance shorten it means the surface is rising, if it lengthens it means the surface is falling
      Serial1.println("cm away"); /the Seria1 print commands send the message in "" to the connected phone
      delay(3000); /wait 3 seconds before sending the next pulse
    }

    else if (distance > 31) { /this detects falling surfaces, similar to the above

      Serial1.println("Descending stairs approaching: ");
      Serial1.print(distance);
      Serial1.println("cm away");
      delay(3000);
    }

    else { /if no change in surface level, send a message to the user to keep going forward
      
      Serial1.println("No changes, keep going");
      delay(2000); /wait 2 seconds before sending the next pulse
    }
}

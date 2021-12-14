/*
  Final_Arc
  accelerates a magnet back and forth along a curve using IR sensors to check whether the magnet has made it across
*/

// mosfet pins
int coil1 = 3; // mosfet 1 on pin 3
int coil2 = 5; // mosfet 2 on pin 5
int coil3 = 6; // mosfet 3 on pin 6
int coil4 = 9; // mosfet 4 on pin 9 (points in opposite direction as 1,2,3)
int coil5 = 10; // mosfet 5 on pin 10 (points in opposite direction as 1,2,3)
int coil6 = 11; // mosfet 6 on pin 11 (points in opposite direction as 1,2,3)

// IR sensor pins
int sensor1 = A0;    // sensor 1 on analog 0
int sensor2 = A1;    // sensor 2 on analog 1

int waitTime = 600; // time to wait until triggering the next side after passing sensor
int flipTime = 2000; // time between sides triggering

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  // initialize outputs
  pinMode(coil1, OUTPUT);
  pinMode(coil2, OUTPUT);
  pinMode(coil3, OUTPUT);
  pinMode(coil4, OUTPUT);
  pinMode(coil5, OUTPUT);
  pinMode(coil6, OUTPUT);

  // initialize inputs
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

  // cut power to all solenoids
  digitalWrite(coil1, LOW);
  digitalWrite(coil2, LOW);
  digitalWrite(coil3, LOW);
  digitalWrite(coil4, LOW);
  digitalWrite(coil5, LOW);
  digitalWrite(coil6, LOW);
}

// function to pulse a coil
void pulse(int coil, int onTime) {
  digitalWrite(coil, HIGH);
  delay(onTime);
  digitalWrite(coil, LOW);
  //delay(breakTime); // I haven't tested without this yet, but we might not need it
}

// the loop function runs over and over again forever
void loop() {
  // accelerate the magnet
  pulse(coil1, 75); // was 70
  pulse(coil2, 55); // was 60
  pulse(coil3, 12); //was 10

  while (analogRead(sensor2) < 400) { // if magnet has not passed all the way over try again
    pulse(coil1, 75);
    pulse(coil2, 55);
    pulse(coil3, 12);
  }
  delay(waitTime); // wait a little extra time

  // return magnet
  pulse(coil6, 30);
  pulse(coil5, 20);
  delay(40);
  pulse(coil4, 50);

  while (analogRead(sensor1) < 400) { // if magnet has not passed all the way over try again
    pulse(coil6, 30);
    pulse(coil5, 20);
    delay(40);
    pulse(coil4, 50);
  }
  delay(waitTime); // wait a little extra time
}

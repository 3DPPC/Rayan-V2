#include <StateMachine.h>
// #include <Servo.h> // error code


StateMachine machine = StateMachine();
State* onState = machine.addState(&on); 
State* offState = machine.addState(&off);

State* freeHandState = machine.addState(&freeHand);
State* holdState = machine.addState(&hold);
State* grabState = machine.addState(&grab);
State* releaseState = machine.addState(&release);

//State* grip1State = machine.addState(&);
//State* grip2State = machine.addState(&);
//State* grip3State = machine.addState(&);

State* vibrateState = machine.addState(&vibrate); 
State* stillState = machine.addState(&still); 

// States
void off() {
  Serial.println("This device is turned off");
}

void on() {
  Serial.println("This device is turned on");
}

void freeHand() {
  Serial.println("This device is in freeHand mode");
}

void grab() {
  Serial.println("This device is grabbing");
}

void release() {
  Serial.println("This device is releasing");
}

void hold() {
  Serial.println("This device is holding");
}

// TODO: evaluate if these can be replaced with a class
void vibrate() {
  Serial.println("This device is vibrating");
}

void still() {
  Serial.println("This device is still");
}

//class Vibrator {
//  public:
//    Vibrator();
//    void vibrateMe();
//  private:
//    int pin = 1;
//};
//Vibrator::vibrateMe() {
//  Serial.println("This device is vibrating");
//};

// transitions
bool turningOn() {
  if(digitalRead(5) == HIGH){
    return true;
  }
  return false;
}

bool turningOff() {
  if(digitalRead(5) == HIGH){
    return true;
  }
  return false;
}

bool startGrabbing(){
  if(digitalRead(5) == HIGH){
    return true;
  }
  return false;
}

bool startReleasing(){
  if(digitalRead(5) == HIGH){
    return true;
  }
  return false;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  
  // TODO: research more on turningOn
  offState->addTransition(&turningOn,onState);
  onState->addTransition(&turningOff,offState);
  freeHandState->addTransition(&startGrabbing,holdState);
  holdState->addTransition(&startReleasing,freeHandState);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}

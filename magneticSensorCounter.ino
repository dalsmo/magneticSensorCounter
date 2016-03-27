
//simple sketch to register sensor input from magnetic sensors and increment a counter
// the counter is displayed over seial, so thet the user can read it. 
// every XX points the arduino will ground a given output triggering some external function

/* motto better to make mistaks now, than regretting doing nothing later*/

int points = 0;
int previousLoopMaxPoints = 0;
int threshhold = 500;
boolean triggered[20]; // try to default initialise to zero if possible 
int pinNumbers[20] = {A1,A2....A10,10,11,...,20};

int exitePin = 21;

void setup() {
  // put your setup code here, to run once:
  // al pins are input pins to start with:), no nead to define
  pinMode(exitePin, OUTPUT);
  digitalWrite(exitePin, HIGH);
}

void loop() {
  
  // check all inputs, count points when being triggerd 
  for(int i=0; i<20,i++){
     if(digitalRead(i)==HIGH && triggered[i]==true){
       // pin already counted, do nothing
     }else if(digitalRead(i)==HIGH && triggered[i]==false){
       // pin trigger!
       triggered[i]=ture;
       counter++;
     }else if(digitalRead(i)==LOW && triggered[i]==true){
       triggered[i]=false;
     }else(digitalRead(i)==LOW && triggered[i]==false){
       // nothing is happening, do nothing
     }  
  }
  
  // trigger external thing if we have passed the threshoild
  if( (points%threshhold) < (previousLoopMaxPoints%threshhold) ){
    digitalWrite(exitePin, LOW);
    delay(100);
    digitalWrite(exitePin, HIGH);
  }
  previousLoopMaxPoints = points;
  
  // now give the serial some output
  for(int i=0; i<10;i++){
    Serial.println("."); // to clear the screen
  }
  Serial.print(".               ");
  Serial.print(points);
  Serial.print("  points");
  Serial.println(".");
  Serial.println(".");
  for(int i=0; i<10;i++){
    Serial.print(triggered[i]);
    if(i%5==0){
      Serial.print("    ");
    }
  }
  
 
}





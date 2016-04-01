
//simple sketch to register sensor input from magnetic sensors and increment a counter
// the counter is displayed over seial, so thet the user can read it. 
// every XX points the arduino will ground a given output triggering some external function

/* motto better to make mistaks now, than regretting doing nothing later*/

int points = 0;
int previousLoopMaxPoints = 0;
int threshhold = 500;
boolean triggered[20] = {false,false,false,false,false, false,false,false,false,false, false,false,false,false,false, false,false,false,false,false}; // try to default initialise to zero if possible 
int pinNumbers[20] = {3,4,5,6,7, 8,9,10,11,12, 57,58,59,60,61, 62,63,64,65,66};

int exitePin = 13;

void setup() {
  Serial.begin(9600); 
  // put your setup code here, to run once:
  // al pins are input pins to start with:), no nead to define
  pinMode(exitePin, OUTPUT);
  digitalWrite(exitePin, HIGH);
  for(int i=0; i<20;i++){
    digitalWrite(pinNumbers[i], LOW);
    pinMode(pinNumbers[i], INPUT);
  }
}

void loop() {
  
  // check all inputs, count points when being triggerd 
  //for(int i=0; i<20;i++){
  // triggered[i]= digitalRead(pinNumbers[i]);
  //}
  for(int i=0; i<20;i++){
     if((digitalRead(pinNumbers[i])==LOW) && (triggered[i]==true)){
       // pin already counted, do nothing
     }else if((digitalRead(pinNumbers[i])==LOW) && (triggered[i]==false)){
       // pin trigger!
       triggered[i]=true;
       points++;
     }else if((digitalRead(pinNumbers[i])==HIGH) && (triggered[i]==true)){
       triggered[i]=false;
     }else if((digitalRead(pinNumbers[i])==HIGH) && (triggered[i]==false)){
       // nothing is happening, do nothing
     }else{
      
     }
  }
  
  // trigger external thing if we have passed the threshoild
  if( (points%threshhold) < (previousLoopMaxPoints%threshhold) ){
    digitalWrite(exitePin, LOW);
    delay(1000);
    Serial.println("                        CONGRATULATIONS! ");
    digitalWrite(exitePin, HIGH);
  }
  previousLoopMaxPoints = points;
  
  // now give the serial some output
  for(int i=0; i<20;i++){
    if(i%5==0){
      Serial.print("    ");
    }
    Serial.print(triggered[i]);
  }
  Serial.print("   ");
  Serial.print(points);
  Serial.println(" Points");
}

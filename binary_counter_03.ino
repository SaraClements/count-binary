//LED Pin Variables
int LedPins[] = {2,3,4,5,6,7,8,9};

void setup() {
  // put your setup code here, to run once:

  for(int i = 0; i < 8; i++) {
    pinMode(LedPins[i], OUTPUT);
  }

  //utilize serial monitor
  Serial.begin(9600);

}

void loop() {

  countBinary();
  
}

//convert integers to binary values
int *intToBinary(int n) {

  //array to store binary number
  int binaryNum[] = {0,0,0,0,0,0,0,0};

  //counter for binary array
  int i = 0;
  while(n >= 1) {
    // storing remainder in binary array
    binaryNum[i] = n%2;
    n = n/2;
    i++;
  }

  //test code by printing final result to serial monitor
  
  Serial.print("binaryNum = {");

  for(i = 0; i<=7; i++) {
    Serial.print(binaryNum[i]);
    Serial.print(",");
  }

  Serial.print("}");
  Serial.println();


  //allocate 8 bits of memory to revBin pointer (to be used in next loop)
  //required to set up pointer in order to return revBin in function
  
  int *revBin = malloc(8);
  if(!revBin){
    return NULL;
  }

  //print binary array in reverse order to create revBin
  
  for(int j = 7, d = 0; j >= 0; j--, d++){
    revBin[d] = binaryNum[j];
  }

  //test code by printing final result to serial monitor
  
  Serial.print("revBin = {");

  for(i = 0; i<=7; i++) {
    Serial.print(revBin[i]);
    Serial.print(",");
  }

  Serial.print("}");
  Serial.println();

  // return revBin, will create pointer to reference this later
  return revBin;

}


// function to translate revBin array to output on LEDs
void binaryLights(int n){

  //call array revBin using pointer (runs fcn and sets pointer to array return value whose address has already been stored)
  int *p = intToBinary(n);
  
  for(int i = 0; i <=7; i++){
    if(p[i] == 0){
      digitalWrite(LedPins[i], LOW);
    } else {
      digitalWrite(LedPins[i], HIGH);
    }
    // test efficacy of pointer via serial monitor
    Serial.print("i = ");
    Serial.print(i);
    Serial.println();      
    Serial.print("revBin[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(p[i]);
    Serial.println(); 
  }
  
  //reallocate pointer
  free(p);

}

//counts from 0 to 255 and calls fcns to translate integer to binary to LED output
void countBinary(){
  
  for(int i = 0; i <= 255; i++) {
    binaryLights(i);
    delay(100);
  }
}


#define SW1 PC0 // A0
#define SW2 PC1 // A1
#define SW3 PC2 // A2
#define SW4 PC3 // A3
#define SWPORT PORTC
#define SWDDR DDRC
#define SWPIN  PINC

void setup() {
  Serial.begin(9600);
  SWDDR  |= (1<<SW1) | (1<<SW2) | (1<<SW3) | (1<<SW4); //FORCE INPUT
  SWPORT |= (1<<SW1) | (1<<SW2) | (1<<SW3) | (1<<SW4); //Pullups ON
}

void loop() {
  static unsigned int oldstate, swstate;
  oldstate = swstate;
  swstate = ~SWPIN & ((1<<SW1) | (1<<SW2) | (1<<SW3) | (1<<SW4));
  if(swstate !=oldstate){
    Serial.print(swstate);
    delay(1);
  }  
}


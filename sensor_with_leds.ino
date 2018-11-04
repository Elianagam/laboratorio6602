#define LED100CM 2  
#define LED90CM 3
#define LED80CM 4
#define LED70CM 5
#define LED60CM 6

#define LED50CM 7
#define LED40CM 8
#define LED30CM 9

#define LED20CM 10
#define LED10CM 11

#define ECHO 12
#define TRIGGER 13

const float vsound = 34300; // cm/s
const int ledPins[] = {	LED100CM, LED90CM, LED80CM, LED70CM, LED60CM, 	// VERDE
			LED50CM, LED40CM, LED30CM,			// AMARILLO
    			LED20CM, LED10CM				// ROJO
		      }; 
int lenLeds = 10; 
int max_distance = 100; 

void setup() {
    Serial.begin(9600);

    for(int i = 0; i < lenLeds; i++) {
	pinMode(ledPins[i], OUTPUT);
    }

    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);

    ledsOff(0); //comienza con todos los leds apagados
}

void loop() {
    startTrigger();
    float distance = getDistance();
		
    int pos = abs(int((distance / 10) - 10)); // obtiene la posicion del ultimo led que se encendera
						// ej int((35cm/10) -10) = |int(-6.5)| = 6, pos de led de 30cm 
	
    ledsOff(pos);

    if(distance <= max_len) { 
	// si la distancia es menor a 100 se encienden los leds
    	ledsOn(distance);
    }
}

void ledsOff(int pos) {
    //apago los leds que correspondan a una distancia menor a la posicion actual
    for(int i = pos; i < lenLeds ; i++) {
	digitalWrite(ledPin[i], LOW);
    }
}

void ledsOn(int pos) {
    for(int i = 0; i < pos; i++) {
	digitalWrite(ledPin[i], HIGH);
    }
}

float getDistance() {
    unsigned long time = pulseIn(ECHO, HIGH); // en microsegundos
    float distance = tiempo * vsound * 10^6 / 2; 
    Serial.print(distance + "cm \n");
    delay(500);

    return distance;
}

void startTrigger() {
    // inicia trigger para comenzar a medir
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
	
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGGER, LOW);
}

#define LED100CM 11  
#define LED90CM 10
#define LED80CM 9
#define LED70CM 8
#define LED60CM 7

#define LED50CM 6
#define LED40CM 5
#define LED30CM 4

#define LED20CM 3
#define LED10CM 2

#define ECHO 12
#define TRIGGER 13

const float vsound = 34300; // cm/s
const int ledPins[] = { LED100CM, LED90CM, LED80CM, LED70CM, LED60CM,   // VERDE
                        LED50CM, LED40CM, LED30CM,                      // AMARILLO
                        LED20CM, LED10CM,                               // ROJO
                        };
int lenLeds = 10;
int max_distance = 100;
float last_distance;
int init_pos;
int end_pos;

void setup() {
    Serial.begin(9600);

    for(int i = 0; i < lenLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
    }

    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
    last_distance = 0.00;
    init_pos = 0;
    end_pos = lenLeds;
    ledsOff(0); //comienza con todos los leds apagados
}

void loop() {
    startTrigger();
    float distance = getDistance();

    int pos = abs(int((distance / 10) - 10)); // obtiene la posicion del ultimo led que se encendera
                                            // ej int((35cm/10) -10) = |int(-6.5)| = 6, pos de led de 40cm
    Serial.print(distance,": ",pos, "\n");
    if(last_distance == distance) {
	// verificar que las distancias decimales no sean las mismas, porque esto no funcionaria
	// o se podria hacer una verificacion dependiendo que valor recibe cuando no choca con nada
	ledsOff(0);
    }
    else {
        ledsOff(pos);
    }

    if(distance <= max_distance) {
        // si la distancia es menor a 100 se encienden los leds
        ledsOn(pos);
        last_distance = distance;
	end_pos = init_pos = pos;
    }
}

void ledsOff(int pos) {
    //apago los leds que correspondan a una distancia menor a la posicion actual
    //for(int i = pos; i < lenLeds ; i++) {
    for(int i = pos; i < end_pos ; i++) { //probar con esta linea
        digitalWrite(ledPins[i], HIGH);
    }
}

void ledsOn(int pos) {
    for(int i = init_pos; i <= pos; i++) {
        digitalWrite(ledPins[i], LOW);
    }
}

float getDistance() {
    unsigned long time = pulseIn(ECHO, HIGH); // en microsegundos
    float distance = (time * vsound * 0.000001) / 2.00;
    delayMicroseconds(100);

    return distance;
}

void startTrigger() {
    // inicia trigger para comenzar a medir
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(2);

    digitalWrite(TRIGGER, LOW);
}

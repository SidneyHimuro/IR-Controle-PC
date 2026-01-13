#include <IRremote.h>

#define IR_PIN     2
#define PWR_PIN    8
#define PC_STATE   4

#define DESLIGAR_CLIQUES 3
#define TEMPO_MAX_MS     5000

// IR Control Mapping - Replace with your codes
// Use IRremote "ReceiveDump" example to find your remote's info
#define IR_PROTOCOL    NEC           // Protocol type (e.g., NEC, SONY, SAMSUNG)
#define IR_ADDRESS     0x00          // Place your Remote Address here
#define IR_COMMAND     0x00          // Place your Button Command here

unsigned long tempoInicio = 0;
int contadorCliques = 0;

void setup() {
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, LOW);

  pinMode(PC_STATE, INPUT);

  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {

  bool pcLigado = digitalRead(PC_STATE);

  if (IrReceiver.decode()) {

    // Check if the received signal matches your defined mapping
    if (
      IrReceiver.decodedIRData.protocol == IR_PROTOCOL &&
      IrReceiver.decodedIRData.address  == IR_ADDRESS  &&
      IrReceiver.decodedIRData.command  == IR_COMMAND  &&
      !(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)
    ) {

      // ===== PC OFF → 1 click turns it ON =====
      if (!pcLigado) {
        ligarPC();
        contadorCliques = 0;
      }

      // ===== PC ON → Count clicks to turn OFF =====
      else {
        registrarClique();
      }
    }

    IrReceiver.resume();
  }

  // Reset counter if time limit is reached
  if (contadorCliques > 0 && (millis() - tempoInicio > TEMPO_MAX_MS)) {
    contadorCliques = 0;
  }
}

// ================= FUNCTIONS =================

void registrarClique() {

  if (contadorCliques == 0) {
    tempoInicio = millis();
  }

  contadorCliques++;

  Serial.print("Cliques: ");
  Serial.println(contadorCliques);

  if (contadorCliques >= DESLIGAR_CLIQUES) {
    desligarPC();
    contadorCliques = 0;
  }
}

void ligarPC() {
  Serial.println("Ligando PC...");
  pressionarBotao(300);
}

void desligarPC() {
  Serial.println("Desligando PC...");
  pressionarBotao(300);
}

void pressionarBotao(int tempoMs) {
  digitalWrite(PWR_PIN, HIGH);
  delay(tempoMs);
  digitalWrite(PWR_PIN, LOW);
}
#include <IRremote.h>

#define IR_PIN     2
#define PWR_PIN    8
#define PC_STATE   4

#define DESLIGAR_CLIQUES 3
#define TEMPO_MAX_MS     5000

// Controle IR (NEC)
#define IR_ADDRESS 0x40
#define IR_COMMAND 0x53

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

    if (
      IrReceiver.decodedIRData.protocol == NEC &&
      IrReceiver.decodedIRData.address  == IR_ADDRESS &&
      IrReceiver.decodedIRData.command  == IR_COMMAND &&
      !(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)
    ) {

      // ===== PC DESLIGADO → 1 clique liga =====
      if (!pcLigado) {
        ligarPC();
        contadorCliques = 0;
      }

      // ===== PC LIGADO → contar cliques =====
      else {
        registrarClique();
      }
    }

    IrReceiver.resume();
  }

  // Reseta se estourar o tempo
  if (contadorCliques > 0 && millis() - tempoInicio > TEMPO_MAX_MS) {
    contadorCliques = 0;
  }
}

// ================= FUNÇÕES =================

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

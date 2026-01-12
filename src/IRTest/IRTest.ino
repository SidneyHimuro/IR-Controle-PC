#include <IRremote.h>

#define IR_PIN 2

void setup() {
  Serial.begin(9600);

  // Inicializa receptor IR
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("Leitor IR iniciado...");
  Serial.println("Pressione qualquer botao do controle");
}

void loop() {
  if (IrReceiver.decode()) {

    Serial.println("================================");

    Serial.print("Protocolo: ");
    Serial.println(IrReceiver.decodedIRData.protocol);

    Serial.print("Endereco: 0x");
    Serial.println(IrReceiver.decodedIRData.address, HEX);

    Serial.print("Comando: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    Serial.print("Raw (hex): 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      Serial.println("Repeticao do botao");
    }

    IrReceiver.resume();
  }
}

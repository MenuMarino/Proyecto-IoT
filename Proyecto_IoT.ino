#include <WiFi.h>
#include <PubSubClient.h>

// Credenciales de mi wifi
const char* ssid = "Benja-1";
const char* password = "Ut3c1836";
// Configuracion para MQTT
const char* mqttServer = "192.168.0.2"; // Ip local de mi pc, en donde se realiza el mosquitto_sub
const char* topic = "iot/p2";
const int mqttPort = 1883;

// Inicializamos las variables del WiFi y para realizar la comunicacion MQTT
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  // Conectar a wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(WiFi.status());
  }
  Serial.println(("\nConnected to the WiFi network"));

  // Conectar a mqtt broker
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(topic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }

  // publish y subscribe
  client.publish(topic, "1");
  client.subscribe(topic);
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length) {
  // Esta funcion es para enviarle mensajes al ESP-32, no ha sido utilizada
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");

  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }

  Serial.println();
  Serial.println(" - - - - - - - - - - - -");
}

void loop() {
  // Esto se llama para permitir que el cliente procese los mensajes entrantes y mantenga su conexión con el servidor
  client.loop();
  // Enviar la info del sensor
  publishData();
}

void publishData() {
  if (Serial.available()) {
    // Leer los datos enviados por el Arduino Mega
    int humedad = Serial.parseInt();

    // Enviar la informacion por internet a la computadora
    client.publish(topic, String(humedad).c_str());

    // Imprimir el valor en el monitor serial del ESP32
    Serial.print("Valor de humedad recibido: ");
    Serial.println(humedad);
  }
}

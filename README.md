# Proyecto-IoT
Proyecto del curso Internet de las cosas realizado en UTEC. 
El proyecto consiste en un sistema de irrigación automático con Arduino. 
Además de eso, se envia la informacion a traves del WiFi para poder visualizar los cambios en la humedad de la tierra.

## Integrantes
* Cristian Caballero
* Benjamin Diaz
* Rodrigo Céspedes
* Fabrizio Garcia

## Requerimientos
### Arduino
Para el codigo del ESP32 se necesita agregar el siguiente board en las preferencias

`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

Despues de eso, en el menu de Boards Manager buscamos esp32 (by Espressif) e instalamos la version 2.0.4.

### Python
Se necesita instalar las siguientes librerias, para poder graficar y recibir los datos a traves de mqtt.

`pip install matplotlib paho-mqtt`

import matplotlib.pyplot as plt
import paho.mqtt.client as mqtt

# Variable para almacenar los valores recibidos
data = []

# Función para actualizar la gráfica
def update_plot():
    fig, ax = plt.subplots()  # Crear una nueva figura y ejes
    ax.plot(data)
    ax.set_xlabel("Tiempo")
    ax.set_ylabel("Valor")
    ax.set_title("Gráfica de valores MQTT")
    ax.grid(True)
    plt.draw()  # Actualizar la gráfica
    plt.pause(0.1)  # Pequeña pausa para actualizar la gráfica
    plt.clf()

# Callback que se ejecuta al recibir un mensaje MQTT
def on_message(client, userdata, msg):
    value = float(msg.payload.decode())
    data.append(value)
    update_plot()

# Configuración del cliente MQTT
broker_address = "192.168.0.2"  # Dirección del broker MQTT
topic = "iot/p2"  # Tema MQTT para suscribirse

client = mqtt.Client()

# Asignar la función de callback al cliente MQTT
client.on_message = on_message

# Conexión al broker MQTT y suscripción al tema
client.connect(broker_address)
client.subscribe(topic)

# Crear la gráfica inicial
plt.figure()

# Mantenerse en un bucle infinito para recibir mensajes
client.loop_forever()

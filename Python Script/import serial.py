#/*******************************************************************************************************
#------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
#------------------------------------date : 13/04/2024------------------------------------------------
#------------------------------------função do programa: Salvar os dados
#*******************************************************************************************************/

import serial
import pandas as pd

# Configurações da porta serial
port = "COM11"  # Altere para a porta serial correta
baudrate = 9600
timeout = 5

# Inicialize a comunicação serial
ser = serial.Serial(port, baudrate, timeout=timeout)

# Leitura e processamento dos dados
data = []
while True:
    line = ser.readline().decode().strip()
    if line:  # Se houver dados
        values = [float(x) for x in line.split(",")]
        data.append(values)

# Crie um DataFrame pandas com os dados
df = pd.DataFrame(data, columns=["Temperature Thermocouple (C)", "Current (A)", "Temperature LM35 (C)"])

# Salve os dados em um arquivo Excel
df.to_excel("C:\Users\bruno\Documents\dados_coletados.csv", index=False)

# Feche a porta serial
ser.close()
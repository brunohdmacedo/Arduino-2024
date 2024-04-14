#/*******************************************************************************************************
#------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
#------------------------------------date : 13/04/2024------------------------------------------------
#------------------------------------função do programa: Salvar os dados Atualizar os dados
#*******************************************************************************************************/

import serial
import csv

# Abre a porta serial
arduino_port = 'COM11'  # Substitua 'COMX' pela porta serial do seu Arduino
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate)

# Abre o arquivo CSV para escrita
csv_file = open('C:\Users\bruno\Documents\dados_coletados.csv', 'w', newline='')
csv_writer = csv.writer(csv_file)

# Escreve o cabeçalho no arquivo CSV
csv_writer.writerow(['Temperatura Thermocouple (C)', 'Corrente (A)', 'Temperatura LM35 (C)'])

# Loop para ler dados da porta serial e gravá-los no arquivo CSV
try:
    while True:
        # Lê uma linha da porta serial
        serial_data = ser.readline().decode().strip()
        
        # Separa os valores
        data = serial_data.split(',')
        
        # Escreve os valores no arquivo CSV
        csv_writer.writerow(data)
        
        # Imprime os dados lidos
        print("Temperatura Thermocouple:", data[0], "C")
        print("Corrente:", data[1], "A")
        print("Temperatura LM35:", data[2], "C")
        print()
except KeyboardInterrupt:
    # Fecha a porta serial e o arquivo CSV ao pressionar Ctrl + C
    ser.close()
    csv_file.close()

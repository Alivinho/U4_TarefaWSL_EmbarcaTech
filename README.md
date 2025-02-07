# Projeto: Controle de LEDs e Display OLED com Raspberry Pi Pico

## Descrição
Este projeto implementa um sistema de controle utilizando o Raspberry Pi Pico, integrando uma matriz de LEDs WS2812, um display OLED SSD1306 e dois LEDs RGB, controlados por botões. A comunicação é feita via UART, permitindo a entrada de caracteres para exibição no display ou na matriz de LEDs.

## Funcionalidades
- Leitura de caracteres via UART
- Exibição de caracteres no display OLED SSD1306
- Acionamento de uma matriz de LEDs WS2812 para exibição de números
- Controle de LEDs RGB por meio de botões com debounce
- Indicação visual no display OLED ao pressionar os botões

## Hardware Utilizado
- Raspberry Pi Pico
- Matriz de LEDs WS2812 (5x5)
- Display OLED SSD1306 (I2C)
- Dois botões para interação
- Dois LEDs RGB (Azul e Verde)

## Pinos Utilizados
- **UART**:
  - TX: GPIO 0
  - RX: GPIO 1
- **Botões**:
  - Botão A: GPIO 5
  - Botão B: GPIO 6
- **LEDs RGB**:
  - Azul: GPIO 12
  - Verde: GPIO 11
- **Matriz WS2812**: GPIO 7
- **Display OLED SSD1306**:
  - SDA: GPIO 14
  - SCL: GPIO 15

## Configuração e Execução
### 1. Instalação das Dependências
Certifique-se de que as bibliotecas necessárias estão instaladas no seu ambiente de desenvolvimento para o Raspberry Pi Pico.

### 2. Compilação e Upload
Compile o código e faça o upload para o Raspberry Pi Pico utilizando o SDK do Pico e um ambiente como o VS Code ou o terminal.

### 3. Interação
- Envie um caractere pela UART para exibi-lo no display OLED.
- Pressione os botões para alternar o estado dos LEDs RGB.
- Envie um número (0-9) para exibi-lo na matriz de LEDs WS2812.




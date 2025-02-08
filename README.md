# Controle de LEDs e Display OLED com Raspberry Pi Pico na Placa Bitdoglab

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
### 1. Instalar Dependências
Certifique-se de que o **Pico SDK** e as bibliotecas necessárias estão instaladas no ambiente de desenvolvimento.

### 2. Compilar e Fazer o Upload
- Utilize um ambiente como **VS Code + CMake** ou um terminal para compilar o código.
- Converta o arquivo "main.c" para um arquivo **UF2** e transfira para o Raspberry Pi Pico.

### 3. Como Usar
- **Enviar um caractere via UART** → Exibe no **display OLED**.
- **Pressionar os botões** → Alterna o estado dos **LEDs RGB** e exibe feedback no display.
- **Enviar um número (0-9) pela UART** → Exibe o número na **matriz de LEDs WS2812**.

- Se necessário, ajuste os **endereços I2C** do display OLED no código.
a alternar o estado dos LEDs RGB.
- Envie um número (0-9) para exibi-lo na matriz de LEDs WS2812.




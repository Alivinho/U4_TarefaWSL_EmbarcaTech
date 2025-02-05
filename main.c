#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

// Definição de Pinos do LED RGB
#define LED_RED_PIN 13
#define LED_BLUE_PIN 12
#define LED_GREEN_PIN 11

// Definição de Pinos dos Botões
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6


#define WS2812_PIN 7
#define IS_RGBW false
#define NUM_PIXELS 25

//extern void animacao_1(PIO pio, uint sm, uint numero_atual);

// Protótipos das Funções utilizadas
void initLedButtons();

static volatile uint numero_atual = 0;   // Variável para armazenar o número atual

const uint32_t BRIGHTNESS = 0xCC; // Ajusta o brilho aqui (0x00 para apagado, 0xFF para brilho máximo)

// Acionamento da matriz de LEDs - ws2812b
/*void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
       pio_sm_put_blocking(pio, sm, (desenho[24-i]) * BRIGHTNESS); 
    }
}*/


int main() {

    stdio_init_all();

    initLedButtons();
    

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);



    //animacao_1(pio, sm, numero_atual);

    while (1){

    }

    return 0;
}

void initLedButtons(){
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
}
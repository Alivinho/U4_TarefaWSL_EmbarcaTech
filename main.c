#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define WS2812_PIN 7
#define IS_RGBW false
#define NUM_PIXELS 25

extern void animacao_1(PIO pio, uint sm, uint numero_atual);


static volatile uint numero_atual = 0;   // Variável para armazenar o número atual

const uint32_t BRIGHTNESS = 0xCC; // Ajusta o brilho aqui (0x00 para apagado, 0xFF para brilho máximo)

// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
       pio_sm_put_blocking(pio, sm, (desenho[24-i]) * BRIGHTNESS); 
    }
}


int main() {
    stdio_init_all();
    

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);



    animacao_1(pio, sm, numero_atual);

    while (1){

    }

    return 0;
}
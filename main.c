#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "hardware/i2c.h"
#include "includes/ssd1306.h"
#include "includes/font.h"

// Definição de Pinos do LED RGB
#define LED_RED_PIN 13
#define LED_BLUE_PIN 12
#define LED_GREEN_PIN 11

// Definição de Pinos dos Botões
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

// Matriz de LEDS
#define WS2812_PIN 7
#define IS_RGBW false
#define NUM_PIXELS 25

// Display Oled - SSD1306
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

extern void animacao_1(PIO pio, uint sm, uint numero_atual);

// Protótipos das Funções utilizadas
void initLedButtons();

const uint32_t BRIGHTNESS = 0xCC; // Ajusta o brilho aqui (0x00 para apagado, 0xFF para brilho máximo)

// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
       pio_sm_put_blocking(pio, sm, (desenho[24-i]) * BRIGHTNESS); 
    }
}


int main() {

    stdio_init_all();

    initLedButtons();
    
    // Configuração do PIO e da Matriz de LED
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Configuração (Inicialuzação) do Display Oled
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL); 
    ssd1306_t ssd; 
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(&ssd); 
    ssd1306_send_data(&ssd);

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);


    bool cor = true;
    while (true){
        cor = !cor;

        if (stdio_usb_connected()){
            char caractere;

            printf("Digite um caractere ou número: ");
            scanf(" %c", &caractere);

            if (caractere >= '0' && caractere <= '9') {
                // Se for um número (0 a 9), exibe na matriz WS2812
                uint numero_atual = (uint)(caractere - '0');  // Converte diretamente o caractere para inteiro

                animacao_1(pio, sm, numero_atual);
            } 
        }
        // Atualiza o conteúdo do display com animações
        ssd1306_fill(&ssd, !cor); // Limpa o display
        ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
        //ssd1306_draw_char(&ssd,'A', 8, 10);
        ssd1306_draw_string(&ssd, "CARACTERE", 8, 10); // Desenha uma string
        //ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30); // Desenha uma string
        //ssd1306_draw_string(&ssd, "PROF WILTON", 15, 48); // Desenha uma string      
        ssd1306_send_data(&ssd); // Atualiza o display

        sleep_ms(1000);
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


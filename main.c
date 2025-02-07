#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "hardware/i2c.h"
#include "includes/ssd1306.h"
#include "includes/font.h"

// Definição dos Pinos e taxa de transmissão da  UART
#define UART_ID uart0    
#define BAUD_RATE 115200 
#define UART_TX_PIN 0    
#define UART_RX_PIN 1    

// Definição de Pinos do LED RGB
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
ssd1306_t ssd; 

// Definição dos variáveis para controle da Rotina de Interrupção
#define DEBOUNCE_DELAY 200  
volatile uint32_t last_interrupt_timeA = 0;
volatile uint32_t last_interrupt_timeB = 0;

// Função para dese
extern void animacao_1(PIO pio, uint sm, uint numero_atual);

// Protótipos das Funções utilizadas
void initLedButtons();
void button_callback(uint gpio, uint32_t events);
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho);
void exibir_caractere_no_display(char caractere);

const uint32_t BRIGHTNESS = 0xCC; // Ajusta o brilho aqui (0x00 para apagado, 0xFF para brilho máximo)


int main() {

    stdio_init_all();

    initLedButtons();

    // Configuração (Inicialização) da UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
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
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(&ssd); 
    ssd1306_send_data(&ssd);

    // Chamada de funções para Interrupção dos botões 
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    bool cor = true;

    // Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    // Desenha o retângulo uma única vez
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);  // Desenha o retângulo (com cor)
    ssd1306_draw_string(&ssd, "ESPERANDO...", 25, 30); // Desenha uma string        
    ssd1306_send_data(&ssd);  // Atualiza o display

    while (true){
        cor = !cor;

        if (stdio_usb_connected()){
            char caractere;

            printf("Digite um caractere ou número:\n");
            scanf(" %c", &caractere);

            if (caractere >= '0' && caractere <= '9') {
                // Se for um número (0 a 9), exibe na matriz WS2812
                uint numero_atual = (uint)(caractere - '0');  // Converte diretamente o caractere para inteiro

                animacao_1(pio, sm, numero_atual);
            }else{
                exibir_caractere_no_display(caractere);
            }
        }

        //ssd1306_draw_string(&ssd, "EMbARCATECH", 20, 30); // Desenha uma string        
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

    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
}


// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
       pio_sm_put_blocking(pio, sm, (desenho[24-i]) * BRIGHTNESS); 
    }
}

// Funão da rotina de interrupção 
void button_callback(uint gpio, uint32_t events) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A_PIN) {
        if (tempo_atual - last_interrupt_timeA < DEBOUNCE_DELAY ) return;
        last_interrupt_timeA = tempo_atual;
        static bool led_state_a = false;
        led_state_a = !led_state_a;
        gpio_put(LED_GREEN_PIN, led_state_a);
        
        printf("\nBotão A pressionado: LED Verde %s", led_state_a ? "LIGADO" : "DESLIGADO");
       
        ssd1306_fill(&ssd, false);  
        ssd1306_draw_string(&ssd, led_state_a ? "LED VERDE ON" : "LED VERDE OFF", 18, 30);
        ssd1306_send_data(&ssd);  
    }
    else if (gpio == BUTTON_B_PIN) {
        if (tempo_atual - last_interrupt_timeB < DEBOUNCE_DELAY ) return;
        last_interrupt_timeB = tempo_atual;
        static bool led_state_b = false;
        led_state_b = !led_state_b;
        gpio_put(LED_BLUE_PIN, led_state_b);

        printf("\nBotão B pressionado: LED Azul %s", led_state_b ? "LIGADO" : "DESLIGADO");

        ssd1306_fill(&ssd, false);  
        ssd1306_draw_string(&ssd, led_state_b ? "LED AZUL ON" : "LED AZUL OFF", 18, 30);
        ssd1306_send_data(&ssd); 

    }
}

void exibir_caractere_no_display(char caractere){

    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);  // Desenha o retângulo (com cor)
    ssd1306_draw_char(&ssd, caractere, 62, 32);
    ssd1306_send_data(&ssd); // Atualiza o display

}


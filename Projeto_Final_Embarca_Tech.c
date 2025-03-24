// declaração das bibliotecas utilizadas no codigo
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "display_init.h"
#include "pio_matrix.pio.h"
#include "frames.h"
#include "config_leds.h"


#define BUZZER_PIN 21 // Buzzer A, está conectado - através de um transistor - no GPIO21 da Raspberry pi pico
#define MATRIZ_PIN 7 // A matriz de LED's está conectado ao GPIO07
#define BTA 05 // O botão A está conectado ao GPIO5
#define BTB 06 // O botão B está conectado ao GPIO6

// O led verde e azul estão conectados no GPIO 11 e 12 respectivamente
#define LED_VERDE 11
#define LED_AZUL 12

#define BUZZER_FREQUENCIA 100 // definindo uma frequencia padrão para o buzzer

// definindo as frequencias das notas musicais 
#define DO_FREQUENCIA 262
#define RE_FREQUENCIA 294
#define MI_FREQUENCIA 330
#define FA_FREQUENCIA 349



// Preparar área de renderização para o display
struct render_area frame_area = {
    start_column : 0, // Coluna inicial da área de renderização 
    end_column : ssd1306_width - 1, // Última coluna da área (largura total do display - 1)
    start_page : 0, // Página inicial 
    end_page : ssd1306_n_pages -1 // Última página (altura maxima do display dividida por 8)
};


// função para iniciar o PWM do pino do buzzer
void pwm_init_buzzer(uint pin, uint frequencia, uint intensidade) {
    // configurando o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(pin); // obter o slice do pino
    uint channel = pwm_gpio_to_channel(pin); // obter o canal do pino

    //configurar o PWM com a frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequencia * 4096));
    pwm_init(slice, &config, true);


    pwm_set_gpio_level(pin, 0); // iniciar o PWM no nível baixo
    pwm_set_chan_level(slice, channel, intensidade); // define a itensidade do som
}

// função para emitir o som com duração e intensidade especificada
void beep(uint pin, uint duration_ms, uint intensidade) {
    
    uint slice = pwm_gpio_to_slice_num(pin); // obter o slice do pino
    uint channel = pwm_gpio_to_channel(pin); // obter o canal do pino


    pwm_set_gpio_level(pin, intensidade); //define o nível do PWM


    sleep_ms(duration_ms);

    
    pwm_set_chan_level(slice, channel, 0); //define o duty cicle do canal

    
    sleep_ms(100); 
}

// Função para escrever no display
void escrever(char *text) {

    // Calcula o tamanho do buffer necessário para renderizar a área do display
    calculate_render_area_buffer_length(&frame_area);
    
    uint8_t ssd[ssd1306_buffer_length]; // Cria um buffer para armazenar os dados da tela   
    memset(ssd, 0, ssd1306_buffer_length); // Zera o buffer (limpa a tela temporariamente)
    render_on_display(ssd, &frame_area); // Renderiza o buffer vazio no display para limpar a área

    char *texto[] = {text}; // Armazena o texto em um array de ponteiros para strings

    int y = 0; // Define a posição inicial no eixo Y (altura)

    // Percorre o array de texto e escreve cada string no display
    for (uint i = 0; i < count_of(texto); i++)
    {
        ssd1306_draw_string(ssd, 5, y, texto[i]); // Escreve o texto na posição (5,y)
        y += 8; // Avança 8 pixels para evitar sobreposição do texto
    }

    // Atualiza o display com o novo conteúdo do buffer
    render_on_display(ssd, &frame_area);
}

void clear_display() {
    uint8_t ssd[ssd1306_buffer_length]; // Cria um buffer para armazenar os dados da tela
    memset(ssd, 0, ssd1306_buffer_length); // Preeche o buffer com zeros para apagar o conteúdo da tela
    render_on_display(ssd, &frame_area); // Renderiza o buffer vazio no display

}


int main()
{
    
    stdio_init_all(); // inicializar o sistema de saída padrão
    init_display(); // Inicialização do i2c
    ssd1306_init(); // Processo de inicialização completo do OLED SSD1306


    // inicializando os Botões e configurando como tipo de entrada
    gpio_init(BTA);
    gpio_set_dir(BTA, GPIO_IN);
    gpio_pull_up(BTA);
    gpio_init(BTB);
    gpio_set_dir(BTB, GPIO_IN);
    gpio_pull_up(BTB);

    // inicializando os LEDS e configurandos como tipo de saida
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    
    PIO pio = pio0;
    uint32_t valor_led;
    double r = 0.0, g = 0.0, b = 0.0;
    bool ok;
    ok = set_sys_clock_khz(128000, false); // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock



    // Configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program); // offset recebe o endereço de memória onde o programa foi alocado
    uint sm = pio_claim_unused_sm(pio, true); // reservando uma máquina de estados
    pio_matrix_program_init(pio, sm, offset, MATRIZ_PIN); // inicialização do programa na sm
       
    escrever("");

    while (true) {
        // se o botão A for precionado
        if(gpio_get(BTA) == 0) {

            gpio_put(LED_VERDE, 1); // O LED Verde é ligado

            setar_leds_verde(leds[2], valor_led, pio, sm, r, g, b);

            // chama função para iniciar o PWM do pino do buzzer
            pwm_init_buzzer(BUZZER_PIN, DO_FREQUENCIA, 2048);

            escrever("NOTA DO"); // Escreve a nota DÓ no display


            
            // chama a função para emitir o som com duração e intensidade especificada
            beep(BUZZER_PIN, 500, 2048); // toca a nota Dó
            
            sleep_ms(300); // Uma pausa de 0,3 segundos, para chamar a proxima nota musical

            clear_display();

            // é chamado novamente a função de inicialização do pino e a itensidade é aumentada
            pwm_init_buzzer(BUZZER_PIN,RE_FREQUENCIA, 3072); 
            escrever("NOTA RE"); // Escreve a nota RÉ no display
            beep(BUZZER_PIN, 500, 3072); // toca a nota Ré
            sleep_ms(300);
            clear_display();
            gpio_put(LED_VERDE, 0);

            setar_leds_verde(leds[0], valor_led, pio, sm, r, g, b);

            // Pausa de 0,2 segundos para evitar efeito bouncing
            sleep_ms(200); 
        }
        
        if(gpio_get(BTB) == 0) {
            gpio_put(LED_AZUL, 1); // o LED Azul é ligado

            setar_leds_azul(leds[1], valor_led, pio, sm, r, g, b);

            // chama função para iniciar o PWM do pino do buzzer
            pwm_init_buzzer(BUZZER_PIN, MI_FREQUENCIA, 3584);

            escrever("NOTA MI"); // Escreve a nota MI no display

            // chama a função para emitir o som com duração e intensidade especificada
            beep(BUZZER_PIN, 500, 3584); // toca a nota Mi
            
            sleep_ms(300);

            clear_display();

            // é chamado novamente a função de inicialização do pino e a itensidade é aumentada
            pwm_init_buzzer(BUZZER_PIN,FA_FREQUENCIA, 4096);
            escrever("NOTA FA"); // Escreve a nota FÁ no display
            beep(BUZZER_PIN, 500, 4096); // toca a nota Fá
            sleep_ms(300);
            clear_display();
            gpio_put(LED_AZUL, 0);

            setar_leds_azul(leds[0], valor_led, pio, sm, r, g, b);

            // Pausa de 0,2 segundos para evitar efeito bouncing
            sleep_ms(200);
        }

        

    }
    return 0;
}

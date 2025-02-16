// declaração das bibliotecas utilizadas no codigo
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"



#define BUZZER_PIN 21 // Buzzer A, está conectado - através de um transistor - no GPIO21 da Raspberry pi pico
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

int main()
{
    // inicializar o sistema de saída padrão
    stdio_init_all();

    // inicializando os Botões e configurando como tipo de entrada
    gpio_init(BTA);
    gpio_set_dir(BTA,false);
    gpio_pull_up(BTA);
    gpio_init(BTB);
    gpio_set_dir(BTB,false);
    gpio_pull_up(BTB);

    // inicializando os LEDS e configurandos como tipo de saida
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    while (true) {
        // se o botão A for precionado
        if(gpio_get(BTA) == 0) {
            gpio_put(LED_VERDE, 1); // O LED Verde é ligado

            // chama função para iniciar o PWM do pino do buzzer
            pwm_init_buzzer(BUZZER_PIN, DO_FREQUENCIA, 2048);

            // chama a função para emitir o som com duração e intensidade especificada
            beep(BUZZER_PIN, 500, 2048); // toca a nota Dó
            sleep_ms(300); // Uma pausa de 0,3 segundos, para chamar a proxima nota musical

            // é chamado novamente a função de inicialização do pino e a itensidade é aumentada
            pwm_init_buzzer(BUZZER_PIN,RE_FREQUENCIA, 3072); 
            beep(BUZZER_PIN, 500, 3072); // toca a nota Ré 
            sleep_ms(100);
            gpio_put(LED_VERDE, 0);

            // Pausa de 0,2 segundos para evitar efeito bouncing
            sleep_ms(200); 
        }
        
        if(gpio_get(BTB) == 0) {
            gpio_put(LED_AZUL, 1); // o LED Azul é ligado

            // chama função para iniciar o PWM do pino do buzzer
            pwm_init_buzzer(BUZZER_PIN, MI_FREQUENCIA, 3584);

            // chama a função para emitir o som com duração e intensidade especificada
            beep(BUZZER_PIN, 500, 3584); // toca a nota Mi
            sleep_ms(300);

            // é chamado novamente a função de inicialização do pino e a itensidade é aumentada
            pwm_init_buzzer(BUZZER_PIN,FA_FREQUENCIA, 4096);
            beep(BUZZER_PIN, 500, 4096); // toca a nota Fá
            sleep_ms(100);
            gpio_put(LED_AZUL, 0);

            // Pausa de 0,2 segundos para evitar efeito bouncing
            sleep_ms(200);
        }
    }
    return 0;
}

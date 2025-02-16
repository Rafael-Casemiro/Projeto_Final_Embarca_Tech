# 🎵 Projeto: Controle de Buzzer com Raspberry Pi Pico W

## 📌 Descrição
Este projeto utiliza um **buzzer piezoelétrico** e **botões** conectados ao **Raspberry Pi Pico W** para gerar sons musicais diferentes conforme a interação do usuário. O sistema utiliza **PWM (Modulação por Largura de Pulso)** para controlar a frequência e a intensidade das notas sonoras.

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C
- **Microcontrolador:** Raspberry Pi Pico W
- **Bibliotecas:**
  - `pico/stdlib.h` (Funções padrão do SDK)
  - `hardware/pwm.h` (Controle do PWM)
  - `hardware/clocks.h` (Configuração do clock do sistema)

## ⚙️ Hardware Necessário
- Raspberry Pi Pico W
- Buzzer Piezoelétrico
- 2 Botões Push-Button
- LED
- Resistores de Pull-Up

## 🛠️ Configuração do Circuito
1. Conecte o **buzzer** ao **GPIO 21**.
2. Conecte os **botões** aos pinos **GPIO 5 (BTA)** e **GPIO 6 (BTB)**.
3. Utilize resistores de **pull-up internos** para os botões.
4. Conecte os **LEDS indicadores** ao **GPIO 11** e **GPIO 12**.

## 📜 Estrutura do Código
O código principal está estruturado da seguinte forma:
- **Inicialização do hardware**: Configura os botões como entrada com pull-up e define o PWM no buzzer.
- **Função `pwm_init_buzzer(pin, frequencia)`**: Inicializa o PWM no pino do buzzer para gerar a nota desejada.
- **Função `beep(pin, duration_ms)`**: Emite um som pelo buzzer durante um determinado tempo.
- **Loop principal**: Verifica o estado dos botões e emite diferentes notas e intensidades de som.

## 🔧 Instalação e Compilação
### 1️⃣ Configurar o ambiente de desenvolvimento
Certifique-se de que você tem o **SDK do Raspberry Pi Pico** configurado.

### 3️⃣ Carregar no Raspberry Pi Pico W
- Conecte a placa ao PC via **USB** segurando o botão **BOOTSEL**.
- Copie o arquivo **`.uf2`** gerado para a unidade USB do Pico.

## 🎮 Como Usar
- Pressione **BTA (GPIO 5)** para tocar **notas Dó e Ré**.
- Pressione **BTB (GPIO 6)** para tocar **notas Mi e Fá**.
- O LED pisca durante a execução das notas.

## 📌 Melhorias Futuras
- Adicionar mais notas musicais.
- Criar melodias automáticas.
- Implementar controle de intensidade dinâmico.


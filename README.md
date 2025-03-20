# 🎵 Projeto: Controle de Buzzer com Raspberry Pi Pico W


<br/>
<div align="center">
  <h3 align="center">Controle de Buzzer com Raspberry Pi Pico W</h3>

  <p align="center">
    Um projeto com Raspberry Pi Pico para controle de uma matriz de LEDs, buzzer e botões interativos.
    <br/>
    ·
    <a href="https://www.youtube.com/">Vídeo Demonstrativo</a>
  </p>
</div>


## Índice
- [Sobre o Projeto](#sobre-o-projeto)
- [Construído com](#construído-com)
- [Recursos](#recursos)
- [Começando](#começando)
- [Pré-requisitos](#pré-requisitos)
- [Tecnologias Utilizadas](#uso)
- [Uso](#uso)
- [Instalação](#instalação)
- [Melhorias](#contribuindo)


## 📌 Sobre o Projeto

Este projeto foi desenvolvido para controlar uma matriz de LEDs e emitir notas musicais utilizando um buzzer, LEDs e um display OLED SSD1306. Ele foi feito para ser executado em uma Raspberry Pi Pico (ou uma placa similar baseada no RP2040), utilizando a biblioteca Pico SDK para controle de hardware.

### 🔧 Construído com

* [Raspberry Pi Pico C/C++ SDK](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)
* [PIO (Programmable I/O)](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html#programmable-io)
* CMake

---

## 🎯 Recursos

✔️ Raspberry Pi Pico W (RP2040): A placa de desenvolvimento usada  
✔️ Reprodução de **notas musicais** no **Buzzer** (GPIO21)  
✔️ **Botões físicos** para interação:  
   - **Botão A** (GPIO5) → Ativa sequência de notas (Dó, Ré)  
   - **Botão B** (GPIO6) → Ativa sequência de notas (Mi, Fá)  
✔️ **Display OLED SSD1306** para exibição
✔️ **Matriz de LEDs** para exibir efeitos de luz

---

## ⚙️ Pré-requisitos

- **Hardware necessário:**
  - Raspberry Pi Pico W
  - Matriz de LEDs 
  - Buzzer Piezoelétrico 
  - Display OLED  
  - Botões físicos para controle

- **Software necessário:**
  - Raspberry Pi Pico SDK
  - CMake
  - Compilador ARM GCC
  - Ferramentas de build (Ninja ou Make)

---

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C
- **Microcontrolador:** Raspberry Pi Pico W
- **Bibliotecas:**
  - `pico/stdlib.h` (Funções padrão do SDK)
  - `hardware/pwm.h` (Controle do PWM)
  - `hardware/clocks.h` (Configuração do clock do sistema)
  - `ssd1306.h` (Biblioteca para controlar o display OLED)
  - `hardware/i2c.h` (Controlador I2C)
  - `hardware/pwm.h` (Controlador PWM)
  - `display_init` (Funções de inicialização do display)
  - `pio_matrix.pio.h` (Código para controlar a matriz de LEDs via PIO)
  - `frames.h` (Configurações específicas para a matriz de LEds)
  - `config_leds.h` (Arquivos com configurações específicas para a matriz de LEDs)

## 🎮 Como Usar
- Pressione **BTA (GPIO 5)** para tocar **notas Dó e Ré**.
- Pressione **BTB (GPIO 6)** para tocar **notas Mi e Fá**.

---

## 🔧 Instalação e Compilação

1️⃣ Clone o repositório:
   ```
   git clone •	https://github.com/Rafael-Casemiro/Projeto_Final_Embarca_Tech
   ```
2️⃣ Navegue até o diretório do projeto:
   ```sh
   cd seu-repositorio
   ```
3️⃣ Crie e entre no diretório `build`:
   ```sh
   mkdir build && cd build
   ```
4️⃣ Gere os arquivos de build com CMake:
   ```sh
   cmake ..
   ```
5️⃣ Compile o projeto:
   ```sh
   make
   ```
6️⃣ Envie o arquivo `.uf2` para a Raspberry Pi Pico W.

---

## 📌 Melhorias Futuras
- Adicionar mais notas musicais.
- Adicionar suporte a múltiplos buzzers.



   


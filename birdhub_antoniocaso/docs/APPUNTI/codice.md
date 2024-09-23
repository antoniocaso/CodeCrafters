# Stampa in loop

```python
# loop forever
while True:
    # print something
    print("Hello Zerynth!")
    # sleep 1 second
    sleep(1000)

```

# Led Blink
1. Si importa il modulo *board* dal "board support package" chiamato *bsp*. Il modulo *board* contiene nomi specifici, variabili e impostazioni in maniera che questo progetto sia portabile su diverso hardware zerynth.
2. Si importa il modulo *gpio* per il controllo dei pin GPIO.
3. Creiamo una funzione python chiamata *blink* che* accende e spegne un led con un certo ritardo.
4. Facciamo partire due thread, i parametri sono: il nome della funzione seguito dalla lista di parametri.
5. I due thread sono eseguiti indipendentemente, il che consente di gestire blinking di led diversi.

LED_BLUE e LED_GREEN sono costanti contenute in *bsp* e fanno riferimento o a dei pin GPIO
L'avvio dei thread dev'essere eseguito una volta, per cui questo si trova al di fuori di un loop. 

La funzione *gpio.toggle()* fa passare dallo stato LOW allo stato HIGH il pin.

```python
from bsp import board

import gpio

def blink(led, delay):
    while True:
        sleep(delay)
        gpio.toggle(led)

thread(blink, LED_BLUE, 1000)
thread(blink, LED_GREEN, 2000)

```

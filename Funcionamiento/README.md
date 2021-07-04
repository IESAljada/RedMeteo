# Funcionamiento

[<p align="center"><img src="videos/portada_video.png" width="500"/></p>](https://www.youtube.com/watch?v=M3VhcBCXWJw)


## Anemómetro
Nuestro anemometro consiste en tres "cucharas" imprimidas con la impresora 3D del instituto unidas a un pequeño motor

Se trata de un motor que funciona como una dinamo que emite una variacion de voltage que se ha mapeado para dar los valores lo mas reales posibles . Básicamente para poder ajustar se ha hecho lo siguiente: se ha cogido un anemómetro profesional a una distancia X de una fuente de viento, se ha utilizado un compresor de aire para que siempre sople con la misma fuerza y al lado el anemómetro de la estación a la misma distancia ; se registran los datos (el voltage obtenido del anemómetro de la estación con la velocidad obtenida en uno profesional).


## Veleta
La veleta funciona con un potenciómetro efecto hall rotativo por lo que cada posición tiene un voltaje
 distinto que va desde 0 hasta – 5 voltios. El programa mapea estos datos para asociar el valor de voltaje
 a  un valor previamente calibrado con una brújula. 
También se ha calibrado para que el centro de masas se encuentre en el eje del sensor. 

### Explicación de programación.
1. Establecemos las variables a utilizar. Las que vayan acompañadas de “#define” serán aquellas asociadas al arduino y las que vayan con “float” serán utilizadas en el programa cuyos valores serán expresados con números decimales.
1. Dentro de la estructura  “voidsetup” determinaremos los comandos que deberán activarse para iniciar el programa. De esta forma arduino enviará la señal de “inicializando”..
1. Creamos una función que llamaremos “HacerLecturas”. El programa lee el valor analógico del sensor y lo transformará mediante la función mapeo el voltaje recibido del potenciómetro en grados norte. Al valor obtenido se le dará la variable “direccion”. Los valores de voltaje preestablecidos son calibrados mediante una brújula.
1. Dentro de la estructura “voidloop” el programa ejecutará la función “HacerLecturas” y ésta escribirá en el monitor los datos recibidos. Finalmente al usar el comando “Seria.println” los datos aparecerán separados por espacios.
### Explicación del funcionamiento.
La veleta funciona con un potenciómetro efecto hall rotativo por lo que cada posición tiene un voltaje distinto que va desde 0 hasta – 5 voltios. 
El programa mapea estos datos para asociar el valor de voltaje a  un valor previamente calibrado. 
También se ha calibrado para que el centro de masas se encuentre en el eje del sensor. 

## Pluviómetro
El pluvionetro tiene la función de medir la cantidad de agua acumulada por superficie durante las precipitaciones. El agua de la lluvia se almacena en una especie de depósito y al estar este lleno se vacia y se inclina para que el otro depósito se vuelva a llenar y así sucesivamente mientras llueva. Por medio de varias funciones del arduino en el que se asignan variables, se puede puede programar una ecuación, mediante un sensor magnético se mide la diferencia de voltaje entre el tiempo, atraves de una ecuación podemos calcular la precipitación en "mm/h". 

Comenzamos definiendo la función #define, la cual,  es un componente útil que permite al programador dar un nombre a un valor constante antes de compilar el programa, en este caso es "PLUVIOMETRO_IN" con un valor de 2.
Proseguimos asignando las variables "lluvia" , "tiempo1" y "tiempo2"  como un valor float, es decir, un valor que posee decimales.
Ahora, nos adentramos en la función setup. El setup es la primera función en ejecutarse dentro de un programa en Arduino. Es, básicamente, donde se "setean" las funciones que llevará a cabo el microcontrolador. En primer lugar, llamamos al monitor serie mediante la función "Serial.begin()", con un valor de 9600 bps. Después ordenamos a la Arduino a escribir “Inicializando…” mediante el comando Serial.println(). Seguimos asignando el pin al que vamos a conectar el controlador que vamos a utilizar, en este caso, un sensor magnético, que lo vamos a conectar en el pin 2, definido anteriormente, e interrumpimos el pluviómetro mediante el comando INPUT_PULLUP.

Seguimos con la función "calcular_lluvia", en la que por su propio  nombre indica, es una función creada para calcular el nivel de lluvia.
En esta función, comenzamos igualando la variable "tiempo2" a la función "millis()" , la cual asigna el tiempo medido en la variable "tiempo2" a milisegundos.

Ahora hemos utilizado un condicional para calcular la lluvia: Si el tiempo2 es mayor que el tiempo1 y restando el tiempo2 menos el tiempo1 es mayor o igual a 120, entonces:

Escribimos el valor de "tiempo1" y el de "tiempo2". Tras esto realizamos la ecuación de la lluvia:  *lluvia = 6*158.57*3600/(tiempo2-tiempo1)*

Tras haber realizado esta ecuación,  imprimimos su valor en el monitor serie, acompañado de su medida "mm/h". E igualamos los tiempos, "tiempo1 = tiempo2".

El pluviómetro mide la cantidad de lluvia en función del tiempo aplicando la fórmula anterior. En el interior del pluviometro tenemos implantado un  sensor magnético que mide la diferencia de voltaje entre el tiempo,  que cuando se llena una parte del cubo, se vacía y en el tiempo que tarda en bajar detecta ese tiempo y lo implementa en la ecuación para calcular la lluvia.


## Sensor de temperatura y humedad (DHT11)
El DHT11 es un sensor de temperatura y humedad que dispone de una salida calibrada a una señal digital.
 Este dispositivo puede medir la temperatura de un área dada, y para hacer un mayor rendimiento de esa área, lo hemos cambiado de lugar a una caja ventilada, para tener una medida lo más precisa posible. En esta caja también estará el arduino.

Respecto a la programación utilizamos librerías como el comando "#define DHT_PINS "y los comandos "Serial.print", "Serial.println" y "read" para que el arduino lea y envie estos datos.


# Temporizador para ejercicios
Trabajo práctico N°2 del curso online de Sistemas Embebidos

## Datos
- Alumno: Fernando Augusto Gonzalez
- Correo electrónico: ferauzalez@gmail.com

## Aspectos generales
- Este proyecto fue planteado como un subsistema de un reloj para gimnasios. El subsistema consiste en dos temporizadores (tiempo de ejercitación y descanso) que se
repiten un determinado número de veces (repeticiones). Tanto la cuenta inicial de los temporizadores como el número de series está definida por el usuario.
- En la idea de proyecto no se aclaró que el display a utilizar es de cuatro dígitos y siete segmentos. En los sucesivos trabajos prácticos se usará uno como el de [éste link](https://articulo.mercadolibre.com.ar/MLA-912188513-display-7-segmentos-4-digitos-056-rojo-arduino-catodo-comun-_JM#position%3D5%26search_layout%3Dgrid%26type%3Ditem%26tracking_id%3D843cb5e5-9544-4f3b-b1cc-106021ec19cf)

## Lineamientos del trabajo práctico N°2

De acuerdo al correo de Ariel, los lineamientos del correspondiente TP son:
- Modularización en archivos (acorde a lo que se ve en el capítulo 5)
- Buen uso de variables y funciones públicas y privadas (cap. 5)
- Diseño con bajo acoplamiento y alta cohesión (ver capítulo 5)
- Máquina de estado finito (al menos una, acorde al capítulo 4)

## Requerimientos
Los siguientes requerimientos vienen del TP1:
1. Contar con los siguientes tres estados: Espera, Incrementar y Decrementar.
2. Poder seleccionar, mediante un botón, el valor inicial del parámetro a configurar. Ya sea el temporizador 1, temporizador 2 ó el número de repeticiones. La acción de presionar dicho botón debe estar asociada al encendido/apagado de tres LEDs. Un LED corresponderá al temporizador 1 (tiempo de ejercitación), otro al temporizador 2 (tiempo de descanso) y otro al número de repeticiones. Al presionar el botón se debe encender un LED y apagar los demás; esto permite al usuario saber qué valor inicial quedó seleccionado para configurar
3. Incrementar el valor inicial del parámetro seleccionado mediante un pulsador
4. Decrementar el valor inicial del parámetro seleccionado mediante un pulsador. No decrementar por debajo del cero.
5. Iniciar el temporizador de ejercitación mediante la pulsación de un botón. Si la cuenta regresiva está iniciada, pausarla mediante la pulsación del mismo botón.
6. Al finalizar el tiempo de ejercitación, iniciar la cuenta regresiva del temporizador de descanso.
7. Al finalizar el temporizador de descanso, decrementar el número de repeticiones en una unidad e iniciar el temporizador de ejercitación.
8. Al finalizar el número de repeticiones, permanecer en estado de espera.
9. Informar al usuario mediante puerto serie del estado en el que se encuentra el subsistema y de los valores de los temporizadores

## Descripción
### Módulos
En este trabajo práctico se agregó el uso de módulos. En total se usó 6 carpetas para clasificarlos:
- microcontroller: Agrega la lógica que comanda el uso de recusos del microcontrolador que no sean entradas digitales. Para esta presentación se agrega sólo la funcionalidad de delay pero posteriormente se puede incliuir el uso de reloj de tiempo real.
- button: Agrega la lógica que comanda las entradas digitales.
- led: Agrega la lógica que comanda el comportamiento de los led (estar prendidos o parpadeando)
- user interface: Es donde irían los módulos relacionados con la interfaz de usuario. Para esta presentación se agrega el módulo __uart__ que gobierna la comunicación por puerto serie. Posteriormente se podría incluir el módulo del display de cuatro dígitos de siete segmentos.
- FSM: Es donde irían las máquinas de estado. Para esta presentación se encuentra la máquina "principal" que gobierna los estados por lo que navega el usuario al presionar los botones.
- timer: Agrega la lógica del reloj.

El diagrama de módulos, funciones y variables se presenta a continuación. Se recomienda abrir el archivo de la imagen que se encuentra en el repositorio para una mejor visiualización. Se agregan dos imagenes, una con formato _.png_ y la otra con formato _.svg_ por si se desesa ampliar sin perder resolución. En este diagrama se puede ver a qué funciones llama una determinada función, qué variables usa y una clasificación entre funciones públicas y privadas entre otros datos.

![diagrama de módulos, funciones y variables](https://github.com/ferauzalez/ARMBookCurso2024_TP1/blob/develop/Curso%20ARMBook%202024%20-%20Diagrama%20de%20modulos%2C%20funciones%20y%20variables.png)

### Máquina de estados
En esta presentación del trabajo práctico se incluye una máquina de estados llamada "principal", cuyo diagrama se presenta a continuación. Se recomienda abrir el archivo de la imagen que se encuentra en el repositorio para una mejor visiualización. Se agregan dos imagenes, una con formato _.png_ y la otra con formato _.svg_ por si se desesa ampliar sin perder resolución.

![FSM Principal](https://github.com/ferauzalez/ARMBookCurso2024_TP1/blob/develop/Curso%20ARMBook%202024%20-%20FSM%20Principal.png)


En [este enlace](https://youtu.be/fCFSCCyr1Co) se encuentra el video de demostración. La salida por puerto serie que se muestra en el video, se muestra en el bloque siguiente:

```
Opened with baud rate: 115200
MODE: Exercise
00 : 10
MODE: Rest
00 : 05
MODE: Repetitions
00 : 03
MODE: Repetitions
00 : 03
MODE: Repetitions
00 : 02
MODE: Repetitions
00 : 02
MODE: Exercise
00 : 10
MODE: Exercise
00 : 09
MODE: Exercise
00 : 08
MODE: Exercise
00 : 07
MODE: Exercise
00 : 06
MODE: Exercise
00 : 05
MODE: Exercise
00 : 04
MODE: Exercise
00 : 03
MODE: Exercise
00 : 02
MODE: Exercise
00 : 01
MODE: Exercise
00 : 00
MODE: Rest
00 : 04
MODE: Rest
00 : 03
MODE: Rest
00 : 02
MODE: Rest
00 : 01
MODE: Rest
00 : 00
MODE: Repetitions
00 : 01
MODE: Exercise
00 : 09
MODE: Exercise
00 : 08
MODE: Exercise
00 : 07
MODE: Exercise
00 : 06
MODE: Exercise
00 : 05
MODE: Exercise
00 : 04
MODE: Exercise
00 : 03
MODE: Exercise
00 : 02
MODE: Exercise
00 : 01
MODE: Exercise
00 : 00
MODE: Rest
00 : 04
MODE: Rest
00 : 03
MODE: Rest
00 : 02
MODE: Rest
00 : 01
MODE: Rest
00 : 00
MODE: Repetitions
00 : 00
------------------------------
COUNTDOWN IS FINISHED!
------------------------------
MODE: Exercise
00 : 00
```

## Discusión
- Se observa en la salida por puerto serie que al modificar el valor de repeticiones, se muestra cuatro veces el valor. Se replica a continuación para más claridad:
```
MODE: Repetitions
00 : 03
MODE: Repetitions
00 : 03
MODE: Repetitions
00 : 02
MODE: Repetitions
00 : 02
```
- Al presionar el botón _BUTTON_SELECT_MODE_ la máquina de estados pasa del estado _WAITING_ al estado _SELECT_MODE_. Una de las salidas de ese estado es mostrar el valor actual del modo seleccionado. Entonces se obtiene
```
MODE: Repetitions 
00 : 03
```
* Luego al presionar el botón BUTTON_DECREASE la máquina de estados pasa del estado _SELECT_MODE_ al estado _WAITING_, y como resultado se vuelve a mostrar el valor del modo actual (el último seleccionado).
```
MODE: Repetitions 
00 : 03
```
* Desde el estado  _WAITING_, al presionar el botón BUTTON_DECREASE (nótese que es la segunda vez que el usuario debe presionar), la máquina de estados pasa al estado _DECREASE_. Se descuenta efectivamente el valor. se obtiene por puerto serie:
```
MODE: Repetitions 
00 : 02
```
* Desde el estado _DECREASE_, al presionar el botón _BUTTON_SELECT_MODE_, la máquina de estados pasa del estado _DECREASE_ al estado _WAITING_, y finalmente se obtiene por puerto serie:
```
MODE: Repetitions 
00 : 02
```
Lo que sigue en el video de demostración es el evento de presionar el botón _BUTTON_PLAY_PAUSE_, con el que se inicia la cuenta regresiva.

### Sobre los requerimientos
- En esta presentación se cumplen con los requermientos originales del TP 1, del 1 al 8.
- El requerimiento N°9 (el último)
  > Informar al usuario mediante puerto serie del estado en el que se encuentra el subsistema y de los valores de los temporizadores
  no se cumple, debido a que para esta presentación se usa el puerto serie para presentar los valores actualizados del modo seleccionado e informar los valores de los tres modos _ensuciaría_ la consola y podría llevar a confusión al usuario. 

## Conclusiones
- Se incluyó modificaciones al TP1 de acuerdo a los lineamientos propuestos.
- Estos cambios tuvieron por objetivo refactorizar el código. Por ello, [En el video de demostración del presente trabajo](https://youtu.be/fCFSCCyr1Co) se observa un comportamiento similar al [correspondiente del TP1](https://youtu.be/J5sgj14au_0).
- El comportamiento descripto anteriormente en la sección __discusión__, se replica de forma similar cuando el usuario intenta incrementar o decrementar el tiempo de ejercicio y de descanso. Y eso se debe a dos cuestiones. La primera es que la función _main()_ actualiza la máquina de estados sólo cuando la lectura de los botones devuelve un valor que se corresponda con algunos de los botones conectados a la protoboard, por defecto permanece en el estado _WAITING_. La segunda es la forma en la que se realizó el diseño de la máquina de estados. Visto este comportamiento, noté que se pueden realizar mejoras en el diseño, por ejemplo eliminando el estado _WAITING_ o usando interrupciones cuando se presiona un botón. Sucedió  que costó mucho tiempo entender el tema de máquinas de estados y realizar el diseño, a la vez que se debió reacomodar el proyecto usando módulos. Entonces para no dilatar más la entrega se presenta ésta versión del diseño con la posibilidad de realizar mejoras si es necesario.

## Notas
### Modificaciones sobre el TP1
Antes de iniciar con el trabajo práctico N°2 se agregó los requerimientos al *Readme*. Además  se incluyó el link faltante en la oración "Se incluyó la clase _Ticker_ para llamar la función que hace el descuento. Más información sobre la clase en éste __link__"
### Referencias
- [Idea de proyecto](https://drive.google.com/file/d/1E1HMZ6O3roSUBYhBtxat7gXWZ-FmFl0v/view)
- Además de los comentarios sobre el trabajo práctico. Cualquier otro comentario sobre cómo mejorar la redacción del informe también es bienvenido.


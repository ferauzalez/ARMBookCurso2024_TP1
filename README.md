# Temporizador para ejercicios
Trabajo práctico N°1 del curso online de Sistemas Embebidos

## Datos
- Alumno: Fernando Augusto Gonzalez
- Correo electrónico: ferauzalez@gmail.com

## Aspectos generales
- Este proyecto fue planteado como un subsistema de un reloj para gimnasios. El subsistema consiste en dos temporizadores (tiempo de ejercitación y descanso) que se
repiten un determinado número de veces (repeticiones). Tanto la cuenta inicial de los temporizadores como el número de series está definida por el usuario.
- En la idea de proyecto no se aclaró que el display a utilizar es de cuatro dígitos y siete segmentos. En los sucesivos trabajos prácticos se usará uno como el de [éste link](https://articulo.mercadolibre.com.ar/MLA-912188513-display-7-segmentos-4-digitos-056-rojo-arduino-catodo-comun-_JM#position%3D5%26search_layout%3Dgrid%26type%3Ditem%26tracking_id%3D843cb5e5-9544-4f3b-b1cc-106021ec19cf)

## Requerimientos
1. Contar con los siguientes tres estados: Espera, Incrementar y Decrementar.
2. Poder seleccionar, mediante un botón, el valor inicial del parámetro a configurar. Ya sea el
temporizador 1, temporizador 2 ó el número de repeticiones. La acción de presionar dicho
botón debe estar asociada al encendido/apagado de tres LEDs. Un LED corresponderá al
temporizador 1 (tiempo de ejercitación), otro al temporizador 2 (tiempo de descanso) y otro al
número de repeticiones. Al presionar el botón se debe encender un LED y apagar los demás;
esto permite al usuario saber qué valor inicial quedó seleccionado para configurar
3. Incrementar el valor inicial del parámetro seleccionado mediante un pulsador
4. Decrementar el valor inicial del parámetro seleccionado mediante un pulsador. No decrementar
por debajo del cero.
5. Iniciar el temporizador de ejercitación mediante la pulsación de un botón. Si la cuenta regresiva
está iniciada, pausarla mediante la pulsación del mismo botón.
6. Al finalizar el tiempo de ejercitación, iniciar la cuenta regresiva del temporizador de descanso.
7. Al finalizar el temporizador de descanso, decrementar el número de repeticiones en una unidad
e iniciar el temporizador de ejercitación.
9. Al finalizar el número de repeticiones, permanecer en estado de espera.
10. Informar al usuario mediante puerto serie del estado en el que se encuentra el subsistema y de
los valores de los temporizadores

## Descripción
- Se debe iniciar el puerto serie con un baud rate de 115200.
- El ingreso a los comandos se realiza mediante los botones montados en protoboard.
- La acciones a seguir, para usar sistema (en un modo general) son: Seleccionar el tiempo de ejercitación > Configurar la cuenta > Seleccionar el tiempo de descanso > Configurar la cuenta > Seleccionar el número de repeticiones > Configurar la cuenta > Iniciar la cuenta regresiva (pausarla y reanudarla si es necesario)
- Los LEDs indican el modo seleccionado y además, cuando la cuenta regresiva está activa, el parpadeo de los mismos indica qué modo está descontándose en ese momento. La idea es que al tener un sólo display de 7 segmentos, con la ayuda de los LEDs el usuario sepa qué tiempo es el que se muestra mediante el display.
- Se simuló el display de 4 dígitos de 7 segmentos con el puerto serie, indicando en cada impresión de pantalla el modo que se seleccionó previamente (esto simula el encedido de uno de tres LEDs posibles).
- Se incluyó la clase Ticker para llamar la función que hace el descuento. Más información sobre la clase en éste [link](https://os.mbed.com/docs/mbed-os/v6.16/apis/ticker.html)
- Se implementó los estados del sistema sin seguir una estructura definida. Esto fue debido a que, para el trabajo práctico N°2, se pretende incluir conceptos de máquinas de estados, de acuerdo a una sugerencia hecha por Ariel en la idea de proyecto.

## Imágenes

Vista lateral
![vista lateral](https://github.com/ferauzalez/ARMBookCurso2024_TP1/assets/55369433/9dfa8a28-6b24-4f2b-8b43-528acfc6abfb)

Vista superior
![vista superior](https://github.com/ferauzalez/ARMBookCurso2024_TP1/assets/55369433/35b737f6-098f-48fa-a950-dabd1439650e)


## Conclusiones
- El trabajo práctico N°1 cumple con los requerimientos propuestos en la idea de proyecto. Se puede visualizar el funcionamiento del sistema en [éste link](https://youtu.be/J5sgj14au_0).

## Referencias
- [Idea de proyecto](https://drive.google.com/file/d/1E1HMZ6O3roSUBYhBtxat7gXWZ-FmFl0v/view)


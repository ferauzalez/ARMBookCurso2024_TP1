# Temporizador para ejercicios
Trabajo práctico N°1 del curso online de Sistemas Embebidos

## Datos
- Alumno: Fernando Augusto Gonzalez
- Correo electrónico: ferauzalez@gmail.com

## Aspectos generales
- Este proyecto fue planteado como un subsistema de un reloj para gimnasios. Los requerimientos de éste proyecto se encuentran en la [idea de proyecto](https://drive.google.com/file/d/1E1HMZ6O3roSUBYhBtxat7gXWZ-FmFl0v/view)
- En la idea de proyecto no se aclaró que el display a utilizar es de cuatro dígitos y siete segmentos. En los sucesivos trabajos prácticos se usará uno como el de [éste link](https://articulo.mercadolibre.com.ar/MLA-912188513-display-7-segmentos-4-digitos-056-rojo-arduino-catodo-comun-_JM#position%3D5%26search_layout%3Dgrid%26type%3Ditem%26tracking_id%3D843cb5e5-9544-4f3b-b1cc-106021ec19cf)

## Descripción
- Se debe iniciar el puerto serie con un baud rate de 115200.
- El ingreso a los comandos se realiza mediante los botones montados en protoboard.
- La acciones a seguir, para usar sistema (en un modo general) son: Seleccionar el tiempo de ejercitación > Configurar la cuenta > Seleccionar el tiempo de descanso > Configurar la cuenta > Seleccionar el número de repeticiones > Configurar la cuenta > Iniciar la cuenta regresiva (pausarla y reanudarla si es necesario)
- Los LEDs indican el modo seleccionado y además, cuando la cuenta regresiva está activa, el parpadeo de los mismos indica qué modo está descontándose en ese momento. La idea es que al tener un sólo display de 7 segmentos, con la ayuda de los LEDs el usuario sepa qué tiempo es el que se muestra mediante el display.
- Se simuló el display de 4 dígitos de 7 segmentos con el puerto serie, indicando en cada impresión de pantalla el modo que se seleccionó previamente (esto simula el encedido de uno de tres LEDs posibles).
- Se incluyó la clase Ticker para llamar la función que hace el descuento. Más información sobre la clase en éste link
- Se implementó los estados del sistema sin seguir una estructura definida. Esto fue debido a que, para el trabajo práctico N°2, se pretende incluir conceptos de máquinas de estados, de acuerdo a una sugerencia hecha por Ariel en la idea de proyecto.

## Imágenes

Vista lateral
![vista lateral](https://github.com/ferauzalez/ARMBookCurso2024_TP1/assets/55369433/9dfa8a28-6b24-4f2b-8b43-528acfc6abfb)

Vista superior
![vista superior](https://github.com/ferauzalez/ARMBookCurso2024_TP1/assets/55369433/35b737f6-098f-48fa-a950-dabd1439650e)


## Conclusiones
El trabajo práctico N°1 cumple con los requerimientos propuestos en la idea de proyecto. Se puede visualizar el funcionamiento del sistema en [éste link](https://youtu.be/J5sgj14au_0).


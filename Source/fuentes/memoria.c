/*
/**
 * 
 * PUNTOS CLAVE DE UTILIZACION DE LA FLASH
 * 
 * - El monitor de VDD tiene que estar habilitado cuando se esta escribiendo o borrando la flash
 * - Deshabilitar las interrpupciones globales antes de setear PSWE a 1
 * - Hay que tener cuidado con los modelos de memoria Large y Compact, porque usan xdata y pdata para 
 * variables de usuario, y ambos generan codigos de escritura MOVX
 * - Secuencias Lock y Key deben generarse antes de cada operacion de escritura o borrado.
 * - intentos de escritura, lectura o borrado de secciones de memoria localizadas en espacio reservado
 * generaran un reset del dispositivo
 * - El CPU se detiene en las operaciones de lectura y escritura de la flash, pero los dispositivos perifericos
 * siguen andando
 * - Las interrupciones que surgen durante una operacion de escritura o borrado se pospondran hasta que se
 * complete la operacion
 * - La pagina de la flash que contiene el o los bytes del Lock no se pueden borrar desde el codigo de 
 * aplicacion
 * 
 * 
 * Para escribir en la memoria flash se usa la instruccion MOVX. Por defecto, esta instruccion carga datos
 * en la XRAM, pero cambiando el registro PSCTL se puede modificar para que escriba en la Flash. Las
 * instrucciones MOVX se generan en C usando punteros de memoria de tipo xdata o pdata.
 * 
 * Solo se puede escribir en memoria habiendo borrado todo antes. La instruccion de escritura solo puede poner
 * bits en 0
 */
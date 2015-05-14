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
 */
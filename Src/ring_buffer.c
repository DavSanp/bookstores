
#include "ring_buffer.h"

#define capacity (8)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;
uint8_t is_full;

/*
 * @brief Esta funcion calcula los datos disponibles en el buffer
 *
 * @retval size: cantidad de datos disponibles
 */
uint8_t ring_buffer_size(void)
{
	uint8_t size = 0;
	if (head_ptr > tail_ptr) {
		size = head_ptr - tail_ptr;
	} else {

	}
}


/**
 * @brief Esta funcion resetea el buffer
 */
 void ring_buffer_reset(void)
 {
	 is_full = 0;
	 tail_ptr = 0;
	 head_ptr = 0;
 }

 /**
  * @brief Esta funcion verifica si el buffer esta lleno (1 lleno y 0 vacio )
  */
  uint8_t ring_buffer_is_full(void)
  {
 	 return (head_ptr == tail_ptr && !is_full);
  }

  /**
    * @brief Esta funcion verifica si el buffer esta vacio (1 vacio y 0 lleno )
    */
    uint8_t ring_buffer_is_full(void)
    {
   	 return ((head_ptr + 1)% capacity) == tail_ptr;
    }
/**
 * @brief Esta funcion escribe un dato en el buffer circular
 *
 * @param data: el dato que se va a escribir
 *
 * @retval Ninguno
 */
void ring_buffer_write(uint8_t data)
{
	ring_buffer[head_ptr] = data;
	head_ptr = head_ptr + 1;

	if (head_ptr >= capacity) { // si la cabeza llega al final de la memoria
	  head_ptr = 0;
	}

	if (is_full != 0) { // si se pierden datos viejos
	  tail_ptr = tail_ptr + 1;
	}

	if (tail_ptr >= capacity) { // si la cola llega al final de la memoria
	  tail_ptr = 0;
	}

	if (head_ptr == tail_ptr) { // si la cabeza alcanza la cola
	  is_full = 1;
	}
}

/**
 * @brief Esta funcion lee un dato del buffer circular
 *
 * @param data: la direccion de donde se va a escribir el dato
 *
 * @retval 1: hay datos disponibles, 0: no hay datos
 */
uint8_t ring_buffer_read(uint8_t *data) // 0x20
{
	if ((is_full != 0) || (head_ptr != tail_ptr)) { // data available
		*data = ring_buffer[tail_ptr]; // add: 0x20, val: buffer
		tail_ptr = tail_ptr + 1;
		if (tail_ptr >= capacity) {
			tail_ptr = 0;
		}
		is_full = 0;

		return 1; // buffer con datos
	}
	return 0; // buffer vacio
}


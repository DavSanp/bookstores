
#include "ring_buffer.h"


void ring_buffer_init(ring_buffer_t *rb, uint8_t * mem_add, uint8_t cap)
{
	rb->buffer = mem_add;
	rb->capacity = cap;

	ring_buffer_reset();
}

/*
 * @brief Esta funcion reinicia los datos disponibles en el buffer
 *
 * @retval size: cantidad de datos disponibles
 */
void ring_buffer_reset(ring_buffer_t *rb)
{
	rb->head = 0;
	rb->tail = 0;
	rb->is_full = 0;
}

/*
 * @brief Esta funcion calcula los datos disponibles en el buffer
 *
 * @retval size: cantidad de datos disponibles
 */
uint8_t ring_buffer_size(void)
{
	uint8_t size = 0;
	if (head_ptr >= tail_ptr && is_full == 0) {
		size = head_ptr - tail_ptr;
	} else {
		size = (capacity - tail_ptr) + head_ptr;
	}
	return size;
}

/*
 * @brief Esta funcion revisa si el buffer esta lleno
 *
 * @retval is_full: 0 si no esta lleno, 1 si esta lleno
 */
uint8_t ring_buffer_is_full(void)
{
	return is_full;
}

/*
 * @brief Esta funcion revisa si el buffer esta vacio
 *
 * @retval 0 si esta vacio, 1 si no esta vacio
 */
uint8_t ring_buffer_is_empty(void)
{
	return ((head_ptr == tail_ptr) && (is_full == 0)) ? 1 : 0;
}

/**
 * @brief Esta funcion escribe un dato en el buffer circular
 *
 * @param data: el dato que se va a escribir
 *
 * @retval Ninguno
 */
void ring_buffer_write(ring_buffer_t *rb, uint8_t data)
{
	rb->buffer[rb->head] = data;
	rb->head = rb->head + 1;

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


/*
 * ring_buffer.h
 *
 *  Created on: Aug 16, 2024
 *      Author: saaci
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>

void ring_buffer_reset(void);
uint8_t ring_buffer_size(void);
uint8_t ring_buffer_is_full(void);
uint8_t ring_buffer_is_empty(void);

void ring_buffer_write(uint8_t data);
uint8_t ring_buffer_read(uint8_t *byte);

#endif /* INC_RING_BUFFER_H_ */

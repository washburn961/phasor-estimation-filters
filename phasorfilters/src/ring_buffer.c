#include "ring_buffer.h"

// Initializes the ring buffer (assumes content is already allocated)
uint32_t ring_buffer_init(ring_buffer* buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->is_full = 0;

    for (uint32_t i = 0; i < buffer->size; i++) {
        buffer->content[i] = 0;
    }

    return 0;
}

// Writes data to the ring buffer
uint32_t ring_buffer_write(ring_buffer* buffer, float data) {
    buffer->content[buffer->head] = data;
    buffer->head = (buffer->head + 1) % buffer->size;

    if (buffer->is_full) {
        buffer->tail = (buffer->tail + 1) % buffer->size;
    }

    buffer->is_full = (buffer->head == buffer->tail);

    return 0;
}

// Reads data from the ring buffer at a specified index
uint32_t ring_buffer_read(ring_buffer* buffer, float* out_data, uint32_t index) {
    if (!buffer->is_full && index >= buffer->head) {
        return 1; // Error: Trying to read more data than available
    }

    uint32_t actual_index = (buffer->head + buffer->size - index - 1) % buffer->size;
    *out_data = buffer->content[actual_index];

    return 0;
}

// Reads multiple elements from the ring buffer
uint32_t ring_buffer_read_many(ring_buffer* buffer, float* out_data, uint32_t out_size) {
    if (out_size > buffer->size || (!buffer->is_full && out_size > buffer->head)) {
        return 1; // Error: Trying to read more data than available
    }

    for (uint32_t i = 0; i < out_size; i++) {
        ring_buffer_read(buffer, &out_data[i], i);
    }

    return 0;
}
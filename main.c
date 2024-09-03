#include <stdio.h>
#include "ring_buffer.h"

// Define buffer content and initialize ring buffer structure
float buffer_content[8] = { 0 };
ring_buffer buffer = {
    .size = 8,
    .content = buffer_content
};

void print_buffer(ring_buffer* buffer) {
    float out_data[8];
    uint32_t out_size = buffer->is_full ? buffer->size : buffer->head;

    ring_buffer_read_many(buffer, out_data, out_size);

    for (uint32_t i = 0; i < out_size; i++) {
        printf("%0.0f ", out_data[i]);
    }
    printf("\n");
}

int main(void) {
    // Initialize the ring buffer
    ring_buffer_init(&buffer);

    // Write data from 1 to 32 into the ring buffer
    for (int i = 1; i <= 32; i++) {
        ring_buffer_write(&buffer, (float)i);
        printf("After writing %d: ", i);
        print_buffer(&buffer);
    }

    return 0;
}

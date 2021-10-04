#include "stdio.h"
#include "string.h"

// change me
#define AVAILABLE_SLOTS 4                                           // should be 512 for ESP32
#define SLOT_TYPE char                                              // char: 1 byte => 8 bit

// better don't change me
#define AVAILABLE_BITS_MASK ((1 << (sizeof(SLOT_TYPE) * 8)) - 1)    // 1 byte -> 8 bit -> ((1 << 8) - 1) -> 11111111
SLOT_TYPE arr[AVAILABLE_SLOTS];                                     // dummy array, should be esp32's eeprom "width"

//
void distribute(long val);

long collect();

void increment();
//

int main(void) {
    printf("size: %d\n", sizeof(char));

    // store an int32 number
    long val = 1 << 30;
    distribute(val);
    printf("val: %ld\n", val);

    // collect an int32 number
    long out = collect();
    printf("out: %ld\n", out);

    // check if everything worked
    if (val != out) {
        printf("WARN :: value mismatch. %ld != %ld\n", val, out);
    }

    distribute(123);
    increment();
    printf("inc: %ld\n", collect());

    return 0;
}

void distribute(long val) {
    memset(arr, 0, AVAILABLE_SLOTS * sizeof(SLOT_TYPE));
    for (int i = 0; val != 0;) {
        arr[i++] = (SLOT_TYPE) (val & AVAILABLE_BITS_MASK);
        val >>= sizeof(SLOT_TYPE) * 8;
    }
}

long collect() {
    long res = 0;
    for (int i = AVAILABLE_SLOTS - 1; i >= 0; i--) {
        if (res == 0 && arr[i] == 0) { // skip blank bits
            continue;
        }
        res = res << (sizeof(SLOT_TYPE) * 8) | (arr[i] & AVAILABLE_BITS_MASK);
    }
    return res;
}

void increment() {
    distribute(collect() + 1);
}

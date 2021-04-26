
#include "sys/etimer.h"
#include "sys/ctimer.h"
#include "sys/clock.h"
#include "tiny-AES128-C/aes.c"

#include <stdio.h>
#include <stdint.h>

#define LOOP INTERVAL
#define CBC 1
#define SECOND 1000000

static struct etimer et;
static struct ctimer timer;

volatile bool status = false;

void dump( uint8_t ∗ str , unsigned long size ){
    for(int i = 0; i < size; i++){
        printf ("%.2x", str [ i ]) ;
    }
    printf ("\n") ;
}
static void process_task(void *ptr){
    unsigned long time_start;
    unsigned long time_stop;
    unsigned long cycles;



    const uint8_t SIZE = 16 ∗ 7; // 128 bytes , 1024 bits
    const uint16_t PAYLOADSIZE = SIZE ∗ 8;

    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7 , 0x15, 0x88, 0x09, 0xcf , 0x4f , 0x3c};
    uint8_t iv [] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    uint8_t in[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a, 0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51, 0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,0xf6 , 0x9f , 0x24, 0x45, 0xdf , 0x4f , 0x9b, 0x17,0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10,0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,0xf6 , 0x9f , 0x24, 0x45, 0xdf , 0x4f , 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10}; 
    uint8_t in [2048] = {0};
    uint8_t out[2048] = {0};



    printf ("Size : %d\n", PAYLOADSIZE) ;
    dump(out, SIZE);


    time_start = RTIMERNOW() ;

    uint16_t TRIALS = 100;
    for(int i = 0; i < TRIALS; i++){
        AES_CBC_encrypt_buffer(out, in, SIZE, key, iv);
    }

    time_stop = RTIMERNOW() ;
    cycles = time_stop - time_start;
    printf("POST out: ");
    dump(out, SIZE);
    printf("START: %lu\n", time_start);
    printf("STOP: %lu\n", time_stop);
    printf ("cycles , rtimer second : %lu %d\n", cycles , RTIMER_SECOND) ;
}
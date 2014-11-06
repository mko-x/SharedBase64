//
//  base64sqrl_decode.c
//  Base64SQRL
//
//  Created by Markus Kosmal on 05/11/14.
//
//
#include "base64sqrl.h"
#include "base64sqrl_shared.h"

/**
 *  Alphabet for decoding
 */
static const unsigned char a_decoding[256] =
{
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1,
    
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63,
    
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

/**
 *  Alphabet legend
 */
static const int a_ignore = -1;

/**
 *  Status legend
 */
static const int s_err = -1;
static const int s_initial_byte = 0;

static const int s_second_byte = 1;
static const int s_third_byte = 2;

static const int s_emit_bytes = 3;
static const int s_all_read = 4;

static int end_size;
/**
 *  Calculate expected length of output data
 *
 *  @param input_length of string
 *
 *  @return estimated length
 */
int decode_out_length(int input_length){
    return input_length / 3 * 4;
}

/**
 *  The decoding function.
 *
 *  Will try to decode all data in a rush at first.
 *  That will work in 99% of the executions if source data contains no-data bytes like whitespace.
 *
 *  If rushing didn't work will work with stateful byte for byte analyzing.
 *
 *  @param data          source data to decode
 *  @param input_length  of source data
 *  @param output_length estimated output length
 *
 *  @return decoded byte array of source data or NULL if illegal data was found
 */
unsigned char* decode_do(const char* source,
                         int source_length,
                         int *target_length) {
    
    // allocate some memory if possible
    unsigned char *target = malloc(*target_length);
    if (target == NULL) return NULL;
    
    // initalize working variables
    int state = 0;
    int work = 0;
    int tp = 0; //target byte position pointer
    
    // decoding main loop
    // sp is source byte position pointer
    for (int sp = 0; sp < source_length;) {
        
        // try a rush with guessing there is no no-data byte
        // we will try that for all following bytes after starting a new triple
        if(state == s_initial_byte){
            work = -1;
            while (sp+4 <= source_length) {
                work = (a_decoding[source[sp] & 0xff] << bg6_3) |
                (a_decoding[source[sp+1] & 0xff] << bg6_2) |
                (a_decoding[source[sp+2] & 0xff] << bg6_1) |
                (a_decoding[source[sp+3] & 0xff]);
                if(work >= 0){
                    target[tp+2] = work;
                    target[tp+1] = (work >> bg8_1);
                    target[tp] = (work >> bg8_2);
                    tp += 3;
                    sp += 4;
                }
            }
            if(sp >= source_length) break;
        }
        
        int q = a_decoding[source[sp++] & 0xff];
        
        // analyze current byte
        switch (state) {
            case s_initial_byte:
                if(q >= 0){
                    work = q;
                    ++state;
                }
                else if(q != a_ignore){
                    state = s_err;
                    return NULL;
                }
                break;
            case s_second_byte:
                if(q >= 0){
                    work = (work << bg6_1) | q;
                    ++state;
                }
                else if(q != a_ignore){
                    state = s_err;
                    return NULL;
                }
                break;
            case s_third_byte:
                if(q >= 0){
                    work = (work << bg6_1) | q;
                    ++state;
                }
                else if(q != a_ignore){
                    state = s_err;
                    return NULL;
                }
                break;
            case s_emit_bytes:
                if(q >= 0){
                    work = (work << bg6_1) | q;
                    
                    target[tp+2] = work;
                    target[tp+1] = (work >> bg8_1);
                    target[tp] = (work >> bg8_2);
                    tp += 3;
                    state = 0;
                }
                else if(q != a_ignore){
                    state = s_err;
                    return NULL;
                }
                break;
            case s_all_read:
                if(q != a_ignore){
                    state = s_err;
                    return NULL;
                }
                break;
            default: //illegal state
                state = s_err;
                return NULL;
                break;
        }
        
    }
    
    // FINISH HIM! check end status
    switch(state){
        case 1: //one more byte left, cannot emit output byte -> fail
            return NULL;
        case 2: //two more bytes left, add one more output byte
            target[tp++] = (work >> 4);
            break;
        case 3: //three more bytes left, add two more output bytes
            target[tp++] = (work >> 10);
            target[tp++] = (work >> 2);
        case 4: //read all + padding -> fine
        case 0: //read all -> fine
            break;
        default: //illegal state
            return NULL;
    }
    
    *target_length = tp;
    
    return target;
}

/**
 *  Decode base64 string to byte array.
 *
 *  @param data         source data
 *  @param input_length length of source data
 *
 *  @return a byte array of encoded source
 */
unsigned char* decode(const char* data, int input_length, int *out_length){
    *out_length = decode_out_length(input_length);
    if(out_length <= 0){
        return NULL;
    }
    unsigned char* output = decode_do(data, input_length, out_length);
//    if(sizeof(output) == out_length){
//        return output;
//    }
//    for(int i = 0; i <)
    return output;
}

///
//
#include "base64sqrl.h"
#include "base64sqrl_shared.h"

static const char t_encoding[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '-', '_'
};

int encode_out_length(int input_length){
    int out = input_length / 3 * 4;
    
    switch (input_length % 3) {
        case 0: break;
        case 1: out += 2; break;
        case 2: out += 3; break;
    }
    return out;
}

char* encode_do(const unsigned char *data,
                    int input_length,
                    int output_length) {
    
    char *encoded_data = malloc(output_length);
    if (encoded_data == NULL) return NULL;
    
    //main encoding loop
    //sp - sourcepointer
    //tp - targetpointer
    for (int sp = 0, tp = 0; sp < input_length;) {
        
        int work = -1;
        
        // 3 bytes left
        if(sp+3 <= input_length){
        
            int octet_a = (unsigned char)data[sp++];
            int octet_b = (unsigned char)data[sp++];
            int octet_c = (unsigned char)data[sp++];
            
            work = ((octet_a & 0xff) << bg8_2)
                                | ((octet_b & 0xff) << bg8_1)
                                | (octet_c & 0xff);
            
            encoded_data[tp++] = t_encoding[(work >> bg6_3) & 0x3F];
            encoded_data[tp++] = t_encoding[(work >> bg6_2) & 0x3F];
            encoded_data[tp++] = t_encoding[(work >> bg6_1) & 0x3F];
            encoded_data[tp++] = t_encoding[work & 0x3F];
        }
        else{
            if(sp == input_length - 1){
                work = (unsigned char) (data[sp++] & 0xff) << 4;
                encoded_data[tp++] = t_encoding[(work >> bg6_1) & 0x3f];
                encoded_data[tp++] = t_encoding[work & 0x3f];
            }
            else if (sp == input_length -2){
                int octet_a = (unsigned char)data[sp++];
                int octet_b = (unsigned char)data[sp++];
                work = ((octet_a & 0xff) << 10) |
                        ((octet_b & 0xff) << 2);
                
                encoded_data[tp++] = t_encoding[(work >> bg6_2) & 0x3f];
                encoded_data[tp++] = t_encoding[(work >> bg6_1) &0x3f];
                encoded_data[tp++] = t_encoding[work & 0x3f];
            }
        }
    }
    
    return encoded_data;
}

char* encode(const unsigned char* data, int input_length){
    int out_length = encode_out_length(input_length);
    return encode_do(data, input_length, out_length);
}

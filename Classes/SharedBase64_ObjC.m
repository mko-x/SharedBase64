//
//  Base64SqrlCoding.m
//  Base64
//
//  Created by Markus Kosmal on 03/11/14.
//
//

#import "SharedBase64_ObjC.h"

extern char* encode(const unsigned char* data,
                    int input_length,
                    int *output_length);

extern unsigned char* decode(const char* encoded,
                             int input_length,
                             int *output_length);

extern int request_size(int key);

@implementation Base64SqrlCoding

static NSStringEncoding _encType = NSASCIIStringEncoding;

/**
 *  Encode a byte array to a base64 representing string.
 *
 *  @param data byte array to encode
 *
 *  @return base64 encoded string representation of input
 */
+(NSString *) encodeDataToBase64: (NSData *) data{
    int outsize = -1;
    char* rawOut = encode([data bytes], (int) data.length, &outsize);
    
    if(outsize <= data.length){
        return NULL;
    }
    NSString * result = [[NSString alloc] initWithBytesNoCopy:rawOut length:outsize encoding:_encType freeWhenDone:YES];
    return result;
}

/**
 *  Decode a base64 string to its byte array representation
 *
 *  @param string base64 encoded string
 *
 *  @return decoded byte array or NULL if string was illegal
 */
+(NSData *) decodeBase64ToData: (NSString *) string{
    
    NSUInteger inLen = [string lengthOfBytesUsingEncoding:_encType];
    if(inLen <= 0){
        return NULL;
    }
    
    const char* rawIn = (const char*) [[string dataUsingEncoding:_encType] bytes];
    
    int outsize = -1;
    
    unsigned char* rawOut = decode(rawIn,(int) inLen, &outsize);
    if(rawOut == NULL){
        return NULL;
    }
    
    return [NSData dataWithBytes:rawOut length:outsize];
}

@end

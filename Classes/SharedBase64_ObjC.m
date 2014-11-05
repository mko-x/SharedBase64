//
//  Base64SqrlCoding.m
//  Base64
//
//  Created by Markus Kosmal on 03/11/14.
//
//

#import "Base64SqrlCoding.h"

extern char* encode(const unsigned char* data,
                    int input_length);

extern unsigned char* decode(const char* encoded,
                             int input_length);

extern int decode_result_size();

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
    char* rawOut = encode([data bytes], (int) data.length);
    
    return [NSString stringWithUTF8String:rawOut];
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
    unsigned char* rawOut = decode(rawIn,(int) inLen);
    if(rawOut == NULL){
        return NULL;
    }
    
    int size = decode_result_size();
    if(size <= 0){
        return NULL;
    }
    
    return [NSData dataWithBytes:rawOut length:size];
}

@end

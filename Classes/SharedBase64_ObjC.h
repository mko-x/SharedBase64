//
//  Base64SqrlCoding.h
//  Pods
//
//  Created by Markus Kosmal on 03/11/14.
//
//

#import <Foundation/Foundation.h>

/**
 *  Base64 encoding/decoding according to sqrl specs.
 *
 *  Contains https://www.ietf.org/rfc/rfc3548.txt filepath/urlSafe encoding
 *
 *  @see https://www.grc.com/sqrl/protocol.htm
 */
@interface Base64SqrlCoding : NSObject

/**
 *  Encode unwrapped, no padding and url-safe
 *
 *  @param data target
 *
 *  @return base64 encoded string
 */
+(NSString *) encodeDataToBase64: (NSData *) data;

/**
 *  Decode base 64 string url-safe
 *
 *  @param string base64 encoded string
 *
 *  @return data
 */
+(NSData *) decodeBase64ToData: (NSString *) string;

@end

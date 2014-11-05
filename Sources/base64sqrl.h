//
//  base64sqrl.h
//  Base64(url) according to SQRL specification at https://www.grc.com/sqrl/protocol.htm so no options, only encode and decode.
//  Based upon  RFC2045 http://www.ietf.org/rfc/rfc2045.txt,
//              RFC3548 http://www.ietf.org/rfc/rfc3548.txt,
//              RFC4648 http://www.ietf.org/rfc/rfc4648.txt
//
//  Created by Markus Kosmal on 03/11/14.
//  Released to public domain.
//
#ifndef __MKO_BASE64_H__
#define __MKO_BASE64_H__

#include <stdlib.h>

/**
 *  Encode byte array to base64 encoded string.
 *
 *  @param data byte array
 *  @param inLength
 *  @param outLength
 *
 *  @return encoded base64 string of data
 */
    char* encode(const unsigned char* data,
                 int input_length);

/**
 *  Decode base64 string to byte array.
 *
 *  @param encoded   base64 string
 *  @param inLength
 *  @param outLength
 *
 *  @return byte array from encoded string
 */
    unsigned char* decode(const char *data,
                          int input_length);

/**
 *  Fetch the final result size of decoded string
 *
 *  @return length of bytes in result
 */
    int decode_result_size();
#endif

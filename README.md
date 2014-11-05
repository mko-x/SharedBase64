Base 64 implementation

Optimized for cross-platform/web/network string encoded binary communication.

Based on plain C core - only dependency is to <stdlib.h>.

Doesn't care for padding('=','==') as it doesn't append something to create useless data.
Doesn't care for wrapping ('\n','CRLF') as not necessary for communication.
Produces URL safe encoded strings by replacing '+' and '/' with => '-' and '_' and ignoring padding with '='.

Made according to
 - RFC2045 http://www.ietf.org/rfc/rfc2045.txt
 - RFC3548 http://www.ietf.org/rfc/rfc3548.txt
 - RFC4648 http://www.ietf.org/rfc/rfc4648.txt

Wrapper available:
 - Objective-C -> SharedBase64_ObjC.h

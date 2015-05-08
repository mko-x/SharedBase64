/**
 * Created by Markus Kosmal
 *
 * Released to Public Domain
 *
 * @author mko
 */

package de.mko.sharedbase64;

/**
 * Wrapper interface for JNI calls to native C base64 methods.
 *
 */
public interface SharedBase64 {

    /**
     * URL-safe base64 encoding of data.
     *
     * @param data
     *            to be base64 encoded
     * @return base64 encoded data representation
     */
    public String encode(String data);

    /**
     * URL-safe base64 decoding of data. Trying to perform any request at once. If that isn't possible, each byte will be analyzed one for one.
     *
     * @param base64
     *            encoded data
     * @return decoded data from input
     */
    public String decode(String data);
}

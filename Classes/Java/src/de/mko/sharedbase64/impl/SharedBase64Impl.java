
package de.mko.sharedbase64.impl;

import de.mko.sharedbase64.SharedBase64;

public class SharedBase64Impl implements SharedBase64 {

    @Override
    public String encode(final String data) {
        return null;
    }

    @Override
    public String decode(final String data) {
        return null;
    }

    protected native String _encode(String data);

    protected native String _decode(String data);

}

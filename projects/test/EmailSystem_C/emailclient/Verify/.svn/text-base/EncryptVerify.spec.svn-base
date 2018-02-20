#include "Email.h"
#include "Client.h"

automaton EncryptVerify {

    before void verify(_:int, msg:int) {
        if (!isReadable(msg)) {
            fail;
        }
    }
}

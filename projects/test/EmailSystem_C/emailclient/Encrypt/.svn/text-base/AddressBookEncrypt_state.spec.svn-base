#include "Email.h"
#include "Client.h"

automaton EncryptConsistently2 {

    INIT:

        before void mail (client:int, msg:int) {
            if (isEncrypted(msg)) {
                --> CONFIDENTIAL;
            } else {
                --> PUBLIC;
            }
        }

    PUBLIC:

        before void mail (client:int, msg:int) if (isEncrypted(msg)) {
            fail;
        }

    CONFIDENTIAL:

        before void mail (client:int, msg:int) if (!isEncrypted(msg)) {
            fail;
        }    
    
}

#include <stdio.h>
#include "Email.h"
#include "Client.h"


automaton VerifyForward {

    before void deliver(client:int, msg:int) {
        
        puts("before deliver\n");

        if (isVerified(msg) ) {
            int pubkey = findPublicKey(client, getEmailFrom(msg));
            if (pubkey == 0) {
                fail;
            }
        
        }        
    }
}

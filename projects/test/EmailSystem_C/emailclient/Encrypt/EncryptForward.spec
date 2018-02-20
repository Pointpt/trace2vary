#include "Email.h"
#include "Client.h"
#include <stdio.h>

automaton EncryptForward {

    introduction {
        // in_encrypted values:
        // -1 - uninitialized
        //  0 - no
        //  1 - yes
        int in_encrypted = 0;        
    }


    before void incoming(_:int, msg:int) {
        puts("before incoming\n");
        in_encrypted = isEncrypted(msg);
        printf("in_encrypted=%d\n", in_encrypted);
    }


    before void mail(_:int, msg:int) {
        puts("before mail\n");
        printf("in_encrypted=%d\n", in_encrypted);
        if (in_encrypted && !isEncrypted(msg)) {
            fail;            
        }
    }
}

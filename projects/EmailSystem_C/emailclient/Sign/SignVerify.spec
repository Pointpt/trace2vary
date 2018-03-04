#include <stdlib.h>
#include <stdio.h>
#include "Email.h"
#include "Client.h"


automaton SignVerify1 {

    introduction {
        // sent_signed values:
        // -1 - uninitialized
        //  0 - no
        //  1 - yes
        int sent_signed= -1;        
    }


    before void mail(_:int, msg:int) {
        puts("before mail\n");
        sent_signed = isSigned(msg);
        printf("sent_signed=%d\n", sent_signed);
    }


    before void verify(client:int, msg:int) {
        puts("before verify\n");
        printf("sent_signed=%d\n", sent_signed);
        if (sent_signed==1) {

            int pubkey = findPublicKey(client, getEmailFrom(msg));
            if (pubkey == 0 || !isKeyPairValid(getEmailSignKey(msg), pubkey)) {
                fail;
            }
        }
    }
}

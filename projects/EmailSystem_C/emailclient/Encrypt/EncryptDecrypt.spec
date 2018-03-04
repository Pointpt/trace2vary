#include "Email.h"
#include "Client.h"
#include <stdio.h>

automaton EncryptDecrypt {

    introduction {
        // sent_encrypted values:
        // -1 - uninitialized
        //  0 - no
        //  1 - yes
        int sent_encrypted = -1;        
    }


    before void mail(_:int, msg:int) {
        puts("before mail\n");
        sent_encrypted = isEncrypted(msg);
        printf("sent_encrypted=%d\n", sent_encrypted);
    }


    before void incoming(client:int, msg:int) {
        puts("before decrypt\n");
        printf("sent_encrypted=%d\n", sent_encrypted);
        if (sent_encrypted==1) {
            
            if (!isKeyPairValid(getEmailEncryptionKey(msg), getClientPrivateKey(client))) {
               fail;
            }
        }
        
    }
}

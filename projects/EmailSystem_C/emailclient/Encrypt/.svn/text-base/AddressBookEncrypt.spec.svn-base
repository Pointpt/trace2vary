#include <stdio.h>
#include "Email.h"
#include "Client.h"

automaton EncryptConsistently {

    introduction {
        // mail_is_sensitive values:
        // -1 - uninitialized
        //  0 - no
        //  1 - yes
        int mail_is_sensitive = -1;        
    }

    before void mail (client:int, msg:int) {
        puts("before mail\n");
        if (mail_is_sensitive == -1) {
            mail_is_sensitive = isEncrypted(msg);
        } else if (mail_is_sensitive != isEncrypted(msg)) {
            fail;
        }
    }
}

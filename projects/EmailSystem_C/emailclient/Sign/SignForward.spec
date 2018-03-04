#include <stdlib.h>
#include <stdio.h>
#include "Email.h"
#include "Client.h"


automaton SignForward {


    before void mail(client:int, msg:int) {
        puts("before mail\n");
        if (isSigned(msg)) {
            if (getClientPrivateKey(client) == 0) {
                fail;
            }
        }
    }

}

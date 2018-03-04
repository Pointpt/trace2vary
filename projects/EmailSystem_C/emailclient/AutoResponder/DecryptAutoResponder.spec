#include <stdio.h>
#include "Email.h"
#include "Client.h"

automaton DecryptAutoResponder {

    before void autoRespond (client:int, msg:int) {
        puts("before autoRespond\n");
        if (!isReadable(msg)) {
            fail;
        }
    }
}

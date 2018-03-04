#include "Email.h"
#include "Client.h"
#include <stdio.h>

automaton DecryptForward {

    before void forward(_:int, msg:int) {
        puts("before forward\n");
        if (!isReadable(msg)) {
            fail;            
        }
    }
}

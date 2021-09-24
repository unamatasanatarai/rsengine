#include <stdio.h>
#include "rsengine/loop.h"

void rs_main(){
    printf("%lu\n", rs_get_tick());
    if (rs_get_tick() > 40){
        rs_stop();
    }
}

int main(){
    rs_start();
}

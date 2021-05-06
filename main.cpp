#include <iostream>
#include <omp.h>
#include <string>
#include <boost/lexical_cast.hpp>

#include "EpollInstance.h"
#include "AcceptConnectionEvent.h"

int main(int argc, char** argv) {
    EpollInstance ep;
    AcceptConnectionEvent acceptConnectionEvent(ep, boost::lexical_cast<short int>(argv[1]));

    while(1) {
        ep.waitEvents();
    }

    return 0;
}

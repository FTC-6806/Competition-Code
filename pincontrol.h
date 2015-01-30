#include "hitechnic-superpro.h"

#define setPinValue(pin, status) pinvalues = (pinvalues & ~(1<<pin)) | ((!!status)<<pin); HTSPBwriteIO(HTSPB, pinvalues);
#define setPinMode(pin, status) pinmodes = (pinmodes & ~(1<<pin)) | ((!!status)<<pin); HTSPBsetupIO(HTSPB, pinmodes);
#define getPinValue(pin) ((HTSPBreadIO(HTSPB, (1 << pin)) & (1 << pin)) ? true : false)
#define readadc(pin) HTSPBreadADC(HTSPB, pin, 10)
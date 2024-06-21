
#ifndef TARGETSPECIFIC_XCP_DEBUG_H_
#define TARGETSPECIFIC_XCP_DEBUG_H_

#include <string.h>
#include <stdio.h>

// Enable to print XCP communication messages to console
#define XCP_COM_DEBUG

#ifdef XCP_COM_DEBUG
// Enable to print XCP DAQ communication messages to console
// Attention: Might lead to lots of messages depending on DAQ sampling rate
//#define XCP_DAQ_DEBUG
#endif


#endif /* TARGETSPECIFIC_XCP_DEBUG_H_ */

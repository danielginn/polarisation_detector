/* 
 * Copyright (c) 2008, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef _CE_API_H_
#define _CE_API_H_

#include <vrmusbcam2.h>

#if defined (__cplusplus)
extern "C" {
#endif

/* API for the Codec-Engine-using subsystem, that hides Codec Engine API from
 * its users
 */

// Initialize the codec engine 
int DspInit();            

// Exit the codec engine 
void  DspExit();  

// Allocate/free physically contiguous memory
char *DspAllocMemory(int bufSize);
void DspFreeMemory(char *buf, int bufSize);

enum dsp_cmd
{
	PROC_SYNC,
	PROC_WAIT,
	PROC_ASYNC
};

// Convert images with the VRmagic codec. Choose with "cmd" if the call should be
// blocking (PROC_SYNC), non-blocking (PROC_ASYNC) or waiting (PROC_WAIT)
int DspConvertImage(enum dsp_cmd cmd, VRmImage* source, VRmImage* target);

#if defined (__cplusplus)
}
#endif

#endif /* _CE_API_H_ */


#include "crfb_frame_buffer.h"

CRFBFramebuffer* crfb_create_frame_buffer(unsigned int w, unsigned int h, unsigned char bytesPerPixel) {
    CRFBFramebuffer* frameBuffer = (CRFBFramebuffer*) malloc(sizeof(CRFBFramebuffer));

    frameBuffer->data = malloc(w * h * bytesPerPixel);
    frameBuffer->width = w;
    frameBuffer->height = h;

    frameBuffer->isOwnData = 1;

    return frameBuffer;
}

CRFBFramebuffer* crfb_create_frame_buffer_from_ptr(unsigned int w, unsigned int h, void* data) {
    CRFBFramebuffer* frameBuffer = (CRFBFramebuffer*) malloc(sizeof(CRFBFramebuffer));

    frameBuffer->data = data;
    frameBuffer->width = w;
    frameBuffer->height = h;

    frameBuffer->isOwnData = 0;

    return frameBuffer;
}

void crfb_free_frame_buffer(CRFBFramebuffer* frameBuffer) {
    if(frameBuffer == NULL)
        return;

    if(frameBuffer->isOwnData)
        free(frameBuffer->data);

    free(frameBuffer);
}

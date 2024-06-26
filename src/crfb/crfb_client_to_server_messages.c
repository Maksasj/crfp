#include "crfb_client_to_server_messages.h"

void crfb_client_send_set_encodings_message(CRFBClient* client, CRFBEncoding* encodings, unsigned long count) {
    typedef struct SetEncodings {
        unsigned char messageType;
        unsigned char padding;
        unsigned short numberOfEncodings;
    } SetEncodings;

    SetEncodings enc;

    enc.messageType = SET_ENCODINGS;
    enc.padding = 0;
    enc.numberOfEncodings = count;
    crfb_ushort_to_little(&enc.numberOfEncodings);

    unsigned int size = sizeof(SetEncodings) + sizeof(CRFBEncoding) * count;
    unsigned char* buffer = malloc(size);

    memcpy(buffer, &enc, sizeof(SetEncodings));

    for(int i = 0; i < count; ++i) {
        CRFBEncoding encoding = encodings[i];
        crfb_uint_to_little(&encoding);        
        memcpy(buffer + sizeof(SetEncodings) + i * sizeof(CRFBEncoding), &encoding, sizeof(CRFBEncoding));
    }

    fflush(stdout);

    if(send(client->socket, buffer, size, 0) == -1)
        CRFB_LOG(CRFB_ERROR, "Failed to send packet to server");

    free(buffer);
}

// Todo impleemnt incremental
void crfb_client_send_framebuffer_update_request_message(
    CRFBClient* client, 
    unsigned char incremental, 
    unsigned short xPosition,
    unsigned short yPosition,
    unsigned short width,
    unsigned short height
) {
    typedef struct FramebufferUpdateRequest {
        unsigned char messageType;
        unsigned char incremental;

        unsigned short xPosition;
        unsigned short yPosition;
        unsigned short width;
        unsigned short height;
    } FramebufferUpdateRequest;

    FramebufferUpdateRequest req;
    req.messageType = FRAMEBUFFER_UPDATE_REQUEST;
    req.incremental = incremental;

    req.xPosition = xPosition;
    req.yPosition = yPosition;
    req.width = width;
    req.height = height;

    crfb_ushort_to_little(&req.xPosition);
    crfb_ushort_to_little(&req.yPosition);
    crfb_ushort_to_little(&req.width);
    crfb_ushort_to_little(&req.height);

    if(send(client->socket, &req, sizeof(FramebufferUpdateRequest), 0) == -1)
        CRFB_LOG(CRFB_ERROR, "Failed to send packet to server");
}

void crfb_client_send_key_event_message(CRFBClient* client, unsigned char downFlag, unsigned int key) {
    typedef struct CRFBKeyEvent {
        unsigned char messageType;
        unsigned char downFlag;
        unsigned char padding[2];
        unsigned int key;
    } CRFBKeyEvent;

    CRFBKeyEvent req;
    req.messageType = CRFB_KEY_EVENT;
    req.downFlag = downFlag;
    
    req.padding[0] = 0;
    req.padding[1] = 0;

    req.key = key;

    crfb_uint_to_little(&req.key);

    if(send(client->socket, &req, sizeof(CRFBKeyEvent), 0) == -1)
        CRFB_LOG(CRFB_ERROR, "Failed to send packet to server");
}

void crfb_client_send_pointer_event_message(CRFBClient* client, unsigned char buttonMask, unsigned short xPosition, unsigned short yPosition) {
    typedef struct CRFBPointerEvent {
        unsigned char messageType;
        unsigned char buttonMask;
        unsigned short xPosition;
        unsigned short yPosition;
    } CRFBPointerEvent;

    CRFBPointerEvent req;
    req.messageType = POINTER_EVENT;
    req.buttonMask = buttonMask;
    req.xPosition = xPosition;
    req.yPosition = yPosition;

    crfb_ushort_to_little(&req.xPosition);
    crfb_ushort_to_little(&req.yPosition);

    if(send(client->socket, &req, sizeof(CRFBPointerEvent), 0) == -1)
        CRFB_LOG(CRFB_ERROR, "Failed to send packet to server");
}

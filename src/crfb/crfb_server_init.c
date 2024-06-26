#include "crfb_server_init.h"

CRFBServerInit crfb_client_recv_server_init(CRFBClient* client) {
    CRFBServerInit serverInit;

    if(recv(client->socket, &serverInit.framebufferWidth, sizeof(unsigned short), MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv server init framebufferWidth");

    if(recv(client->socket, &serverInit.framebufferHeight, sizeof(unsigned short), MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv server init framebufferHeight");

    crfb_ushort_to_little(&serverInit.framebufferWidth);
    crfb_ushort_to_little(&serverInit.framebufferHeight);

    serverInit.pixelFormat = crfb_client_recv_pixel_format(client);

    if(recv(client->socket, &serverInit.nameLength, sizeof(unsigned int), MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv server init nameLength");

    crfb_uint_to_little(&serverInit.nameLength);

    serverInit.nameString = (char*) malloc(serverInit.nameLength + 1);
    memset(serverInit.nameString, '\0', serverInit.nameLength + 1);

    if(recv(client->socket, serverInit.nameString, serverInit.nameLength, MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv server init nameString");

    return serverInit;
}

void crfb_printify_server_init(CRFBServerInit serverInit) {
    /*
    printf("framebufferWidth: %d\n", serverInit.framebufferWidth);
    printf("framebufferHeight: %d\n", serverInit.framebufferHeight);

    crfb_printify_pixel_format(serverInit.pixelFormat);

    printf("nameLength: %d\n", serverInit.nameLength);
    printf("nameString: %s\n", serverInit.nameString);
    */
}

CRFBTightServerInitExt crfb_client_recv_tight_server_init_extension(CRFBClient* client) {
    CRFBTightServerInitExt ext;

    if(recv(client->socket, &ext.numberOfServerMessages, sizeof(unsigned short), MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv tight server init extension numberOfServerMessages");

    if(recv(client->socket, &ext.numberOfClientMessages, sizeof(unsigned short), MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv tight server init extension numberOfClientMessages");

    if(recv(client->socket, &ext.numberOfEncodings, sizeof(unsigned short), MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv tight server init extension numberOfEncodings");

    crfb_short_to_little(&ext.numberOfServerMessages);
    crfb_short_to_little(&ext.numberOfClientMessages);
    crfb_short_to_little(&ext.numberOfEncodings);

    char padding[2] = { 0 };

    if(recv(client->socket, padding, 2, MSG_WAITALL) <= 0)
        CRFB_LOG(CRFB_ERROR, "Failed to recv tight server init extension padding");

    return ext;
}

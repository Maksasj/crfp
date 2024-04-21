#include "crfp/crfp.h"

#define BUFFLEN 4096

void int_to_little(int* value) {
    *value = ((*value >> 24) & 0xff) | // move byte 3 to byte 0
             ((*value << 8) & 0xff0000) | // move byte 1 to byte 2
             ((*value >> 8) & 0xff00) | // move byte 2 to byte 1
             ((*value << 24) & 0xff000000); // byte 0 to byte 3
}

void short_to_little(short* value) {
    *value = ((*value & 0xFF00) >> 8) | ((*value & 0x00FF) << 8);
}

int main(int argc, char *argv[]){

    CRFPClient* client = crfp_new_client();

    crfp_client_connect(client, "192.168.1.103", 5900);
    
    {   // Handshake
        {
            char buffer[BUFFLEN] = { '\0' };
            int len = recv(client->socket, buffer, BUFFLEN, 0);
            printf("Server sent: %d '%s'\n", len, buffer);
        }

        char* version = "RFB 003.008\n"; 
        if(send(client->socket, version, strlen(version), 0) == -1) {
            fprintf(stderr,"ERROR failed to send packet to server\n");
        }
    }

    printf("\n");

    {   // Gets security types
        char byte;
        int len = recv(client->socket, &byte, 1, 0);
        printf("Security types %x\n", byte);

        for(int i = 0; i < byte; ++i) {
            char sec;
            int len = recv(client->socket, &sec, 1, 0);
            printf("    Security type: %d\n", sec);

            if(sec == 0) printf("Invalid");
            else if(sec == 1) printf("No Authentication");
            else if(sec == 2) printf("VNC Authentication");
            else if(sec == 5) printf("RSA-AES Security Type");
            else if(sec == 6) printf("RSA-AES Unecrypted Security Type");
            else if(sec == 13) printf("RSA-AES Two-step Security Type");
            else if(sec == 16) printf("Tight Security Type");
            else if(sec == 19) printf("VenCrypt");
            else if(sec == 22) printf("xvp Authentication");
            else if(sec == 30) printf("Diffie-Hellman Authentication");
            else if(sec == 113) printf("MSLogonII Authentication");
            else if(sec == 129) printf("RSA-AES-256 Security Type");
            else if(sec == 130) printf("RSA-AES-256 Unencrypted Security Type");
            else if(sec == 133) printf("RSA-AES-256 Two-step Security Type");
            else printf("Unofficial security type"); 

            printf("\n");                
        }
    }

    printf("\n");
    
    { // Tight Security Type Security handskae
        char type = 16; 
        if(send(client->socket, &type, 1, 0) == -1) {
            fprintf(stderr,"ERROR failed to send packet to server\n");
        }

        {   // Tunnel count
            unsigned int word = 0;
            int len = recv(client->socket, &word, sizeof(word), 0);
            int_to_little(&word);
            printf("Number of tunnels: '%d'\n", word);
        }

        {   // Authentication types
            unsigned int word = 0;
            int len = recv(client->socket, &word, sizeof(word), 0);
            int_to_little(&word);
            printf("Authentication types: '%d'\n", word);
        }

        {   // Security result
            unsigned int word = 0;
            int len = recv(client->socket, &word, sizeof(word), 0);
            printf("Server sent: %d '%d'\n", len, word);

            if(len == 0) printf("LENGTH ZERO");

            if(word == 0) {
                printf("    SecurityResult OK\n");
            } else if(word == 1) {
                printf("    SecurityResult Failed\n");
            } else {
                printf("    Unofficial SecurityResult type\n");
            }
        }
    }

    {
        {   // ClientInit
            typedef struct ClientInit {
                char sharedFlag;
            } ClientInit;

            ClientInit clientInit;
            clientInit.sharedFlag = 0;

            if(send(client->socket, &clientInit, sizeof(ClientInit), 0) == -1) {
                fprintf(stderr,"ERROR failed to send packet to server\n");
            }

            printf("Send client init !\n");
        }

        {
            {
                unsigned short word = 0;
                int len = recv(client->socket, &word, 2, 0);
                short_to_little(&word);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned short word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                short_to_little(&word);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned short word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                short_to_little(&word);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned short word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                short_to_little(&word);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned short word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                short_to_little(&word);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                unsigned char word = 0;
                int len = recv(client->socket, &word, sizeof(word), 0);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                char buffer[BUFFLEN] = { '\0' };
                int len = recv(client->socket, buffer, 2, 0);
                printf("Server sent: %d, '%d' '%d' '%d'\n", len, buffer[0], buffer[1], buffer[2]);
            }

            {
                unsigned int word = 0;
                int len = recv(client->socket, &word, 4, 0);
                int_to_little(&word);
                printf("Server sent: %d, '%d'\n", len, word);
            }

            {
                char buffer[16] = { '\0' };
                int len = recv(client->socket, buffer, 15, 0);
                printf("Server sent: %d '%s'\n", len, buffer);
            }


            unsigned short numberOfServerMessages;
            unsigned short numberOfClientMessages;
            unsigned short numberOfEncodings;

            {
                int len = recv(client->socket, &numberOfServerMessages, sizeof(numberOfServerMessages), 0);
                short_to_little(&numberOfServerMessages);
                printf("Server sent: %d, '%d'\n", len, numberOfServerMessages);
            }
            {
                int len = recv(client->socket, &numberOfClientMessages, sizeof(numberOfClientMessages), 0);
                short_to_little(&numberOfClientMessages);
                printf("Server sent: %d, '%d'\n", len, numberOfClientMessages);
            }
            {
                int len = recv(client->socket, &numberOfEncodings, sizeof(numberOfEncodings), 0);
                short_to_little(&numberOfEncodings);
                printf("Server sent: %d, '%d'\n", len, numberOfEncodings);
            }
            {
                unsigned short padding = 0;
                int len = recv(client->socket, &padding, sizeof(padding), 0);
                short_to_little(&padding);
                printf("Server sent: %d, '%d'\n", len, padding);
            }

            typedef struct Capability {
                signed int code;
                char vendor[4]; 
                char signature[8]; 
            } Capability;

            printf("\nServer messages:\n");
            for(int i = 0; i < numberOfServerMessages; ++i) {
                Capability cap;

                int len = recv(client->socket, &cap.code, sizeof(cap.code), 0);
                len = recv(client->socket, &cap.vendor, sizeof(cap.vendor), 0);
                len = recv(client->socket, &cap.signature, sizeof(cap.signature), 0);

                int_to_little(&cap.code);

                printf("    Capability\n");
                printf("        Code: %d\n", cap.code);
                printf("        Vendor: %.4s\n", cap.vendor);
                printf("        Signature: %.8s\n", cap.signature);
            }


            printf("\nClient messages:\n");
            for(int i = 0; i < numberOfClientMessages; ++i) {
                Capability cap;

                int len = recv(client->socket, &cap.code, sizeof(cap.code), 0);
                len = recv(client->socket, &cap.vendor, sizeof(cap.vendor), 0);
                len = recv(client->socket, &cap.signature, sizeof(cap.signature), 0);

                int_to_little(&cap.code);

                printf("    Capability\n");
                printf("        Code: %d\n", cap.code);
                printf("        Vendor: %.4s\n", cap.vendor);
                printf("        Signature: %.8s\n", cap.signature);
            }

            printf("\nEncodings:\n");
            for(int i = 0; i < numberOfEncodings; ++i) {
                Capability cap;
                
                int len = recv(client->socket, &cap.code, sizeof(cap.code), 0);
                len = recv(client->socket, &cap.vendor, sizeof(cap.vendor), 0);
                len = recv(client->socket, &cap.signature, sizeof(cap.signature), 0);

                int_to_little(&cap.code);

                printf("    Capability\n");
                printf("        Code: %d\n", cap.code);
                printf("        Vendor: %.4s\n", cap.vendor);
                printf("        Signature: %.8s\n", cap.signature);
            }
        }
    }

    {
        // Mistery packet
        char message[40] = {
            0x02, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0x21, 0xff, 0xff, 0xff, 0x20, 0xff, 0xff, 0xff, 0x18, 0xff, 0xff, 0xff, 0x11,
        }; 

        if(send(client->socket, &message, 40, 0) == -1) {
            fprintf(stderr,"ERROR failed to send packet to server\n");
        }
    }

    {
        // Mistery packet
        char message[4] = {
            0xfc, 0x00, 0x02, 0x01
        }; 

        if(send(client->socket, &message, 4, MSG_DONTWAIT) == -1) {
            fprintf(stderr,"ERROR failed to send packet to server\n");
        }
    }

    {
        typedef struct FramebufferUpdateRequest {
            unsigned char messageType;
            unsigned char incremental;

            unsigned short xPosition;
            unsigned short yPosition;
            unsigned short width;
            unsigned short height;
        } FramebufferUpdateRequest;

        FramebufferUpdateRequest req;
        req.messageType = 3;
        req.incremental = 0; // Lost

        req.xPosition = 0;
        req.yPosition = 0;
        req.width = 4320;
        req.height = 1350;

        short_to_little(&req.xPosition);
        short_to_little(&req.yPosition);
        short_to_little(&req.width);
        short_to_little(&req.height);

        if(send(client->socket, &req, sizeof(FramebufferUpdateRequest), MSG_DONTWAIT) == -1) {
            fprintf(stderr,"ERROR failed to send packet to server\n");
        }

        printf("Send framebuffer update request !\n");

        {
            char buffer[16] = { '\0' };
            int len = recv(client->socket, buffer, 16, 0);
            printf("Server sent: %d\n", len);
        }
    }


    {
        typedef struct FramebufferUpdateRequest {
            unsigned char messageType;
            unsigned char incremental;

            unsigned short xPosition;
            unsigned short yPosition;
            unsigned short width;
            unsigned short height;
        } FramebufferUpdateRequest;

        FramebufferUpdateRequest req;
        req.messageType = 3;
        req.incremental = 0; // Lost

        req.xPosition = 0;
        req.yPosition = 0;
        req.width = 4320;
        req.height = 1350;

        short_to_little(&req.xPosition);
        short_to_little(&req.yPosition);
        short_to_little(&req.width);
        short_to_little(&req.height);

        if(send(client->socket, &req, sizeof(FramebufferUpdateRequest), MSG_DONTWAIT) == -1) {
            fprintf(stderr,"ERROR failed to send packet to server\n");
        }

        printf("Send framebuffer update request !\n");

       {
            size_t size = 4320 * 1350 * 4;
                unsigned char* buffer = (char*) malloc(size);

                size_t len = 0;
                while (len < size) {
                    ssize_t n = recv(client->socket, buffer + len, size - len, 0);
                    if (n <= 0) {
                        // error handling here
                        break;
                        printf("Errpr !\n");
                    }
                    len += n;
                }

                printf("%ld\n", len);

                for(int x = 0; x < 4320; ++x) {
                    for(int y = 0; y < 1350; ++y) {
                        printf("%x ", *(buffer + 4320 * y + x));
                    }
                    printf("\n");
                }

                free(buffer);        
        }

        /*
        {
            typedef struct FramebufferUpdate {
                unsigned char messageType;
                unsigned char padding;
                unsigned short numberOfRectangles;
            } FramebufferUpdate;
            
            FramebufferUpdate update;

            {
                int len = recv(client->socket, &update, sizeof(FramebufferUpdate), 0);
                printf("Server sent: %d\n", len);
            }

            short_to_little(&update.numberOfRectangles);

            printf("Message type: %d\n", update.messageType);
            printf("Number Of Rectangles %d\n", update.numberOfRectangles);

            for(int i = 0; i < update.numberOfRectangles; ++i) {
                printf("\n");
                typedef struct Rectangle {
                    unsigned short xPosition;
                    unsigned short yPosition;
                    unsigned short width;
                    unsigned short height;
                    unsigned int encodingType;
                } Rectangle;

                Rectangle rect;
                
                {
                    int len = recv(client->socket, &rect, sizeof(Rectangle), 0);
                    printf("Server sent: %d\n", len);

                    short_to_little(&rect.xPosition);
                    short_to_little(&rect.yPosition);
                    short_to_little(&rect.width);
                    short_to_little(&rect.height);

                    printf("xPosition: %d\n", rect.xPosition);
                    printf("yPosition: %d\n", rect.yPosition);
                    printf("width: %d\n", rect.width);
                    printf("height: %d\n", rect.height);
                    printf("encodingType: %d\n", rect.encodingType);
                }
            }
        }
        */
    }

    crfp_client_close(client);
    crfp_free_client(client);

    return 0;
}
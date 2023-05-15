#include <iostream>
using namespace std;

 

#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#define SOCKET_PATH "/home/gen5/socket/ServerSocket"
struct my_struct {
    char name[100];
    int mbirth;
};
int main(int argc, char *argv[])
{
    int data_socket;
    int result;
    char buffer[1024];
    int n;
    struct sockaddr_un sockAddr;
    memset(&sockAddr, 0, sizeof(struct sockaddr_un));
    sockAddr.sun_family = AF_UNIX;
    strncpy(sockAddr.sun_path, SOCKET_PATH, sizeof(sockAddr.sun_path)-1);

 

    // tạo socket
    data_socket = socket(AF_UNIX, SOCK_STREAM, PF_UNIX);

 

    // connect nó tới master socket, thông qua sockAddr, vì sockAddr bên server đã được bind với master socket, nó là master socket
    result = connect(data_socket, (const struct sockaddr *)&sockAddr, sizeof(struct sockaddr_un));
    if(result == -1){
        perror("connect");
        return 1;
    }

 

    // sau đó client này với server connect với nhau thoong qua thằng data_socket này
    while (true) {
        my_struct mstruct;
        memset(buffer, 0, 1024);
        memset(mstruct.name, 0, 100);
        memset(&mstruct, 0, sizeof(mstruct));
        result = read(data_socket, buffer, sizeof(struct my_struct));
        memcpy(&mstruct, buffer, sizeof(my_struct));
        cout << mstruct.name << " " <<mstruct.mbirth << endl;
        cout << "enter: ";
        cin >> n;

 

        int result = write(data_socket, &n, sizeof(int));
        if(result == -1) {
            perror("write");
            break;
        }
    }
    close(data_socket);
    return 0;
}

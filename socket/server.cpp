#include <iostream>
using namespace std;

#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <vector>

#define SOCKET_PATH "/home/gen5/socket/ServerSocketFile"
struct my_struct {
    char name[100];
    int mbirth;
};

char* localName[10] = {"le ngoc hai", "tran bao ngoc", "bui chi thuc",
                       "nguyen trung hieu", "tran van duc", "doan quang tuyen",
                       "hoang tuan anh", "doan quang luong", "le thuy hien",
                       "le viet quynh"};
int returnLength(char* str){
    int length = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        length++;
    }
    return length;
}

void client_handler(int client_fd, char* local_name, int birth){
    std::cout << "Connected on data_socket " << client_fd << std::endl;
    int n;
    for(;;) {
        my_struct mstruct;
        memset(&mstruct, 0, sizeof(mstruct));
        memcpy(mstruct.name, local_name, returnLength(local_name));
        mstruct.mbirth = birth;

        int result = write(client_fd, &mstruct, sizeof(my_struct));
        if(result == -1) {
            perror("write");
            break;
        }

        // Sleep for a while to simulate work
        std::this_thread::sleep_for(std::chrono::seconds(1));
        result = read(client_fd, &n, sizeof(int));
        cout << "int n " << n << "thread id " << std::this_thread::get_id() << endl;

    }

    std::cout << "Disconnected on data socket " << client_fd << std::endl;
    close(client_fd);
}
int main(int argc, char *argv[])
{
    int master_socket;
    int result;
    int data_socket[10];
    char buffer[1024];

    /* AF_UNIX socket family is used to
       communicate between processes on the same machine
     * struct sockaddr_un là socket address, nó dùng để lưu cái value socket : family, path của socket
     * path: nó là 1 file hệ thống, phải tạo và xóa thủ công, kiểu socket nó sẽ bind với file hệ thống này
     * */
    struct sockaddr_un sockAddr;
    memset(&sockAddr, 0, sizeof(struct sockaddr_un));
    sockAddr.sun_family = AF_UNIX;
    strncpy(sockAddr.sun_path, SOCKET_PATH, sizeof(sockAddr.sun_path)-1);

    unlink(SOCKET_PATH); // xóa file - system call

    // tạo 1 socket trả về file descriptor
    master_socket = socket(AF_UNIX,SOCK_STREAM,PF_UNIX);
    if(master_socket == -1){
        perror("create mastor discrible file socket fail");
        return 1;
    }
    cout << "created mastor discrible file socket success" << endl;

    // binding (liên kết) cái socket này tới cái địa chỉ sockAddr (file vật lý hệ thống kia SOCKET_PATH)
    result = bind(master_socket, (const struct sockaddr *)&sockAddr, sizeof(struct sockaddr_un));
    if(result == -1){
        perror("bind");
        return 1;
    }
    cout << "bind() call succeed" << endl;

    // lắng nghe trên cái socket đó, tối đa 10 thằng, (bn thằng thì tự truyền vào)
    result = listen(master_socket, 10);
    if(result == -1){
        perror("listen");
        return 1;
    }

    /*kiểu khi tạo 1 socket xong bind nó tới 1 file vật lý, xong listen trên nó, hoặc bởi nó là thằng socket đầu tiên được tao -> nó là master socket
     * sau đó bên client thì cũng tạo socket từ socket(), nhưng lúc này nó là data_socket,
     * sau đó liên kết cái data socket này tới master socket, chính là sockAddr, bởi thằng này đang bind tới master socket
     * -> sau đó thì read write hay send recei thôi
     * */

    std::vector<std::thread> threads;

    for(int i = 0;i<10;i++){
        cout << "waiting accept " << i << " ... " << endl;

        /* accept là system call blocking, block tại đây để đợi 1 connect tới từ client - connect()
         * accept() nó trả về data_socket giống với cái trả về từ hàm connect() bên client, tk server client connect nhau thông qua data_socket này
         * master socket ban đầu nó quản lý tất cả data_socket,
        */
        data_socket[i] = accept(master_socket, nullptr, nullptr);
        if(data_socket[i] == -1){
            perror("accept");
            return 1;
        }
        cout << "connected on data_socket " << data_socket[i] << endl;

        std::thread t(client_handler, data_socket[i], localName[i], i);
        threads.emplace_back(std::move(t));
    }
    for(auto& t : threads) {
        t.join();
    }
    close(master_socket);
    return 0;
}

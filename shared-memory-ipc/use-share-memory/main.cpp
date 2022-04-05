#include "logger.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <iostream>

#define GENERATE_KEY 'K'
#define PATH_KEY "/home/gen5/LEARN-FOR-FAST-TRACK/shared-memory-ipc/generate-key"

typedef struct DYDX{
    int priceCurrent = 0;
    int* priceFuture = nullptr;
} DYDX;

int main(int argc, char *argv[])
{
    LOG << "main start use share mem !";

    key_t key = ftok(PATH_KEY, GENERATE_KEY);
    if(key == -1){
        LOG << "path is not exist";
    }
    else{
        LOG << "key is: " << key;
    }

    int shmid;
    shmid = shmget(key, 0, 0);
    LOG << "shmid is: " << " " << shmid;
    DYDX* ptr_share = (DYDX*)shmat(shmid, nullptr, 0);
    if(ptr_share->priceFuture == nullptr){
        LOG << "null";
    }
    else{
        LOG << "no null";
    }
    LOG << ptr_share->priceCurrent << " " << *(ptr_share->priceFuture);

    shmctl(shmid, IPC_RMID, nullptr); // IPC_RMID - remove định danh của vùng nhớ, xóa hẳn vùng nhớ này luôn
    return 0;
}

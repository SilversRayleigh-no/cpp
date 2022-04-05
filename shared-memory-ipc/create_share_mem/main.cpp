#include "logger.h"
#include <sys/types.h>
#include <sys/ipc.h> //key_t and ftok
#include <sys/shm.h> // shmctl, shmget, shmat, shmdt

/*
typedef __key_t key_t;
# define __key_t_defined

 Generates key for System V style IPC.
extern key_t ftok (const char *__pathname, int __proj_id) __THROW;



 Shared memory control operation.
extern int shmctl (int __shmid, int __cmd, struct shmid_ds *__buf) __THROW;

 Get shared memory segment.
extern int shmget (key_t __key, size_t __size, int __shmflg) __THROW;

 Attach shared memory segment.
extern void *shmat (int __shmid, const void *__shmaddr, int __shmflg)
     __THROW;

 Detach shared memory segment.
extern int shmdt (const void *__shmaddr) __THROW;
*/

#define GENERATE_KEY 'K'
#define PATH_KEY "/home/gen5/LEARN-FOR-FAST-TRACK/shared-memory-ipc/generate-key"
#define PATH_KEY_1 "/home/gen5/LEARN-FOR-FAST-TRACK/shared-memory-ipc/generate-key-1"


struct DYDX{
    int priceCurrent = 0;
//    int* priceFuture = nullptr;
};

int main(int argc, char *argv[])
{
    LOG << "main start create share mem !";
    LOG << "size of DYDX: " << sizeof(DYDX);

    /*⇒ các process khác nhau chỉ cần cung cấp path và id giống
    nhau là có thể tạo đúng key truy cập đến cùng một IPC object.*/
    key_t key = ftok(PATH_KEY, GENERATE_KEY);
    if(key == -1){
        LOG << "path is not exist";
    }
    else{
        LOG << "key is: " << key;
    }

    int shmid;
    shmid = shmget(key, sizeof(DYDX), 0666|IPC_CREAT|IPC_EXCL); // tạo ra 1 phân đoạn bộ nhớ dùng chung với size, permission, trả về 1 mã định danh cho phân đoạn bộ nhớ này được liên kết với khóa là key
    /*
    #define IPC_CREAT	01000		Create key if key does not exist.
    #define IPC_EXCL	02000		Fail if key exists.
    #define IPC_NOWAIT	04000		Return error on wait.
    */

    LOG << "shmid is: " << " " << shmid;
//    shmctl(shmid, IPC_RMID, 0);
//    DYDX a;

//    LOG << a.priceCurrent << " " << *(a.priceFuture);

    DYDX* ptr_share = (DYDX*)shmat(shmid, nullptr, 0); // trả về 1 con trỏ chọc vaò cái vùng nhớ có cái mã định danh là shmid
    ptr_share->priceCurrent = 9;

    /* để hiểu đơn giản thì int a = 3; a chính là tên định danh cho cái vùng nhớ 4kb có giá trị là 3 đó */

//    key_t key1 = ftok(PATH_KEY_1, GENERATE_KEY);
//    if(key1 == -1){
//        LOG << "path is not exist";
//        return 0;
//    }
//    else{
//        LOG << "key1 is: " << key1;
//    }

//    int shmid1;
//    shmid1 = shmget(key1, sizeof(int), 0666|IPC_CREAT|IPC_EXCL);
//    LOG << "shmid1 is: " << " " << shmid1;
//    shmctl(shmid1, IPC_RMID, 0);

//    ptr_share->priceFuture = (int*)shmat(shmid1, ptr_share, 0);


//    *(ptr_share->priceFuture) = 3;
//    LOG << ptr_share->priceCurrent << " " << *(ptr_share->priceFuture);

//    shmdt(ptr_share->priceFuture);

    shmdt(ptr_share); // detach ra khỏi cái process này
    // LOG << ptr_share << " - " << "main end create share mem !";
    return 0;
}


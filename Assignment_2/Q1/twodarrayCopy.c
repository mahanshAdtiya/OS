#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(twodarrayCopy, float**, src, float**, dest, int, len,int ,breadth){
    
    float buffer[5][5]; 
    
    if (__copy_from_user(buffer, src, sizeof(float)* (len*breadth))){
        return -EFAULT;
    }

    if (__copy_to_user(dest, buffer, sizeof(float)*(len*breadth)))[
        return -EFAULT;
    ]

    return 0;
}
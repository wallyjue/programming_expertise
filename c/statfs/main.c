#include <stdio.h>
#include <sys/vfs.h>
int main()
{
    struct statfs sfs;
    int i = statfs("/share/CACHEDEV1_DATA", &sfs);
    int percent = (sfs.f_blocks - sfs.f_bfree ) * 100 / (sfs.f_blocks -
sfs.f_bfree + sfs.f_bavail) + 1;
    printf("/share/CACHEDEV1_DATA      %ld    %ld  %ld   %d%% /share/CACHEDEV1_DATA\n\n",
           sfs.f_blocks, (sfs.f_blocks - sfs.f_bfree), sfs.f_bavail, percent);
    system("df /home ");
    return 0;
}

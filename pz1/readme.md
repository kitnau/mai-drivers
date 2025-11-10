# 1) Написать программу для чтения данных с устройства dev/zero
```#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	char buf[100];
	int fd = open("/dev/zero", O_RDONLY);
	read (fd, buf, 100);
	close (fd);
	
	return 0;
}
```

# 2) При помощи strace найти системные вызовы для работы с файловой и подсистемой управления памяти
```(kali㉿kali)-[~/develop/kernel/pz1]
└─$ sudo strace ./pz1

execve("./pz1", ["./pz1"], 0x7ffe5a4cda80 /* 20 vars */) = 0
brk(NULL)                               = 0x55b5ec9f8000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8472396000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=93279, ...}) = 0
mmap(NULL, 93279, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f847237f000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0p\236\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 840, 64) = 840
fstat(3, {st_mode=S_IFREG|0755, st_size=2003408, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 840, 64) = 840
mmap(NULL, 2055800, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f8472189000
mmap(0x7f84721b1000, 1462272, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7f84721b1000
mmap(0x7f8472316000, 352256, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x18d000) = 0x7f8472316000
mmap(0x7f847236c000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e2000) = 0x7f847236c000
mmap(0x7f8472372000, 52856, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f8472372000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f8472186000
arch_prctl(ARCH_SET_FS, 0x7f8472186740) = 0
set_tid_address(0x7f8472186a10)         = 17528
set_robust_list(0x7f8472186a20, 24)     = 0
rseq(0x7f8472186680, 0x20, 0, 0x53053053) = 0
mprotect(0x7f847236c000, 16384, PROT_READ) = 0
mprotect(0x55b5b31a3000, 4096, PROT_READ) = 0
mprotect(0x7f84723d2000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f847237f000, 93279)           = 0
openat(AT_FDCWD, "/dev/zero", O_RDONLY) = 3
read(3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 100) = 100
close(3)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

Вызовы для работы с файловой системой:
 ```access, openat, read, pread64, fstat, close```

Вызовы для работы с памятью:
```brk, mmap, mprotect, munmap, arch_prctl, prlimit64```



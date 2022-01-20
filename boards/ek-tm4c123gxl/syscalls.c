/**
 * @file syscalls.c
 * @author Esteban Duran (@astroesteban)
 * @brief Contains system call definitions for using the C/C++ standard library
 * @version 0.1
 * @date 2022-01-18
 * 
 * @note You can look for sections using nm -g libsyscalls.a | grep exit
 * 
 * @ref https://interrupt.memfault.com/blog/boostrapping-libc-with-newlib#implementing-our-own-c-standard-library
 * @ref https://www.youtube.com/watch?v=AzYC5hO2uJk
 * @ref https://sourceware.org/newlib/libc.html#Syscalls
 * @ref https://github.com/mroy/stellarap/blob/master/newlib_stubs.c
 */
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

// We have to disable the C library's errno in favor of a global variable
#undef errno
extern int errno;


/**
 * @brief A pointer to a list of environment variables and their values. 
 * 
 * @note For a minimal environment, this empty list is adequate.
 * 
 */
char *__env[1] = { 0 };
char **environ = __env;


/**
 * @brief Exit a program without cleaning up files.
 * 
 * @param status The exit status
 */
void _exit(int status)
{
    __asm("BKPT #0");
}


/**
 * @brief Close the file. This is a minimal implementation. Returns -1.
 * 
 * @param file File descriptor
 * @return Returns zero on success or -1 on error and errno is set.
 */
int _close(int file) {
    return -1;
}


/**
 * @brief Executes the program referred to by pathname. Minimal implementation 
 *        (for a system without processes). Returns -1.
 * 
 * @param pathname Must be a binary executable
 * @param argv An array of pointers to strings passed to the new program as its 
 *             command-line arguments
 * @param envp An array of pointers to strings which are passed as the 
 *             environment of the new program.
 * @return int On success execve does not return. On error -1 is returned, and
 *             errno is set to indicate the error.
 */
int _execve(const char *pathname, char *const argv[], char *const envp[]) {
    errno = ENOMEM;
    return -1;
}


/**
 * @brief Create a new process. Minimal implementation (for a system without 
 *        processes). Returns -1.
 * 
 * @return int On sucess, the PID of the child process is returned in the
 *             parent, and 0 is returned in the child. On failure, -1 is
 *             returned in the parent, no child process is created, and errno
 *             is set to indicate the error.
 */
int _fork(void) {
  errno = EAGAIN;
  return -1;
}


/**
 * @brief Status of an open file.
 * 
 * @param file The file descriptor.
 * @param buf A stat object that is filled with the file's properties.
 * @return int On success, zero is returned. On error, -1 is returned, and 
 *             errno is set appropriately.
 */
int _fstat(int file, struct stat *buf) {
  buf->st_mode = S_IFCHR;
  return 0;
}


/**
 * @brief Returns the process ID of the calling process. This is often used by 
 *        routines that generate unique temporary filenames.
 * 
 * @return int The process ID. For this simple implementation we return 1.
 */
int _getpid(void) {
  return 1;
}


/**
 * @brief Query whether output stream is a terminal.
 * 
 * @param file The file descriptor.
 * @return int Returns 1 if fd is an open file descriptor referring to a 
 *             terminal; otherwise 0 is returned, and errno is set to indicate 
 *             the error. Default to 1.
 */
int _isatty(int file) {
  return 1;
}


/**
 * @brief Send any signal to any process group or process.
 * 
 * @param pid If pid is positive, then signal sig is sent to th process with
 *            the ID specified by pid.
 * 
 *            If pid equals 0, then sig is sent to every process in the process
 *            group of the calling process.
 * 
 *            If pid equals -1, then sig is sent to every process for which the
 *            calling process has permission to send signals, except for
 *            process 1 (init).
 * 
 *            If pid is less than -1, then sig is sent to every process in the
 *            process group whose ID is -pid.
 * @param sig If sig is 0, then no signal is sent, but error checking is still
 *            performed; this can be used to check for the existence of a
 *            process ID or process group ID.
 * @return int On success (at least one signal was sent), zero is returned. On 
 *             error, -1 is returned, and errno is set appropriately. For now
 *             errno is set to EINVAL and it returns -1.
 */
int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}


/**
 * @brief Establish a new name for an existing file.
 * 
 * @param path1 Points to a pathname naming an existing file.
 * @param path2 Points to a pathname naming the new file name to be created.
 * @return int  Upon successful completion, 0 shall be returned. Otherwise, -1 
 *              shall be returned and errno set to indicate the error. For now
 *              we set errno to EMLINK and return -1.
 */
int _link(const char *path1, const char *path2) {
  errno = EMLINK;
  return -1;
}


/**
 * @brief Set position in a file.
 * 
 * @param file The file descriptor to set the offset in.
 * @param offset New offset to set to.
 * @param whence The directive to use when offsetting.
 * @return int Upon successful completion, lseek() returns the resulting offset 
 *             location as measured in bytes from the beginning of the file. On 
 *             error, the value (off_t) -1 is returned and errno is set to 
 *             indicate the error. For now we return 0.
 */
int _lseek(int file, int offset, int whence) {
  return 0;
}


/**
 * @brief Opens a file.
 * 
 * @param fileName The name of the file.
 * @param flags The access mode of the file.
 * @param mode Specifies the permissions to use in case a new file is created.
 * @return int Return the new file descriptor, or -1 if an error occurred 
 *             (in which case, errno is set appropriately). For now we return
 *             -1.
 */
int _open(const char *fileName, int flags, int mode) {
  return -1;
}


/**
 * @brief Read from a file.
 * 
 * @param file The file to read from.
 * @param buf The buffer to read the data into. 
 * @param numBytes The number of bytes to read from the file.
 * @return int On success, the number of bytes read is returned (zero indicates 
 *             end of file), and the file position is advanced by this number.
 *             On error, -1 is returned, and errno is set appropriately. For
 *             now we return 0.
 */
int _read(int file, char *buf, size_t numBytes) {
  return 0;
}


/**
 * @brief Increase the program’s data space by increment bytes. In other words
 *        it increments the size of the heap.
 * 
 * @details More often than not, we want the heap to use all the RAM not used 
 *          by anything else. We therefore set HEAP_START to the first address 
 *          not spoken for in our linker script.
 * 
 * @param increment Increments the program's data space by increment bytes.
 * @return caddr_t On success, sbrk() returns the previous program break. On 
 *                 error, (void *) -1 is returned, and errno is set to ENOMEM.
 */
// caddr_t _sbrk(int increment) {
//     static unsigned char *heap = NULL;
//     unsigned char *prev_heap;

//     if (heap == NULL) {
//         // ! FIXME: _end is not working
//         heap = (unsigned char *)&_edata;
//     }
//     prev_heap = heap;

//     heap += increment;

//     return prev_heap;
// }


/**
 * @brief Status of a file (by name).
 * 
 * @param file The file to get information about.
 * @param st Stores the file information.
 * @return int On success, zero is returned. On error, -1 is returned, and 
 *             errno is set appropriately. For now we return 0.
 */
int _stat(const char *file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}


/**
 * @brief Timing information for current process.
 * 
 * @param buf Buffer to hold struct tms data.
 * @return int The number of clock ticks that have elapsed since an arbitrary 
 *             point in the past. The return value may overflow the possible 
 *             range of type clock_t. On error, (clock_t) -1 is returned, and 
 *             errno is set appropriately. For now we return -1.
 */
int _times(struct tms *buf) {
  return -1;
}


/**
 * @brief Remove a file’s directory entry.
 * 
 * @param name The file name to delete from the file system.
 * @return int On success, zero is returned. On error, -1 is returned, and 
 *             errno is set appropriately. For now we return -1.
 */
int _unlink(const char *name) {
  errno = ENOENT;
  return -1;
}


/**
 * @brief Wait for a child process.
 * 
 * @param status 
 * @return int Returns -1 for now.
 */
int _wait(int *status) {
  errno = ECHILD;
  return -1;
}


/**
 * @brief Write to a file. libc subroutines will use this system routine for 
 *        output to all files, including stdout—so if you need to generate any 
 *        output, for example to a serial port for debugging, you should make 
 *        your minimal write capable of doing this.
 * 
 * @param file The file descriptor to write to.
 * @param buf The buffer to write from. 
 * @param numBytes The number of bytes to write from buf. 
 * @return int On success, the number of bytes written is returned (zero 
 *             indicates nothing was written). On error, -1 is returned, 
 *             and errno is set appropriately.
 */
int _write(int file, const void *buf, size_t numBytes)
{
    // TODO: Make it capable of writing to serial out
    switch (file) {
    case (STDOUT_FILENO): {
        // TODO: Write to UART
        return -1;
    }
    case (STDERR_FILENO): {
        // TODO: Write to UART
        return -1;
    }
    }

    // invalid file descriptor
    errno = EBADF;
    return -1;
}
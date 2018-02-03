//
// Created by xyc on 18-1-31.
//

#ifndef PROJECT_UNP_H
#define PROJECT_UNP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXLINE 4096

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

ssize_t Readline(int, void *, size_t);
ssize_t Readn(int, void *, size_t);
ssize_t Writen(int, void *, size_t);
#endif //PROJECT_UNP_H

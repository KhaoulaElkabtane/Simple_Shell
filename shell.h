#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - A structure to hold numeric and string
 * data in a linked list.
 * @n: Numeric value associated with the node.
 * @s: String value associated with the node.
 * @next: Pointer to the next node in the linked list.
 */
typedef struct liststr
{
	int n;
	char *s;
	struct liststr *next;
} liststr;

/**
 *struct info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	liststr *env;
	liststr *history;
	liststr *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} infocmd;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infocmd *);
} builtin_table;


/* shellLoop.c */
int shellLoop(infocmd *, char **);
int findBuil(infocmd *);
void pathCmd(infocmd *);
void forkCmd(infocmd *);

/* fctString2.c */
int fctCmd(infocmd *, char *);
char *fctduplicate(char *, int, int);
char *fctpath(infocmd *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err1.c */
void erputs(char *);
int eputchar(char);
int putfile(char c, int fd);
int putsfile2(char *str, int fd);

/* fctString.c */
int strlength(char *);
int strcomparison(char *, char *);
char *startsWith(const char *, const char *);
char *strCat(char *, char *);

/* fctString1.c */
char *strcopy(char *, char *);
char *strduplicate(const char *);
void strputs(char *);
int _putchar(char);

/* exits.c */
char *strNcopy(char *, char *, int);
char *strNcat(char *, char *, int);
char *strFindchar(char *, char);

/* fctString3.c */
char **strToWords(char *, char *);
char **strToWords2(char *, char);

/* allocation.c */
char *setMem(char *, char, unsigned int);
void strfree(char **);
void *reallocMem(void *, unsigned int, unsigned int);

/* mem.c */
int freemem(void **);

/* fctString4.c */
int fctActive(infocmd *);
int fctDelim(char, char *);
int fctAlphabetic(int);
int fctConv(char *);

/* err2.c */
int erconv(char *);
void erprint(infocmd *, char *);
int fctDecimal(int, int);
char *convnumber(long int, int, int);
void fctremove(char *);

/* builtin.c */
int fctexit(infocmd *);
int fctcurrent(infocmd *);
int fcthelp(infocmd *);

/* builtin1.c */
int printHistory(infocmd *);
int manAlias(infocmd *);

/* fctBuffer.c */
ssize_t extractInput(infocmd *);
int _getline(infocmd *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void unsetInfo(infocmd *);
void setInfo(infocmd *, char **);
void libInfo(infocmd *, int);

/* env.c */
char *getVarEnv(infocmd *, const char *);
int curEnv(infocmd *);
int setEnvVal(infocmd *);
int unsetEnvVal(infocmd *);
int initEnvList(infocmd *);

/* getenv.c */
char **getEnv(infocmd *);
int unsetEnv(infocmd *, char *);
int setEnv(infocmd *, char *, char *);

/* fctHistory.c */
char *historyfile(infocmd *info);
int creathistory(infocmd *info);
int readHistory(infocmd *info);
int buildHistoList(infocmd *info, char *buf, int linecount);
int renumHistory(infocmd *info);

/* lists.c */
liststr *addToNode(liststr **, const char *, int);
liststr *addEndNode(liststr **, const char *, int);
size_t printList(const liststr *);
int delNodeIndex(liststr **, unsigned int);
void freeList(liststr **);

/* lists1.c */
size_t listlength(const liststr *);
char **listString(liststr *);
size_t fctlist(const liststr *);
liststr *nodeStart(liststr *, char *, char);
ssize_t nodeIndex(liststr *, liststr *);

/* vars.c */
int fctchain(infocmd *, char *, size_t *);
void fctcheck(infocmd *, char *, size_t *, size_t, size_t);
int repAlias(infocmd *);
int repVars(infocmd *);
int repString(char **, char *);

#endif

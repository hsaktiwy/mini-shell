
##################################################################################
[FINAL_PROJET_STRUCTURE_IDEA]
[FEEL_FREE_TO_EDIT_AS_YOU_THINK_FITS]
builtins/
	src: cd.c common.c echo.c env.c exit.c export.c pwd.c unset.c
	header: builtin.h
execution/
	src: execute.c execution_utils.c ...
	header: execution.h
environment/
	src: ft_free_env.c ft_getenv.c ft_init_env.c ft_setenv.c ft_unset_envs.c
	header: environment.h
parser/
	src: parser.c redirection_tools.c redirection.c
	header:
lexer/
	src: lexer.c lexer_tools.c ft_get_* ft_next_.. expand.c expanding_issue.c
	header:
????/
	src: main.c 
	header: 
libft/
	src: everything else hh(u didn't think i was going to write all the files hhhh)
	header: libfh.h
include/
	#All header files
	#+ minishell.h will include all headers
	#+ all files will include minishell.h

Makefile: one makefile for everyting or each with a makefile
##########################################################################$$$########

[x] kill parser_tools.c
{
	bash-3.2$ exit ""
	exit
	bash: exit: : numeric argument required

[export]
{
	>export KEY=VALUE
	+export with no args prints all env
	+KEY is invalid if it starts with anything rather than a-z A-Z except '_'
	+KEY is invalid if it contains anything rather than a-z A-Z 0-9 '_'
	+export KEY+=VALUE  appends the value to the prevuios one found in value
	# +everything that comes after $ is egnored including it
	+if a key already exists and it was exported without a value it keeps its prev val
	+any key added to env without a value will be marked is_export so that it will only be printed when export is called and not env
}


	=================================================================
==2120==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 256 byte(s) in 16 object(s) allocated from:
    #0 0x7f86a2712867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x557dca67e6b8 in ft_split libft/ft_split.c:78
    #2 0x557dca676257 in ft_regx lexer/wildcards_utils.c:48
    #3 0x557dca676403 in add_matchs lexer/wildcards_utils.c:65
    #4 0x557dca6765d8 in local_dir lexer/wildcards_utils.c:90
    #5 0x557dca6768c4 in add_wildcards_to_input lexer/wildcards_utils.c:127
    #6 0x557dca674183 in wildcards_start lexer/wildcards.c:32
    #7 0x557dca6744e9 in process_wildcard_argument lexer/wildcards.c:53
    #8 0x557dca674bee in process_wildcards lexer/wildcards.c:94
    #9 0x557dca674fc8 in iswildcards lexer/wildcards.c:121
    #10 0x557dca66c128 in main lexer/main.c:201
    #11 0x7f86a240bd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

Indirect leak of 32 byte(s) in 16 object(s) allocated from:
    #0 0x7f86a2712867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x557dca67d18a in ft_substr libft/ft_substr.c:25
    #2 0x557dca67e5d7 in splited libft/ft_split.c:56
    #3 0x557dca67e764 in ft_split libft/ft_split.c:85
    #4 0x557dca676257 in ft_regx lexer/wildcards_utils.c:48
    #5 0x557dca676403 in add_matchs lexer/wildcards_utils.c:65
    #6 0x557dca6765d8 in local_dir lexer/wildcards_utils.c:90
    #7 0x557dca6768c4 in add_wildcards_to_input lexer/wildcards_utils.c:127
    #8 0x557dca674183 in wildcards_start lexer/wildcards.c:32
    #9 0x557dca6744e9 in process_wildcard_argument lexer/wildcards.c:53
    #10 0x557dca674bee in process_wildcards lexer/wildcards.c:94
    #11 0x557dca674fc8 in iswildcards lexer/wildcards.c:121
    #12 0x557dca66c128 in main lexer/main.c:201
    #13 0x7f86a240bd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: 288 byte(s) leaked in 32 allocation(s).
root@abdelatif:~/mini-shell# 

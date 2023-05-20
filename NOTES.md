urgent task:
	[ ] LOOK AT THE BOTTOM
	[ ]"ls | > out" "ls | <<l" different behaviar
	[ ]	signals in parent, fork and heredoc
	[ ]	$? should expand to exit status
	[x]	removed global struct
	[x] fix the expand problem exepmple : "minishell > $FalS_variable ls -la ___output will be the ls -la result command"
	[x] I made this ~ exanding to $HOME
	[x] fix redirection case with file_name have NULL and file name have Empty space 
	[x] fix the problem that made the redirection don't work where there is no  command: (exemple : bash-3.2$ << kk or < out or < hello)
	[ ] error management {perror("malloc");
  							exit(EXIT_FAILURE);}
	[x] should add a global struct which will contain the exit status of commands
	[x] creat function destroy env to free t_env
	[x] fix the double erreur display in this case "minishell:$> >"
	[x] added .gitignore file, add files u don't need to push to avoid unnecessary conflicts
		and only commit the files that u have modified(this doesn't include files with modified headers!!)
	[x]do redirection in all types(Parcinf fase)
	[x]replace ast with a simple list only (t_cmd)
	[x]fix the problem where u need to keep argument type (is it from "" or '' or $, not "$"-> is from "" ...)
	[x]Expand variables in here doc
	[x]Expand env using our one env (it must be a linked list [key = "", value = ""])
normal task:
	1 [x] i find a leaks in the env_list that we are using specialy in the OLDPWD= key ? fix it ? (see line 96 in this NOTES)
	2 [ ] fix norminette
	3 [ ] fix leaks if there is 
	4 [ ] fix all erreur printf to print in stderror
	5 [ ] fix this cases : bash3-2$ ls 1>/dev/NULL
	6 [ ] organize the working directory [include->libft + others if neccessary; in src-> seperate each step to it folder]
notes : i made a expand_issue file to fix the problems like:(made bye hsaktiwy)
	$a = "ls -la"
	$b = "| wc -l"
	bash-3.2$ $a
	output : 
		total 168
		-rw-r--r--   1 hsaktiwy  candidate      0 May  6 19:26         >     
		drwxr-xr-x  22 hsaktiwy  candidate    748 May  6 19:35 .
		drwxr-xr-x   4 hsaktiwy  candidate    136 May  3 17:07 ..
		drwxr-xr-x  15 hsaktiwy  candidate    510 May  6 19:42 .git
		-rw-r--r--   1 hsaktiwy  candidate     14 May  6 15:21 .here_doc
		-rw-r--r--   1 hsaktiwy  candidate      0 May  6 19:26 >
		-rw-r--r--   1 hsaktiwy  candidate   2279 May  6 19:06 Makefile
	bash-3.2$ $a $b
	output :
		ls: -l: No such file or directory
		ls: wc: No such file or directory
		ls: |: No such file or directory
	the problem is that we will need to be carfull about this cases
	bash-3.2$ $a "$b"
	output:
		ls: | wc -l: No such file or directory
	where in this case we will need to identifie the diffrence between a argument where it was walled bye \' \" and where there is just simple $variables

	plus i linked the extra argument that apear in this wierd cases :
	case1 : 
	bash-3.2$ ls -la << here_doc > output file
		> jshdja
		> asjkdga
		> kk
		> here_doc
		ls: file: No such file or directory
	where the 'file' input in the case1 will behave like a argument for our first detected commad

COMMAND THAT DOESN'T WORK:
[x]ls -la "|"

NOTE= "You can devide task needed to be done to 2 type urgent one and the normale one"

REPORTS: add a report if u find some bugs or something here pls 
"ls                  <<kk"

List_CMD: linked->token->t_cmd 
Linked_T_CMD :  linked->t_file->a_file


### my notes don't mind them
>>> space and #
export > 888	//FIXED
-shell level	//FIXED

--env -i ./minishell seg--	//FIXED or not
--OLDPWD is not set at first-- //FIXED

+ expand ~ && -- to home //FIXED or not
--handle when full path is specified as the name of the command--
--caling close with invalid file descriptor--
> "ls | > out" "ls | <<l" different behaviar

+test all builtins 


-close fds	//FIXED
-bash-3.2$ /tmp
-bash: /tmp: is a directory ## exit 126
-bash-3.2$ /bin/lsds
-bash: /bin/lsds: No such file or directory ## exit 127
-bash-3.2$ sdsf
-bash: sdsf: command not found ## exit 127

>export KEY=VALUE
+export with no args prints all env
+KEY is invalid if it starts with anything rather than a-z A-Z except '_'
+KEY is invalid if it contains anything rather than a-z A-Z 0-9 '_'
+export KEY+=VALUE  appends the value to the prevuios one found in value
# +everything that comes after $ is egnored including it
+if a key already exists and it was exported without a value it keeps its prev val
+any key added to env without a value will be marked is_export so that it will only be printed when export is called and not env



 ls | | | wc or ls |||| wc
 export "VA=ls|wc" should consider one cmd
 echo '$USER'$USER"$USER" 
 ls           | cat         <           out1 // space problem

 echo $f "$HOME" segmentation fault
 echo $f"$HOME"
 echo $f"$HOME""                         "

 whats this anyway
 root@abdelatif# echo $$$
 1682$

################################## LEAK REPORT #########################################
=TRY TO INVESTIGATE THE ROOT OF THESE LEAKS
<<TEST 1 WITH ONE input AND A WHILE BREAK>>
==4047== Memcheck, a memory error detector
==4047== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==4047== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==4047== Command: ./mini_shell
==4047== 
Displaying a tokens (list) : 
        type : COMMOND
                CMD : |ls|
        CMD type cmd(token) = 0
        CMD count arg = 1
                Data :|-la|->[0]
                cmd_in : 0
                cmd_out : 1
                file_in : (null)
                file_out : (null)
        type : COMMOND
                CMD : |wc|
        CMD type cmd(token) = 0
        CMD count arg = 0
                Data :
                cmd_in : 0
                cmd_out : 1
                file_in : (null)
                file_out : (null)
     24     209    1184
==4047== 
==4047== HEAP SUMMARY:
==4047==     in use at exit: 4 bytes in 1 blocks
==4047==   total heap usage: 306 allocs, 306 frees, 11,170 bytes allocated
==4047== 
==4047== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==4047==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4047==    by 0x11055E: ft_realloc (ft_realloc.c:28)
==4047==    by 0x10F7CB: get_simple_arg (ft_get_simple_arg.c:47)
==4047==    by 0x10B1E2: handleArg (lexer_tools.c:48)
==4047==    by 0x109EA1: lexer (lexer.c:100)
==4047==    by 0x10ACA8: executer (executer.c:150)
==4047==    by 0x10AE75: main (main.c:82)
==4047== 
==4047== LEAK SUMMARY:
==4047==    definitely lost: 4 bytes in 1 blocks
==4047==    indirectly lost: 0 bytes in 0 blocks
==4047==      possibly lost: 0 bytes in 0 blocks
==4047==    still reachable: 0 bytes in 0 blocks
==4047==         suppressed: 0 bytes in 0 blocks
==4047== 
==4047== For lists of detected and suppressed errors, rerun with: -s
==4047== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
<<TEST 2 wwith miltiple inputs>>
=======================================================================================
==839== 13 bytes in 1 blocks are still reachable in loss record 6 of 68
==839==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==839==    by 0x11050A: ft_realloc (ft_realloc.c:28)
==839==    by 0x10F777: get_simple_arg (ft_get_simple_arg.c:47)
==839==    by 0x10ED38: get_cmd (ft_get_cmd.c:48)
==839==    by 0x10B0F0: handleCommand (lexer_tools.c:21)
==839==    by 0x109EC0: lexer (lexer.c:96)
==839==    by 0x10ACE8: executer (executer.c:150)
==839==    by 0x10AEA2: main (main.c:82)
========================================================================================
==839== 16 bytes in 1 blocks are still reachable in loss record 10 of 68
==839==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==839==    by 0x10B0B7: handleCommand (lexer_tools.c:17)
==839==    by 0x109EC0: lexer (lexer.c:96)
==839==    by 0x10ACE8: executer (executer.c:150)
==839==    by 0x10AEA2: main (main.c:82)
=========================================================================================
==839== 16 bytes in 1 blocks are still reachable in loss record 11 of 68
==839==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==839==    by 0x1105F8: ft_lstnew (ft_lstnew.c:19)
==839==    by 0x10B104: handleCommand (lexer_tools.c:22)
==839==    by 0x109EC0: lexer (lexer.c:96)
==839==    by 0x10ACE8: executer (executer.c:150)
==839==    by 0x10AEA2: main (main.c:82)
==========================================================================================
==839== 64 bytes in 1 blocks are still reachable in loss record 21 of 68
==839==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==839==    by 0x10EC28: ini_cmd (ft_get_cmd.c:19)
==839==    by 0x10ECD8: get_cmd (ft_get_cmd.c:42)
==839==    by 0x10B0F0: handleCommand (lexer_tools.c:21)
==839==    by 0x109EC0: lexer (lexer.c:96)
==839==    by 0x10ACE8: executer (executer.c:150)
==839==    by 0x10AEA2: main (main.c:82)
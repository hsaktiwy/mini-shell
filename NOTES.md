urgent task:
	[x] freed everything when exit is called
	[x] ignore from # to end  
	[x]"ls | > out" "ls | <<l" different behaviar
	[x]	signals in parent, fork and heredoc
	[x]	$? should expand to exit status
	[x]	removed global struct
	[x] fix the expand problem exepmple : "minishell > $FalS_variable ls -la ___output will be the ls -la result command"
	[x] I made this ~ exanding to $HOME
	[x] fix redirection case with file_name have NULL and file name have Empty space 
	[x] fix the problem that made the redirection don't work where there is no  command: (exemple : bash-3.2$ << kk or < out or < hello)
	[x] error management {perror("malloc");
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

--env -i ./minishell seg--	//FIXED 
--OLDPWD is not set at first-- //FIXED

+ expand ~ && -- to home //FIXED or not
--handle when full path is specified as the name of the command--
--caling close with invalid file descriptor--

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



 [x] ls | | | wc or ls |||| wc (i think it soved)
 [x]export "VA=ls|wc" should consider one cmd
 [x]echo '$USER'$USER"$USER" 
 [x]echo $f "$HOME" segmentation fault
 [x]echo $f"$HOME"
 export "VA=ls|wc" should consider one cmd
 echo '$USER'$USER"$USER" 
 ls           | cat         <           out1 // space problem

 echo $f "$HOME"
 echo $f"$HOME"
 echo $f"$HOME""                         "

 whats this anyway
 root@abdelatif# echo $$$
 1682$

################################## LEAK REPORT #########################################

########################################################################################
 [x] echo '$USER'$USER"$USER" 

 TO DO LIST
 [x] in redirection not working
 [ ] ls           | cat         <           out1 // space problem
 [ ]> "ls | > out" "ls | <<l" different behaviar

############# builtins testing
[x] exit -21131313
[x] exit -9223372036854775809
[x] exit 9223372036854775808
[x] exit +"100"

[x] export = // SIGSEGV

[x] echo $?HELLO (ft_get_simple_arg i added if(str[k + i + 1] == '?') k++; plus the same for the files expand.c ft_get_doube_quote as the all do the same)
{
output bash-3.2$
	bash-3.2$ echo $?HELLo
	0HELLo
	bash-3.2$ echo $?HELLO
	0HELLO
	bash-3.2$ echo $??
	0?
	bash-3.2$ echo "$?HELLo"
	0HELLo
	bash-3.2$ cat << kk
	> $?HHH
	> KK
	> kk
	0HHH
	KK
	bash-3.2$
our : minishell
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> echo "$?HELLO"
	exit status = 0
	0HELLO
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> echo $??
	exit status = 0
	0?
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> echo $?HELLO
	exit status = 0
	0HELLO
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> cat << kk
	exit status = 0
	> $?HHH
	> KK
	> kk
	0HHH
	KK
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> 
}

############# syntax testing
[x] echo hi | < |
{
our: minishell
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> echo hi | < |
	mini-shell:     syntax error near unexpected token `|'
	exit status = 2
bash :
	bash-3.2$ echo hi | < |
	bash: syntax error near unexpected token `|'
	bash-3.2$ echo $?
	258
notes : 
	wach machi khasna ndisplayiwe exit status 258 ?
}
[x] syntax error  set g_exit_status = 2 

[ ] echo hi | > >>
{
our: minishell
	SHLVL:(2) exit:(2):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> echo hi | > >>
	mini-shell:     syntax error near unexpected token `>>'
	exit status = 2
bash :
	bash-3.2$ echo hi | > >>
	bash: syntax error near unexpected token `>>'
	bash-3.2$ echo $?
	258
}
[x] mini-shell:     syntax error near unexpected token `newline' <<what are the extra spaces>>
{
	hahah ok hadi dartha custum ahaha i did fixed it 
}

[x] cat    <| ls    <<should be erorr>>
{
our: minishell
	SHLVL:(2) exit:(0):~/Users/hsaktiwy/Desktop/mini-shell/mini-shell#minishell:$> cat    <| ls    <
	mini-shell: syntax error near unexpected token `|'
	exit status = 2
bash : 
	bash-3.2$ cat    <| ls    <
	bash: syntax error near unexpected token `|'
	bash-3.2$ echo $?
	258
}

[x]  echo hi <<>

[x] } or { or {} or }{

[x] < ls/ > 		<<nothing should be passed to execution>>

[x] <ls>

// ********************  ?
bash-3.2$ ls -la | | 
bash: syntax error near unexpected token `|'
bash-3.2$ echo $?
258
bash-3.2$ ls -la <
bash: syntax error near unexpected token `newline'
bash-3.2$ echo $?
258

[x] fix this problem plus exit status is 255 not 2
{
bash-3.2$ exit 11111111111111111111111111111111111111111111
exit
bash: exit: 11111111111111111111111111111111111111111111: numeric argument required
}

[x] ++ close open file fds in exit

##################################################################################
#######[FINAL_PROJET_STRUCTURE_IDEA]
#######[FEEL_FREE_TO_EDIT_AS_YOU_THINK_FITS]
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

bash-3.2$ exit ""
exit
bash: exit: : numeric argument required
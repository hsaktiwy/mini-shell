{
	""
	echo $'HOME'
	echo $"HOME"
	exit ""
	echo $"$"
	echo $'$'
}

{
	export USER=
	export =
	export +=
}

{
	>> exit status 1 in redirection error
}

{
	< f < Makefile cat
	ls<dadd				##bash: f: No such file or directory
	ls | < dadd		
	< dadd | ls		##bash: dadd: No such file or directory and ls executed
	should add another flag if there is an error so i don't execute the command.
}	//FIXED

{
	export f=Make
	< $f'file' cat
}	//FIXED
 
{
	<< end cat > 1 | << end cat > 2 | << end cat > 3
	
	should add a function to generate heredoc file names so that each heredoc writes to a different file
}	//FIXED

{
	echo $USER'R'$USER""''""''""'$USER'$USE // cuz u have the last null var after single quotes
}	//FIXED

{
	cd ~ (segfault if HOME unseted)
	fix itls 
}	//FIXED

{
	bash-3.2$ << "$HOME"$test cat
	> $HOME
	> $HOME$test
	$HOME

	<< "$HOME""$test" cat
}

{
	...leaks here:
	./
	ls | echo "$d hello"12 | failed cmd | sleep 10 | echo im wake up rn
	echo "$d hello"12
}

{
	minishell:$> export u="s "
	minishell:$> l$u'-la'
}

{
	< lexer/ /bin | ls > out (message is not correct)
}   //FIXED

{
	< lexer/ /bin | ///// | ok > ///// (message is not correct)
}   //FIXED

{
	< lexer/ /bin | "" | ok > "" (messge is not correct)
}   //FIXED

{
	$HOME (messge is not correct)
}   //FIXED

{
	cat | cat | lscat | ls
	l$u' -la'  // u='s'    lah ismeh lya mnak awdi a hamza
}

{
    echo hi > $p
}

    exit 1 in ^C



test runung bash on  a folder that doesn't exist

#####################################################################
➜  myshell42 git:(abdelatif) ✗ ./minishell 
minibash-3.2$ *.txt
=================================================================
==43307==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000003b2f at pc 0x00010c37ceb3 bp 0x7ffee3892360 sp 0x7ffee3892358
READ of size 1 at 0x602000003b2f thread T0
    #0 0x10c37ceb2 in process_wildcards wildcards.c:92
    #1 0x10c37d7d0 in iswildcards wildcards.c:121
    #2 0x10c36ee13 in main main.c:187
    #3 0x7fff718b9cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

0x602000003b2f is located 1 bytes to the left of 6-byte region [0x602000003b30,0x602000003b36)
allocated by thread T0 here:
    #0 0x10c44317d in wrap_malloc+0x9d (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x4917d)
    #1 0x10c38cb88 in ft_strtrim ft_strtrim.c:45
    #2 0x10c3762f3 in remove_white_spaces expand.c:61
    #3 0x10c376af4 in expand_input expand.c:123
    #4 0x10c36ee06 in main main.c:186
    #5 0x7fff718b9cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

SUMMARY: AddressSanitizer: heap-buffer-overflow wildcards.c:92 in process_wildcards
Shadow bytes around the buggy address:
#####################################################################
<<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end ||| <<end 
<<end
bash: syntax error near unexpected token '|'
and then herdocs before error are opened

#####################################################################
if (maximum here-document count exceeded)
	exit minishell with exit_status 2
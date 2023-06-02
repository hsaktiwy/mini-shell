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
[x] minibash-3.2$ *.txt
[x] <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end ||| <<end 
<<end
bash: syntax error near unexpected token '|'
and then herdocs before error are opened

#####################################################################
if (maximum here-document count exceeded)
	exit minishell with exit_status 2


cat *"'"*
cat *'"'*
cat *" "*
cat *'|'*

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

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
}
{
	< lexer/ /bin | ///// | ok > ///// (message is not correct)
}

{
	< lexer/ /bin | "" | ok > "" (messge is not correct)
}

{
	$HOME (messge is not correct)
}

{
	cat | cat | lscat | ls
	l$u' -la'  // u='s'    lah ismeh lya mnak awdi a hamza
}

#############################################################################
minishell:$> echo "$"?
$?
minishell:$> echo "$""?"
$?
minishell:$> echo "$" "?"
$ ?
minishell:$> echo "$"$? "?"
$0 ?
minishell:$> ./.
minishell: ./.: is a directory

##############################################################################
==5287==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 80 byte(s) in 3 object(s) allocated from:
    #0 0x7f532a155867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55e0804e2a5d in ft_split libft/ft_split.c:78
    #2 0x55e0804d9d1d in fix_in_cmd lexer/expanding_issue.c:23
    #3 0x55e0804da092 in fix_if_whitspace lexer/expanding_issue.c:62
    #4 0x55e0804da2c1 in fix_expanding_issue lexer/expanding_issue.c:88
    #5 0x55e0804d2a88 in main2 lexer/main.c:94
    #6 0x55e0804d2db3 in main lexer/main.c:135
    #7 0x7f5329e4ed8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

Direct leak of 17 byte(s) in 4 object(s) allocated from:
    #0 0x7f532a155867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55e0804e2206 in ft_realloc libft/ft_realloc.c:30
    #2 0x55e0804d6796 in get_single_quote lexer/ft_get_single_quote.c:40
    #3 0x55e0804d611c in get_simple_arg lexer/ft_get_simple_arg.c:39
    #4 0x55e0804d31fc in get_cmd lexer/ft_get_cmd.c:76
    #5 0x55e0804d933c in handleCommand lexer/lexer_tools.c:21
    #6 0x55e0804d8eca in lexer lexer/lexer.c:158
    #7 0x55e0804d2a6f in main2 lexer/main.c:90
    #8 0x55e0804d2db3 in main lexer/main.c:135
    #9 0x7f5329e4ed8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

Direct leak of 15 byte(s) in 4 object(s) allocated from:
    #0 0x7f532a155867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55e0804e2206 in ft_realloc libft/ft_realloc.c:30
    #2 0x55e0804d4d4a in expand_env_var lexer/ft_get_double_quote.c:102
    #3 0x55e0804d6052 in get_simple_arg lexer/ft_get_simple_arg.c:34
    #4 0x55e0804d31fc in get_cmd lexer/ft_get_cmd.c:76
    #5 0x55e0804d933c in handleCommand lexer/lexer_tools.c:21
    #6 0x55e0804d8eca in lexer lexer/lexer.c:158
    #7 0x55e0804d2a6f in main2 lexer/main.c:90
    #8 0x55e0804d2db3 in main lexer/main.c:135
    #9 0x7f5329e4ed8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

Direct leak of 12 byte(s) in 4 object(s) allocated from:
    #0 0x7f532a155867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55e0804e2206 in ft_realloc libft/ft_realloc.c:30
    #2 0x55e0804d55c2 in get_double_quote lexer/ft_get_double_quote.c:148
    #3 0x55e0804d61c0 in get_simple_arg lexer/ft_get_simple_arg.c:44
    #4 0x55e0804d95f2 in handleArg lexer/lexer_tools.c:58
    #5 0x55e0804d8f22 in lexer lexer/lexer.c:160
    #6 0x55e0804d2a6f in main2 lexer/main.c:90
    #7 0x55e0804d2db3 in main lexer/main.c:135
    #8 0x7f5329e4ed8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

Direct leak of 12 byte(s) in 4 object(s) allocated from:
    #0 0x7f532a155867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55e0804e2206 in ft_realloc libft/ft_realloc.c:30
    #2 0x55e0804d62b2 in get_simple_arg lexer/ft_get_simple_arg.c:49
    #3 0x55e0804d95f2 in handleArg lexer/lexer_tools.c:58
    #4 0x55e0804d8f22 in lexer lexer/lexer.c:160
    #5 0x55e0804d2a6f in main2 lexer/main.c:90
    #6 0x55e0804d2db3 in main lexer/main.c:135
    #7 0x7f5329e4ed8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: 136 byte(s) leaked in 19 allocation(s).

#############################################################################
minishell:$> .//
minishell: .//: is a directory

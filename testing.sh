	[ ] expand_issue ?? maybe it should go
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
	[x]$a = "ls -la" 
		bash-3.2$ $a
	[x]$b = "| wc -l"
		bash-3.2$ $a $b
		bash-3.2$ $a "$b"
	[ ]where in this case we will need to identifie the diffrence between a argument where it was walled bye \' \" and where there is just simple $variables
	[ ]{	
			plus i linked the extra argument that apear in this wierd cases :
			[]case1 : 
				bash-3.2$ ls -la << here_doc > output file
					> jshdja
					> asjkdga
					> kk
					> here_doc
					ls: file: No such file or directory
				where the 'file' input in the case1 will behave like a argument for our first detected commad
	}
	[x]ls -la "|"
	[ ]"ls                  <<kk"
	[ ]space and #
	[ ]export > 888	//FIXED
	[ ]shell level	//FIXED
	[ ]env -i ./minishell seg--	//FIXED 
	[ ]OLDPWD is not set at first-- //FIXED
	[ ]expand ~ && -- to home //FIXED or not
	[ ]handle when full path is specified as the name of the command--
	[ ]caling close with invalid file descriptor--
	[ ]test all builtins 
	[ ]close fds	//FIXED
	[ ]bash-3.2$ /tmp
	[ ]bash: /tmp: is a directory ## exit 126
	[ ]bash-3.2$ /bin/lsds
	[ ]bash: /bin/lsds: No such file or directory ## exit 127
	[ ]bash-3.2$ sdsf
	[ ]bash: sdsf: command not found ## exit 127
	[x] ls | | | wc or ls |||| wc (i think it soved)
	[x]export "VA=ls|wc" should consider one cmd
	[x]echo '$USER'$USER"$USER" 

	[ ]export "VA=ls|wc" should consider one cmd

	[x] in redirection not working


	[ ]{
		bash-3.2$ cat << kk
		> $?HHH
		> KK
		> kk
		0HHH
		KK
	}
	[x] echo hi | < |
	[ ]{
		bash :
			bash-3.2$ echo hi | < |
			bash: syntax error near unexpected token `|'
			bash-3.2$ echo $?
			258
	}
	[x] syntax error  set g_exit_status = 2 
	[ ] echo hi | > >>
	[x] cat    <| ls    <<should be erorr>>
	[x]  echo hi <<>
	[x] } or { or {} or }{
	[x] < ls/ > 		<<nothing should be passed to execution>>
	[x] <ls>
	[ ]"ls                  <<kk"
	[x] fix this problem plus exit status is 255 not 2
	[ ]exit 11111111111111111111111111111111111111111111
	[x] ++ close open file fds in exit

{
	>> exit status 1 in redirection error
}

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
	l$u' -la'  // u='s'

}
    [ ]exit 1 in ^C
	[ ]test runung bash on  a folder that doesn't exist
	[ ]{<<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end <<end ||| <<end 
		<<end
		bash: syntax error near unexpected token '|'
		and then herdocs before error are opened
	}
	[ ]{
		if (maximum here-document count exceeded)
		exit minishell with exit_status 2
	}
	[ ]cat *"'"*
	[ ]cat *'"'*
	[ ]cat *" "*
	[ ]cat *'|'*

	[ ]{
		-rw-r--r--  1 aigounad  candidate  5 Jun  1 20:56 ls
		minibash-3.2$ chmod +x ls
		minibash-3.2$ ./ls
	}
{
	bash-3.2$ cat "'"*
	testssssss
	bash-3.2$ cat "*"
	cat: *: No such file or directory
	bash-3.2$ cat '*'
	cat: *: No such file or directory
}

{
	$ cat *b
	$ ./
	>>>>leaks
	##########################################
	==19029==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 720 byte(s) in 30 object(s) allocated from:
    #0 0x7fb84948d867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55611a2dc7e0 in ft_split libft/ft_split.c:78
    #2 0x55611a2d4138 in ft_regx lexer/wildcards_utils.c:48
    #3 0x55611a2d42e4 in add_matchs lexer/wildcards_utils.c:65
    #4 0x55611a2d44b9 in local_dir lexer/wildcards_utils.c:90
    #5 0x55611a2d2fba in iswildcards lexer/wildcards.c:98
    #6 0x55611a2d0f91 in handle_command lexer/lexer_tools.c:87
    #7 0x55611a2d02bc in lexer lexer/lexer.c:109
    #8 0x55611a2c9d3c in main2 lexer/main.c:96
    #9 0x55611a2ca586 in main lexer/main.c:196
    #10 0x7fb849186d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

Indirect leak of 570 byte(s) in 60 object(s) allocated from:
    #0 0x7fb84948d867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x55611a2db2b2 in ft_substr libft/ft_substr.c:25
    #2 0x55611a2dc6ff in splited libft/ft_split.c:56
    #3 0x55611a2dc88c in ft_split libft/ft_split.c:85
    #4 0x55611a2d4138 in ft_regx lexer/wildcards_utils.c:48
    #5 0x55611a2d42e4 in add_matchs lexer/wildcards_utils.c:65
    #6 0x55611a2d44b9 in local_dir lexer/wildcards_utils.c:90
    #7 0x55611a2d2fba in iswildcards lexer/wildcards.c:98
    #8 0x55611a2d0f91 in handle_command lexer/lexer_tools.c:87
    #9 0x55611a2d02bc in lexer lexer/lexer.c:109
    #10 0x55611a2c9d3c in main2 lexer/main.c:96
    #11 0x55611a2ca586 in main lexer/main.c:196
    #12 0x7fb849186d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
	####################################################################
}

{
	echo $*
}

unset aa
unset "" //return value
ls | <<l


LEAKS:
command: echo $>
==8791==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 1 byte(s) in 1 object(s) allocated from:
    #0 0x7ff6d9dce867 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x564c34fb7fc6 in ft_strtrim libft/ft_strtrim.c:45
    #2 0x564c34fad2fe in remove_white_spaces lexer/expand_input.c:23
    #3 0x564c34fae517 in expand_input lexer/expand_input.c:106
    #4 0x564c34fa4be6 in get_file lexer/ft_next_arg.c:164
    #5 0x564c34fa8366 in handle_outredirect lexer/lexer.c:84
    #6 0x564c34fa896b in lexer lexer/lexer.c:105
    #7 0x564c34fa2d5c in main2 lexer/main.c:98
    #8 0x564c34fa379b in main lexer/main.c:227
    #9 0x7ff6d9ac7d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
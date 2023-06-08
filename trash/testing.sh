	[ ] expand_issue ?? maybe it should go
	[x] freed everything when exit is called
	[x] ignore from # to end  
	[x]"ls | > out" "ls | <<l" different behaviar
	[x]	signals in parent, fork and heredoc
	[x] fix the expand problem exepmple : "minishell > $FalS_variable ls -la ___output will be the ls -la result command"
	[x] I made this ~ exanding to $HOME
	[x] fix redirection case with file_name have NULL and file name have Empty space 
	[x] fix the problem that made the redirection don't work where there is no  command: (exemple : bash-3.2$ << kk or < out or < hello)
	[x] error management {perror("malloc");
  							exit(EXIT_FAILURE);}
	[x]fix the problem where u need to keep argument type (is it from "" or '' or $, not "$"-> is from "" ...)
	[x]Expand variables in here doc
	[x]{
		export $a="ls -la" 
		$a
	}
	[x]{
		export b="| wc -l"
		$b
		"$b"
	}
	[ ]{	
		ls -la << here_doc > output file
		> kk
		> here_doc
		ls: file: No such file or directory
		where the 'file' input in the case1 will behave like a argument for our first detected commad
	}
	[x]ls -la "|"
	[ ]"ls                  <<kk"
	[ ]space and #
	[x]export > 888	//FIXED
	[x]shell level	//FIXED
	[ ]OLDPWD is not set at first-- //FIXED
	[ ]expand ~ && -- to home //FIXED or not
	[ ]handle when full path is specified as the name of the command--
	[ ]caling close with invalid file descriptor--
	[ ]test all builtins 
	[x] ls | | | wc or ls |||| wc (i think it soved)
	[x]export "VA=ls|wc" should consider one cmd
	[x]echo '$USER'$USER"$USER" 
	[ ]export "VA=ls|wc" should consider one cmd
	[ ]{
		cat << kk
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



TAKE YOUR TIME AND TRY NOT BREAK SOMETHING ELSE WHILE FIXING THIS
{
	[herdoc doesn't work after syntax error]
	ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3

	echo segfault <"<<<"<<amazing
	something
	amazing
}

}
	echo 1 '||' echo 2
}

{	
	[not working+heap-use-after-free]
	export T="<<" 
	$T.	

	export T="|"
	$T$T$T$T$T$T$T
}



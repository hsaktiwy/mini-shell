
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
	[x]echo $f "$HOME" segmentation fault
	[x]echo $f"$HOME"
	[ ]export "VA=ls|wc" should consider one cmd
	[ ]echo '$USER'$USER"$USER" 
	[ ]ls           | cat         <           out1 // space problem
	[ ]echo $f "$HOME"
	[ ]echo $f"$HOME"
	[ ]echo $f"$HOME""                         "
	[x] echo '$USER'$USER"$USER" 
	[x] in redirection not working
	[ ] ls           | cat         <           out1 // space problem
	[ ]> "ls | > out" "ls | <<l" different behaviar
	[x] exit -21131313
	[x] exit -9223372036854775809
	[x] exit 9223372036854775808
	[x] exit +"100
	[x] export = // SIGSEGV
	[x] echo $?HELLO (ft_get_simple_arg i added if(str[k + i + 1] == '?') k++; plus the same for the files expand.c ft_get_doube_quote as the all do the same)
	[ ]echo $?HELLo
	[ ]echo $?HELLO
	[ ]echo $??
	[ ]echo "$?HELLo"
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

	[x] fix this problem plus exit status is 255 not 2
	[ ]exit 11111111111111111111111111111111111111111111
	[ ]exit: 11111111111111111111111111111111111111111111: numeric argument required
	[x] ++ close open file fds in exit

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
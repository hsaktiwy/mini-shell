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
	bash-3.2$ << "$HOME"$test cat
	> $HOME
	> $HOME$test
	$HOME

	<< "$HOME""$test" cat
}

{
	cd ~ (segfault if HOME unseted)
	fix itls 
}	//FIXED

{
	...leaks here:
	ls | echo "$d hello"12 | failed cmd | sleep 10 | echo im wake up rn
	echo "$d hello"12
}

{
	minishell:$> l$u'-la'
	minishell:$> export u="s "
}

### TO_DO_LIST
	+add signal names
	- . ..
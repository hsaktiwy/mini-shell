#!/bin/bash

TEST_ARRAY=(
'##################		    BUILTINS			#################'
#### PWD ####
'pwd'
'pwd "useless argument"'
'unset PWD | pwd'
#### ECHO ####
'echo -n test1'
'echo -n "test1 test2"'
'echo -n "test1 test2" test3'
'echo -n test1		test2'
'echo test1 -n'
'echo "test1 -n"'
'echo -n -n test1'
'echo -n -n -n -n -n test1'
'echo "  -nn "'
'echo "-n test1 -n test2"'
'echo "test1 -n test2"'
'echo ~42'
'echo -n -n -nasd'
'echo -n -n -n-nnnnn'
'echo -n -nnnnnnn -n -nnn -nnnnn -n-n'
'echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain'
'echo -n -n -n-n'
'echo cd ~'
'echo "cd ~"'
'echo ""$?""'
'echo $"HOME"$USER'
'echo $"HOM"E$USER'
'echo "exit_code ->$? user ->$USER home -> $HOME"'
'echo $"HOME"'
'echo $"42$"'
'echo """"""""$USER""""""""'
'echo "$ "'
'echo hi >./outfiles/outfile01 | echo bye'
'echo <123 <456 hi | echo 42'
'echo "$?"'
'echo "cat lol.c | cat > lol.c"'
'echo $USER =intergalaktikus miaf*szomez'
'echo -n"-n" bonjour'
'echo text"$USER"'
'echo "text"   "$USER"    "$USER"'
'echo ''''''''''$USER'''''''''''
'echo """"""""$USER""""""""'
'echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER '''
'echo "text" "text$USER" ... "$USER"'
'echo'
'echo $USER$TESTNOTFOUND$HOME$'
'echo $USER$TESTNOTFOUND$HOME$WTF$PWD'
'echo | cat -e'
'echo hola buenos dias | cat -e'
'echo -n hola que tal bocadillo digital | cat -e'
#### ENV ####
'env | grep USER'
#### EXPORT ####
'export =============123'
'export ='
'export =42'
"export ''=''"
'export ""=""'
'export export'
'export echo'
'export cd'
'export test'
'export TEST'
'export $? '
'export TEST'
'export TEST='
'export TEST=123'
'export ___TEST=123'
# 'export --TEST=123'
"export ''=''"
'export "="="="'
"export '='='='"
'export TE-ST=100'
# 'export -TEST=100'
'export TEST-=100'
'export _TEST=100'
'export =========='
'export 1TEST='
'export ""=""'
'export TES=T=""'
'export TE+S=T=""'
'export TES.T=123'
'export TES.T=123'
'export TES+T=123'
'export TES=T=123'
'export TES}T=123'
'export TES{T=123'
'export TES-T=123'
'export _TEST=123'
'export TES_T=123'
'export TEST_=123'
'export TE*ST=123'
'export TES#T=123'
'export TES@T=123'
'export TES!T=123'
'export TES$?T=123'
'export =============123'
'export +++++++=123'
'export ________=123'
'export TES^T=123'
'export TES!T=123'
'export TES\~T=123'
'export TEST+=100'
'export TES_T=123'
'export Z=z | echo $Z'
'export A=a B=b C=c'
'export zz zzz= zzzz=asd | echo $zz$zzz$zzzz| export | grep zz'
'export =a | echo $a'
'export /dont/export/this=hola | export | grep /dont/export/this'
'export A=a=a=a=a=a| echo $A'
'export A B C| echo $A$B$C'
'export $'
'export ?=42'
#### UNSET ####
'unset ""'
'unset ='
'unset "="'
'unset ""='
'unset =""'
'unset =='
'unset ?'
'unset "?"'
'unset $'
'unset "$"'
'unset $""'
'unset doesntexist'
'unset OLDPWD '
'unset PATH '
'unset TES.T'
'unset TES+T'
'unset TES=T'
'unset TES}T'
'unset TES{T'
'unset TES-T'
'unset _TEST'
'unset TES_T'
'unset TEST_'
'unset TE*ST'
'unset TES#T'
'unset TES@T'
'unset TES!T'
'unset TES$?T'
'unset ============'
'unset +++++++'
'unset ________'
'unset export'
'unset echo'
'unset pwd'
'unset cd'
'unset unset'
'unset sudo'
'unset TES^T'
'unset TES!T'
'unset TES\~T'
'unset'
'export A=a | unset A | echo $A'
'export A=a B=b C=c | unset A asd B asd | echo $A$B$C'
#### CD ####
'cd | pwd'
'unset HOME | cd | pwd'
'cd .| pwd'
'cd ..| pwd'
'cd ..| echo $OLDPWD| pwd'
'unset OLDPWD| cd .. | echo $OLDPWD| pwd'
"cd ' /'| pwd"
'cd ../../ | pwd'
'cd ../../../../../../.. | pwd'
'cd dirwithoutpermissions'
#### EXIT ####
'exit 9223372036854775807'
'exit something somethingv2'
'exit 0 0'
'exit'
'exit ""'
'exit "+100"'
'exit "-100"'
'exit -9223372036854775805'
'exit 0'
'exit 10'
'exit 42'
'exit 1'
'exit +++++'
'exit ++++++'
'exit +1'
'exit ++1'
'exit ++12560'
'exit -----'
'exit ------'
'exit -1'
'exit --1'
'exit -12560'
'exit --12560'
'exit 255'
'exit 1 2'
'exit 1 2 3'
'exit A'
'exit A 2 3'
'exit "A"'
'exit "+++"'
'exit ++++3193912939'
'exit 01'
'exit 001'
'exit 0001'
'exit +++000'
'exit ++++000'
'exit ---000'
'exit ----000'
'exit "something"'
'exit x'
'exit echo'
'exit cd ..'
'exit exit'
'exit 42 42 42 42 42 '
'exit'
'exit 42'
'exit -42'
'exit 512'
'exit 1407'
'exit 21 42'
'exit notanumber'
'################	NO ENVIRONMENT (env -i ./minishell)	#################'
'cd'
'pwd'
'echo $PWD'
'cd .. | echo $OLDPWD'
'./lscp'
'export'
'echo $USER'
'echo $HOME'
'echo $HOME$NOTHING$USER$'
'pwd'
'unset PATH'
'cd -'
'pwd'
'echo "no env over here"'
'exit asd'
'exit 5'
'exit 5 asd'
'unset OLDPWD'
'pwd'
'/bin/ls'
'./ls'
'export T=bazd'
'echo "$T" "meg"'
'cd ..'
'exit'
'pwd'
'cd'
'pwd'
'|'
'""'
"''"
'cd .'
'################		COMMAND EXECUTION	        #################'
'.'
'..'
'""'
'                              '
'			'
'ls'
'/bin/ls'
'./lscp'
'cd dir | ../lscp'
'cd dir/encoreuneautredir | ../../lscp'
'df -h | head -2'
'/'
'../'
'/..'
'..'
'ls imnotaflag meneither'
'idontexist'
'./meneither'
'./dir'
# 'touch ucantexecme.e | chmod 000 ucantexecme.e | ./ucantexecme.e'
'################   		SYNTAX ERRORS			#################'
'|'
'|'
'|b'
'a|||b'
'> > a'
'< < a'
'< >> a'
'>>> a'
'<<<< a'
'a<<<<'
'pwd >|'
'|pwd'
'pwd ||'
'################		    QUOTES			#################'
'echo "$HOME"'
#"echo '\$HOME'"
# "echo ' \"\$HOME\" '"
# "echo \"'\$HOME'\""
# "echo \" '\$PWD' \\\"\$PWD\\\" '\$PWD' \"" "echo \"\\\$HOME\""
# "echo \"'\$'\""
#"echo \\\\\n"
# "echo \"< no pipe | or semicolon will | stop me >\""
'bash -c "I am not a command" "Im the program name"'
'pwd" should not work"'
'echo\" should not work neiter\"'
'################		    PIPES			#################'
'env | sort | grep -v SHLVL | grep -v ^_'
'cat /etc/passwd | grep oi'
'export GHOST=123 | env | grep GHOST'
'/bin/echo 1 | grep 1'
'/bin/echo 1 | grep 2'
'ifconfig | grep ":"'
'ifconfig | grep nothing'
'cd .. | echo "42"'
'echo 42 | cat -e'
'echo 42 | echo no | echo smth | grep 42'
'echo 42 | echo no | echo smth | grep no'
'echo 42 | echo no | echo smth | grep smth'
'/bin/env | grep "_="'
'/bin/env | grep "SHLVL"'
'/bin/echo 1 | kaka'
'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
'/bin/echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
'ls -la ../ | grep "."'
'unset TEST | cat -e'
'ls | cat asd'
'echo 5 + 3 | bc'
'ls | wc | wc -l | bc'
'echo "cat traveler" | cat | cat | cat | cat | cat | cat'
'################	        RIGHT REDIRECTION		#################'
'> a | ls'
'pwd > a | cat a'
'ls > a -f | cat a'
'echo entre el clavel y la rosa > a su majestad es coja| cat a'
'> a echo cucu cantaba la rana| cat a'
'echo "redirection party trick" > a > b > c > d | ls | cat d'
'notacommand > a'
'pwd > dir'
'ls > a imnotaflag meneither'
'################	        DOUBLE REDIRECTION		#################'
'>> a| ls'
'pwd >> a| cat a'
'echo double the redirection double the fun >> a | cat a'
'pwd >> a | echo apendicitis >> a | cat a'
'echo entre el clavel y la rosa >> a su majestad es coja | cat a'
'>> a echo cucu cantaba la rana| cat a'
'echo "party trick x2" >> a >> b >> c >> d | ls | cat d'
'notacommand >> a'
'pwd >> dir'
'ls >> a imnotaflag meneither'
'################	    	LEFT REDIRECTION		#################'
'grep hi <./test_files/infile'
'grep hi "<infile" <         ./test_files/infile'
'grep hi <./test_files/infile_big <./test_files/infile'
'cat <"./test_files/file name with spaces"'
'cat <./test_files/infile_big ./test_files/infile'
'cat <"1""2""3""4""5"'
'cat <"./test_files/infile"'
'echo <"./test_files/infile_big" | cat <"./test_files/infile"'
'echo <"./test_files/infile_big" | cat "./test_files/infile"'
'echo hi | cat <"./test_files/infile"'
'echo hi | cat "./test_files/infile"'
'cat <"./test_files/infile" | echo hi'
'cat <"./test_files/infile" | grep hello'
'cat <"./test_files/infile_big" | echo hi'
'cat <missing'
'cat <missing | cat'
'cat <missing | echo oi'
'cat <missing | cat <"./test_files/infile"'
'echo <123 <456 hi | echo 42'
'ls >./outfiles/outfile01'
'ls >         ./outfiles/outfile01'
'ls >./outfiles/outfile01 >./outfiles/outfile02'
'ls >./outfiles/outfile01 >./test_files/invalid_permission'
'ls >"./outfiles/outfile with spaces"'
'ls >"./outfiles/outfile""1""2""3""4""5"'
'ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"'
'ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission'
'cat <"./test_files/infile" >"./outfiles/outfile01"'
'echo hi >./outfiles/outfile01 | echo bye'
'echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye'
'echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye'
'echo hi >./test_files/invalid_permission | echo bye'
'echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye'
'cat <"./test_files/infile" >./test_files/invalid_permission'
'cat >./test_files/invalid_permission <"./test_files/infile"'
'cat <missing >./outfiles/outfile01'
'cat >./outfiles/outfile01 <missing'
'cat <missing >./test_files/invalid_permission'
'cat >./test_files/invalid_permission <missing'
'cat >./outfiles/outfile01 <missing >./test_files/invalid_permission'
'ls >>./outfiles/outfile01'
'ls >>      ./outfiles/outfile01'
'ls >>./outfiles/outfile01 >./outfiles/outfile01'
'ls >./outfiles/outfile01 >>./outfiles/outfile01'
'ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02'
'ls >>./outfiles/outfile01 >>./outfiles/outfile02'
'ls >>./test_files/invalid_permission'
'ls >>./test_files/invalid_permission >>./outfiles/outfile01'
'ls >>./outfiles/outfile01 >>./test_files/invalid_permission'
'ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02'
'ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02'
'ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing'
'echo hi >>./outfiles/outfile01 | echo bye'
'echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye'
'echo hi >>./test_files/invalid_permission | echo bye'
'echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye'
'cat <minishell.h>./outfiles/outfile'
'cat <minishell.h|ls'
'touch a | < a'
'echo pim pam > pum | cat < pum'
'echo ayayay > a| echo im a butterfly > b | cat < a < b'
'touch a b c| echo sorry > d| cat < a < b < c < d'
'echo ayayay > a | cat < doesnotexist < a'
'< doesnotexist'
'cat < doesnotexist'
'cat < dir'
'################		    MINE			#################'
'echo my test'
'echo bonjour  ls'
'echo bonjour > test 1 [leaks]'
'cd $HOME/Documents'
'echo >'
'echo -n -n -nnnn -nnnnm'
'unset var1'
'export ""'
'unset ""'
'echo test > file test1 [+leaks]'
'$'
'not_cmd bonjour > salut'
'cat Makefile | grep pr | head -n 5 | cat test'
'cat Makefile | grep pr | head -n 5 | hello'
'echo bonjour >>> test'
'echo bonjour > > out'
'echo 2 >> outfile1 > outfile2'
'echo 2 > outfile1 >> outfile2'
'cat < test'
'echo bonjour > $test'
'file_name_in_current_dir'
'$bla'
'export var ="cat Makefile | grep >"'
'export "test=ici"=coucou'
'c$var Makefile'
'$LESS$VAR'
'/bin/echo bonjour'
'not_cmd'
'sleep 1 | exit'
'echo bonjour > $test w t'
'"exit retour a la ligne"'
'minishell'
'cat diufosgid'
' exit '
'exit -10'
'exit +10'
'echo "$HOME"'
'echo "$""HOME"'
'> log echo coucou'
'echo hudifg d | | hugdfihd'
'echo'
'echo simple'
'echo -n simple'
"echo '\'"
'cd'
'cd .'
'cd ~'
'cd /'
'cd no_file'
'cd a b c d'
'pwd a'
'pwd a b c d'
'export LOL=lala ROR=rara'
'unset LOL ROR'
'export "HI= hi"'
'export "HI =hi"'
'/bin/ls'
'echo $?'
'l^Ds'
'| echo'
'> a ls > b < Makefile'
'echo > a Hello World!'
'> a echo Hello World!'
'cat < Makefile | grep gcc > output'
'exit 0 | exit 1'
'exit 1 | exit 0'
'ls -la "|"'
'ls           | cat         <           outfile1'
'echo $f "$HOME"'
'echo $f"$HOME"'
'echo $USER$USER"$USER" '
'echo $f "$HOME"'
'echo $f"$HOME"'
'echo $f"$HOME""                         "'
'echo "$USER"$USER"$USER"'
'ls           | cat         <           outfile1'
'ls | > out'
'exit -21131313'
'exit -9223372036854775809'
'exit 9223372036854775808'
'exit +100'
'export ='
'echo $?HELLO'
'echo $?HELLo'
'echo $?HELLO'
'echo $??'
'echo "$?HELLo"'
'exit 11111111111111111111111111111111111111111111'
'""'
"echo $'HOME'"
'echo $"HOME"'
'exit ""'
'echo $"$"'
"echo $'$'"
'export USER='
'export ='
'export +='
'< f < Makefile cat'
'ls<dadd'
'ls | < dadd'
'dadd | ls'
'< lexer/ /bin | ls > out'
'< lexer/ /bin | ///// | ok > /////'
'< lexer/ /bin | "" | ok > ""'
'$HOME'
'cat | cat | lscat | ls'
'echo hi > $p'
'################   		WILDCARDS			#################'
#"cat *"\'"*"
"cat *'\"'*"
'cat *" "*'
"cat *'|'*"
'echo $*'
'################		    SEGV			#################'
'<>'
'echo |< echo segf'
'echo >          >           < "echo"'
'echo >          >         | echo kekw'
'echo >          >         | echo super valid'
'echo <          <         > echo'
'echo <  < <         > ok'
'echo <  < | echo ok'
'echo <  < |    < ok'
'echo <      < |    > echo'
'echo >>| echo super valid'
'echo >>< "echo"'
'echo < < < echo seegf'
'echo > > < "echo"'
'echo > > | echo kekw'
'echo > > | echo super valid'
'echo < < > echo'
'echo < < < > ok'
'echo >>| echo kekw'
'echo | < echo segf'
'echo <<| echo ok'
'echo <<|< ok'
'echo <<|> echo'
'echo <<> echo'
'echo <<<> ok'
'echo segfault <"<<<"<<amazing'
'amazing'
'echo seg < > echo seg'
'echo seg > < echo segf'
'echo seg < < > echo segf'
'echo seg < < < > echo segf'
'echo segf > | echo is this invalid'
'echo segf < | < echo super valid'
'echo < < | echo ok'
'echo < < | < ok'
'echo < < | > echo'
'echo segfault < " < < < " < < amazing'
'amazing'
'echo seg <  > echo seg'
'echo seg >  < echo segf'
'echo seg <      < > echo segf'
'echo seg <      < <    > echo segf'
'echo <      <     < echo seegf'
'echo |      < echo segf'
'echo segf >     | echo is this invalid'
'echo segf <         |        < echo super valid'
'echo segfault <"    <   <   <"  <   <   amazing'
'amazing'
# 'echo seg <> echo seg'
'echo seg >< echo segf'
'echo seg <<> echo segf'
'echo seg <<<> echo segf'
'echo segf <|< echo super valid'
'">>" asd'
'>">" asd'
'/bin/rm -f ">"'
'cat $USER'
'"echo "'
'"echo -nnnnn"'
'"ECho" -n -nnn"" "-"nnnnn'
'"ECHO" "-n"'
"ECHO '''''-''n'"
"echo '' -n"
'echo "" "" "" -n -n -n -n'
'why'
'not'
'$USER'
'"ECHO"'
'"PWD"'
'echo "-nnnnn "'
'ECHO -nn'
'ECHO -n -n'
'ECHO "-"""n""n""n""n""n""nnnnnn-n'
'ECHO "-"""n""n""n""n""n""nnnnnn -n'
'LS'
'Ls'
'lS'
'ls'
'PWD'
'pWD'
'pwd'
'pwD'
'EXPORT'
'EXIT 123'
'Exit'
'e""""""""""""cho'
'OLDPWD'
'USER'
'" ls"'
'" cat"'
'" echo"'
'" PWD"'
'" pwd"'
'"PWD "'
'"pwd "'
"'pwd '"
'################		    EXTRAS			#################'
"echo 1 '||' echo 2"
'ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3'
'unset ?'
)

usage() {
    printf "usage: ./unit_test.sh [--help | -h] [--no-error | -n] [--builtins | -b] [--no-environment | -e]\n"
    printf "                      [--cmd-execution | -c] [--syntax-error | -s] [--quotes | -q] [--pipes | -p]\n"
    printf "                      [--right-redirection | -r] [--left-redirection | -l] [--double-redirection | -d]\n"
    exit
}

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
YELLOW=$(tput setaf 3)
ROSITA=$(tput setaf 5)
BLUE=$(tput setaf 4)
MARRONMIERDA=$(tput setaf 8)
COLORBONITO=$(tput setaf 12)
NC=$(tput sgr0)

HELP=0
ERROR=1
DFL_TEST=1
TO_TEST=()
OTHER_ARGUMENTS=()
for arg in "$@"
do
    case $arg in
	-h|--help)
	HELP=1
	shift
	;;
        -n|--no-error)
	ERROR=0
        shift
        ;;
	-b|--builtins)
	DFL_TEST=0
	TO_TEST+=('BUILTINS')
	shift
	;;
	-e|--no-environment)
	DFL_TEST=0
	TO_TEST+=('ENVIRONMENT')
	shift
	;;
	-c|--cmd-execution)
	DFL_TEST=0
	TO_TEST+=('EXECUTION')
	shift
	;;
	-s|--syntax-error)
	DFL_TEST=0
	TO_TEST+=('SYNTAX')
	shift
	;;
	-q|--quotes)
	DFL_TEST=0
	TO_TEST+=('QUOTES')
	shift
	;;
	-p|--pipes)
	DFL_TEST=0
	TO_TEST+=('PIPES')
	shift
	;;
	-r|--right-redirection)
	DFL_TEST=0
	TO_TEST+=('RIGHT')
	shift
	;;
	-l|--left-redirection)
	DFL_TEST=0
	TO_TEST+=('LEFT')
	shift
	;;
	-m|--mine)
	DFL_TEST=0
	TO_TEST+=('MINE')
	shift
	;;
	-w|--wildcards)
	DFL_TEST=0
	TO_TEST+=('WILDCARDS')
	shift
	;;
	-segv|--segv)
	DFL_TEST=0
	TO_TEST+=('SEGV')
	shift
	;;
	-d|--double-redirection)
	DFL_TEST=0
	TO_TEST+=('DOUBLE')
	shift
	;;
	-extras)
	DFL_TEST=0
	TO_TEST+=('EXTRAS')
	shift
	;;
	*)
	OTHER_ARGUMENTS+=("$1")
        shift
        ;;
    esac
done

for args in ${OTHER_ARGUMENTS[@]}
do
    printf "${RED}Error:$NC $args: not a valid option\n\n"
    usage
done

if [[ $HELP -eq 1 ]]
then
    usage
fi

if [[ ! -f ../Makefile ]]; then printf "${RED}Error:$NC There is no Makefile to build your minishell in ../"
    printf "\nMake sure to clone this repo in the root of your project\n"
    printf "\n${RED}aborting test...\n\n$NC"
    exit 1
fi

make -C ..

if [[ ! -f ../minishell ]]; then
    printf "${RED}Error:$NC There is no executable called minishell in ../"
    printf "\n\n${RED}aborting test...\n\n$NC"
    exit 1 
fi

cp ../minishell .
printf "copying your minishell to the current directory...\n"

rm -rf diff.txt

if  [[ ! -d dir || ! -d dir/encoreuneautredir ]]; then
    mkdir dir dir/encoreuneautredir
    printf "creating directories ${ROSITA}dir$NC, ${ROSITA}dir/encoreuneautredir$NC...\n"
fi
if [[ ! -d dirwithoutpermissions ]]; then
    mkdir -m 0000 dirwithoutpermissions
    printf "creating directory ${ROSITA}dirwithoutpermissions$NC...\n"
fi
cp $(which ls) lscp
printf "%s\n" "copying ${ROSITA}$(which ls)$NC to ${ROSITA}lscp$NC..."

printf "\n\t\t\t    ${YELLOW}[ MINISHELL UNIT TEST ]$NC\n\n\n"

#KEYWORD=esternocleidomastoideo ###############
#echo "echo $KEYWORD" > testfile #############
#./minishell < testfile > hpc ###############
#sed "s/$KEYWORD//" hpc > hp #################

TOTAL=0
ENV=""
for val in "${TEST_ARRAY[@]}"
do
    if [[ "$val" = *ENVIRONMENT* ]]
    then
	ENV="env -i"
    elif [[ "$val" = *EXECUTION* ]]
    then
	ENV=""
    fi
    if [[ "$val" = *####* ]]
    then
	if [[ DFL_TEST -eq 1 ]]; then
	    printf "%s" "${NC}$val"
	else
	    TEST_SECTION=0
	    for section in ${TO_TEST[@]}
	    do
		if [[ "$val" = *$section* ]]; then
		    printf "%s" "${NC}$val"
		    TEST_SECTION=1
		    if [[ $ERROR == 1 ]]; then
			printf " ${COLORBONITO}STDERR$NC"
		    fi
		    continue;
		fi
	    done
	fi
	if [[ $ERROR == 1 && $DFL_TEST == 1 ]]; then
	    printf " ${COLORBONITO}STDERR$NC"
	fi
	if [[ $DFL_TEST == 1 || $TEST_SECTION == 1 ]]; then
	    printf "\n"
	fi
	continue 
    fi
    if [[ $DFL_TEST -eq 0 && $TEST_SECTION -eq 0 ]]
    then
	continue
    fi
#	echo "$val" > testfile ########
    TESTOK=0
    $ENV bash -c "$val" minishell > out1 2> err1
    RET1=$?
    rm -rf a b c d
    $ENV ./minishell -c "$val" > out2 2> err2 ######   #####
    RET2=$?
#	awk 'NR==FNR{a[$0]=1;next}!a[$0]' out2 hp > p #############3
#	printf "${YELLOW}p is$NC $(cat p)\n" ##################
#	awk 'NR==FNR{a[$0]=1;next}!a[$0]' hp out2 > pc ##############
#	printf "${YELLOW}pc is$NC $(cat pc)\n" ##################
#	printf "${YELLOW}out2 was$NC\n $(cat out2)\n" ##############
#	sed "s/$(cat p)//" pc > out2 ################### 
#	printf "${YELLOW}now out2 is$NC $(cat out2)\n" ####################
    rm -rf a b c d p pc ###############
    if [[ $(uname) == "Darwin" ]]; then
        sed -i "" 's/line 0: //' err1
	#	sed -i "" 's/.*minishell: -c: `.*//' err1
	#	sed -i "" 's/ -c://' err1
    else
        sed -i 's/line 0: //' err1
	#	sed -i 's/.*minishell: -c: `.*//' err1
	#	sed -i 's/ -c://' err1
    fi
    if [[ $(cat out2) == "exit" ]];then
	echo exit >> out1
    fi
    DIFF=$(diff out1 out2) 
    ERRDIFF=$(diff err1 err2)
    if [[ "$DIFF" == "" && $RET1 == $RET2 ]]; then
	TESTOK=1
    fi
    if [[ $TESTOK == 0 || ($ERROR == 1 && $ERRDIFF != "" ) ]]
    then
	if [[ $ENV == "" ]]; then
	    printf "%s\n" "${YELLOW}$val$NC" >> diff.txt
	else
	    printf "%s\n" "${YELLOW}$ENV ./minishell: $val$NC" >> diff.txt
	fi
	printf "${ROSITA}< bash       (exited with %d)$NC\n" "$RET1" >> diff.txt
	printf "${ROSITA}> minishell  (exited with %d)\n$NC" "$RET2" >> diff.txt
    fi

    if [[ $TESTOK == 1 ]]
    then
	PASSED=$((PASSED+1))
	printf "%-80s[PASS]$NC" "${GREEN}$val"
    else
	printf "%-80s[FAIL]$NC" "${RED}$val"
	if [[ "$DIFF" != "" ]]; then
		printf "%s\n" "${COLORBONITO}----- STDOUT -----$NC" >> diff.txt
		diff out1 out2 >> diff.txt
	fi
    fi

    if [[ $ERROR == 1 && "$ERRDIFF" == "" ]]
    then
	if [[ $TESTOK == 1 ]]; then
	    printf "${GREEN} [    ]$NC\n"
	else printf "${RED} [    ]$NC\n"
	fi
    elif [[ $ERROR == 1 && "$ERRDIFF" != "" ]]
    then
	if [[ $TESTOK == 1 ]]; then
	    printf "${GREEN} [${MARRONMIERDA}FAIL${GREEN}]$NC\n"
	else
	    printf "${RED} [${MARRONMIERDA}FAIL${RED}]$NC\n"
	fi
	printf "%s\n" "$COLORBONITO----- STDERR -----$NC" >> diff.txt
	diff err1 err2 >> diff.txt
    else
	printf "\n"
    fi

    if [[ "$DIFF" != "" || $RET1 != $RET2 || ($ERROR == 1 && $ERRDIFF != "") ]]
    then
	printf "\n\n" >> diff.txt
    fi

    TOTAL=$((TOTAL+1))
done

printf "\n\n\t${GREEN}$PASSED$NC tests ${GREEN}passed$NC from a total of $TOTAL tests"
printf "  ||  ${GREEN}$PASSED passed$NC - "
if [[ $((TOTAL - PASSED)) == 0 ]]; then
	printf "${GREEN}$((TOTAL - PASSED)) failed$NC"
else
	printf "${RED}$((TOTAL - PASSED)) failed$NC"
fi

printf "\n\n\t\t\'cat diff.txt | less\'  for detailed information\n\n"

rm -rf minishell out1 out2 err1 err2 a b c d pum lscp hpc hp testfile
rm -rf file log out output salut test 'test 1' test\\ ';' '000' 'chmod' 'd;' 'a;' echo
chmod +r dirwithoutpermissions
rm -rf ucantexecme.e dir dir/encoreuneautredir dirwithoutpermissions

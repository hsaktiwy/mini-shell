
########## STDOUT ##############
export T="|"
echo segfault $T grep segfault

export T='|'
echo segfault $T grep segfault

export T=">"
echo segfault $T grep segfault

export T='<'
echo segfault $T grep segfault

export T="<<"
echo segfault $T grep segfault

export T='<<'
echo segfault $T grep segfault

export T="|"
$T$T$T$T$T$T$T

export T="echo segfault | grep segfault"
$T

export T="<<"
$T.

########## STDERR ###############
exit 9223372036854775805

exit 123"123"

exit "+100"
exit -9223372036854775805
exit 0

exit 10

exit 42

exit 1





# cat << "$USER"
# why
# not
# $USER

# cat << "$US"E"R"
# because
# we
# love
# bash
# $USER

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la | cat << stop3
$USER
ad
as $HOME
stop
awd
wf$PWDdqwdwqd
stop1
das
das
stop2
dsq
wd
wf$PWDdqwdwqd
stop3

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > out | cat << 'stop3'
$USER
ad
stop
dsa
stop1
sad
stop2
as $HOME
stop3
/bin/rm -f out

ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
fe
wf
fwe
f
stop
dw
stop1
dwasd
stop2
cat Makefile | ls > out
cat out
/bin/rm -f out

ls | cat << stop | ls -la > out0| cat << stop1 | ls | cat << stop2 | ls -la >> out | cat << stop3
fe
wf
fwe
f
stop
dw
stop1
dw
stop2
e
wf
stop3
/bin/rm -f out
/bin/rm -f out0

ls | cat << stop | grep "asd"
is this good
stop

ls | cat << stop | ls -la | cat << stop1
12
32232
23
stop
awdaw
daswd
stop1


ls|cat Makefile|cat<<asd>out
$USER
asd
/bin/rm -f out

ls|cat Makefile|cat<<'asd'>out
$USER
asd
/bin/rm -f out

ls|cat Makefile|cat<<"asd">out
$USER
asd
/bin/rm -f out

############################################
### HERE_DOC ###
cat << lim
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

<<lim cat
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

cat << lim
test
lim

cat << EOF
"EOF"
!! HELLO
@42 !!
 EOF\t\b\n
testing your minishell :)
limm
EOF

cat << hello
$USER
$NOVAR
$HOME
hello

cat << 'lim'
$USER
$NOVAR
$HOME
lim

cat << lim''
$USER
$NOVAR
$HOME
lim

cat << "lim"
$USER
$NOVAR
$HOME
lim

cat << 'lim'
$USER
$NOVAR
$HOME
lim
##############################################
echo \$USER

echo \\$USER

echo \\\$USER

echo \\\\$USER

echo \\\\\$USER

echo \\\\\\\\\$USER

echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

##################################################
>echo>
/bin/rm -f echo

<echo<
/bin/rm -f echo

>>echo>>
/bin/rm -f echo
##################################################
echo "env | /usr/bin/wc -l" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "ls" | env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?
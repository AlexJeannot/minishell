#!/bin/bash

################ VARIABLES GLOBALES ################
test_number=1
display_error_msg=1
GREEN="\033[38;5;113m"
RED="\033[38;5;160m"
GREY="\033[38;5;109m"
ORANGE="\033[38;5;208m"
WHITE="\033[38;5;15m"
CYAN="\033[38;5;51m"
RESET="\033[0m"


################ FONCTIONS ################

add_newline()
{
    echo >> diff_minishell.txt
    echo >> diff_bash.txt
}

delete_file()
{
    for file in $@
    do
        if [ -f $file ]
        then
            rm $file
        fi
    done
}

run_shell()
{
    param_number=0

    echo $2 | $1 > buffer 2>&1
    for opt in "$@"
    do
        if [ $param_number \> 1 ]
        then
            cat < buffer | $opt > buffer2 2>&1
            cat < buffer2 > buffer
            rm buffer2
        fi
        let "param_number+=1"
    done
    if [ $display_error_msg == 0 ]
    then
        cat < buffer | grep -v Minishell: > buffer2
        cat < buffer2 > buffer
        cat < buffer | grep -v bash: > buffer2
        cat < buffer2 > buffer
    fi
    cat < buffer
}

run_return()
{
    echo $1 | ../minishell > /dev/random 2>&1 ; echo $? > diff_minishell.txt
    echo $1 | bash > /dev/random 2>&1 ; echo $? > diff_bash.txt
    diff --text diff_minishell.txt diff_bash.txt > /dev/random 2>&1
    result=$?
    if [ $result = 0 ]
    then
        echo -e "$GREEN TEST $test_number ✓$RESET"
    elif [ $result = 1 ]
    then
        echo -e "$RED\n======================== TEST $test_number ✗ ========================$RESET"
        echo -e "\033[38;5;90mCommand :$RESET" $1

        echo -e "$GREY\nMinishell output\n-------------------------------------------------------------$RESET"
        diff --text diff_minishell.txt diff_bash.txt | grep '<' | cut -c 2-
        echo -e "$GREY-------------------------------------------------------------$RESET"

        echo -e "$ORANGE\nBash output\n-------------------------------------------------------------$RESET"
        diff --text diff_minishell.txt diff_bash.txt | grep '>' | cut -c 2-
        echo -e "$ORANGE-------------------------------------------------------------\n$RESET"
    fi
    let "test_number+=1"
}

run_test()
{
    run_shell '../minishell' "$@" > diff_minishell.txt
    run_shell 'bash' "$@"  > diff_bash.txt
    diff --text diff_minishell.txt diff_bash.txt > /dev/random 2>&1
    result=$?
    if [ $result = 0 ]
    then
        echo -e "$GREEN TEST $test_number ✓$RESET"
    elif [ $result = 1 ]
    then
        echo -e "$RED\n======================== TEST $test_number ✗ ========================$RESET"
        echo -e "\033[38;5;90mCommand :$RESET" $1

        echo -e "$GREY\nMinishell output\n-------------------------------------------------------------$RESET"
        diff --text diff_minishell.txt diff_bash.txt | grep '<' | cut -c 2-
        echo -e "$GREY-------------------------------------------------------------$RESET"

        echo -e "$ORANGE\nBash output\n-------------------------------------------------------------$RESET"
        diff --text diff_minishell.txt diff_bash.txt | grep '>' | cut -c 2-
        echo -e "$ORANGE-------------------------------------------------------------\n$RESET"
    fi
    let "test_number+=1"
}


################ CLEAN SHELL ################

if [ "$1" = "clean" ]
then
    delete_file "diff_minishell.txt diff_bash.txt a b ../a ../b buffer buffer2 prog"
    exit
fi


################ SETUP SHELL ################
LC_ALL=C
gcc test.c -o prog
rm -rf diff_minishell.txt diff_bash.txt test_cd ~/test_cd test_files
delete_file "a b ../a ../b"
cd .. && make re && cd test

echo -e "$WHITE\n\nDisplay error messages ? [$GREEN Y$WHITE /$RED N $WHITE]$RESET"
echo -ne "$CYAN>> $RESET"
read user_input
if [ $user_input = 'N' ]
then
    display_error_msg=0
fi


################ SCRIPT ################

#ECHO
run_test 'echo test'
run_test 'echo echo'
run_test 'echo'
run_test 'echo -n -n lala'
add_newline
run_test 'echo \n'
run_test 'echo "test""test" "lala"'
run_test 'echo "test"test"" "lala"'
run_test 'echo "test"\""test" "lala"'
run_test 'echo "test"\"\""\"test" "lala"'
run_test "echo 'test''test''lala'"
run_test "echo 'test'\\'test'\''lala'"
run_test "echo 'test''test''lala'"
run_test 'echo -n oui'
add_newline
run_test 'echo $PWD'
run_test 'echo $OLDPWD'
run_test 'echo \$PWD'
run_test 'echo \\$PWD'
run_test 'echo $NOVAR'
run_test 'pwd ; echo $PWD ; echo OLDPWD ; unset PWD ; echo $PWD ; echo $OLDPWD ; cd .. ; echo $OLDPWD ; pwd ; echo $OLDPWD ; cd .. ; pwd ; echo $OLDPWD'


#ENV
run_test 'env' 'grep -v _=' 'sort'
export SHLVL=8 && run_test 'env' 'grep -a SHLVL'
export SHLVL=test && run_test 'env' 'grep -a SHLVL'
export SHLVL=0 && run_test 'env' 'grep -a SHLVL'
export SHLVL=+23 && run_test 'env' 'grep -a SHLVL'
export SHLVL=-10 && run_test 'env' 'grep -a SHLVL'
export SHLVL=8+8 && run_test 'env' 'grep -a SHLVL'
export SHLVL=++9 && run_test 'env' 'grep -a SHLVL'
export SHLVL=-8+8 && run_test 'env' 'grep -a SHLVL'
export SHLVL=9-8 && run_test 'env' 'grep -a SHLVL'
run_test 'export testvar ; env | grep -a testvar'
run_test 'export testvar= ; env | grep -a testvar'
run_test 'export testvar=0 ; env | grep -a testvar'
run_test 'export testvar=1234567 ; env | grep -a testvar'
run_test 'export testvar=lala ; env | grep -a testvar'
run_test 'export testvar=lala%lala ; env | grep -a testvar'
run_test 'export testvar=@lala ; env | grep -a testvar'
run_test 'export testvar10 ; env | grep -a testvar10'
run_test 'export testvar10= ; env | grep -a testvar10'
run_test 'export testvar10=10 ; env | grep -a testvar10'
run_test 'export _testvar ; env | grep -a _testvar'
run_test 'export _testvar= ; env | grep -a _testvar'
run_test 'export _testvar=10 ; env | grep -a _testvar'
run_test 'export _testvar=lala ; env | grep -a _testvar'
run_test 'export _testvar=lala10 ; env | grep -a _testvar'
run_test 'export _testvar10 ; env | grep -a _testvar10'
run_test 'export _testvar10= ; env | grep -a _testvar10'
run_test 'export _testvar10=lala ; env | grep -a _testvar10'
run_test 'export _testvar10=10; env | grep -a _testvar10'
run_test 'export _testvar10=lala10 ; env | grep -a _testvar10'


#EXPORT
run_test 'export' 'grep -v _=' 'sort'
export SHLVL=8 && run_test 'export' 'grep -a SHLVL'
export SHLVL=test && run_test 'export' 'grep -a SHLVL'
export SHLVL=0 && run_test 'export' 'grep -a SHLVL'
export SHLVL=+23 && run_test 'export' 'grep -a SHLVL'
export SHLVL=-10 && run_test 'export' 'grep -a SHLVL'
export SHLVL=8+8 && run_test 'export' 'grep -a SHLVL'
export SHLVL=++9 && run_test 'export' 'grep -a SHLVL'
export SHLVL=-8+8 && run_test 'export' 'grep -a SHLVL'
export SHLVL=9-8 && run_test 'export' 'grep -a SHLVL'
run_test 'export %' 
run_test 'export !' 
run_test 'export +' 
run_test 'export testvar ; export | grep -a testvar'
run_test 'export testvar= ; export | grep -a testvar'
run_test 'export testvar=0 ; export | grep -a testvar'
run_test 'export testvar=1234567 ; export | grep -a testvar'
run_test 'export testvar=lala ; export | grep -a testvar'
run_test 'export testvar=lala%lala ; export | grep -a testvar'
run_test 'export testvar=@lala ; export | grep -a testvar'
run_test 'export testvar10 ; export | grep -a testvar10'
run_test 'export testvar10= ; export | grep -a testvar10'
run_test 'export testvar10=10 ; export | grep -a testvar10'
run_test 'export _testvar ; export | grep -a _testvar'
run_test 'export _testvar= ; export | grep -a _testvar'
run_test 'export _testvar=10 ; export | grep -a _testvar'
run_test 'export _testvar=lala ; export | grep -a _testvar'
run_test 'export _testvar=lala10 ; export | grep -a _testvar'
run_test 'export _testvar10 ; export | grep -a _testvar10'
run_test 'export _testvar10= ; export | grep -a _testvar10'
run_test 'export _testvar10=lala ; export | grep -a _testvar10'
run_test 'export _testvar10=10; export | grep -a _testvar10'
run_test 'export _testvar10=lala10 ; export | grep -a _testvar10'


#UNSET
run_test 'unset'
run_test 'unset novar'
run_test 'unset %' 
run_test 'export a ; export ; unset a ; export' 'grep -v _='
run_test 'export a= ; export ; unset a ; export' 'grep -v _='
run_test 'export a=10 ; export ; unset a ; export' 'grep -v _='
run_test 'export a=lala ; export ; unset a ; export' 'grep -v _='
run_test 'export a=?lala%lala; export ; unset a ; export' 'grep -v _='
run_test 'export a=a10a10 ; export ; unset a ; export' 'grep -v _='
run_test 'export a10 ; export ; unset a10 ; export' 'grep -v _='
run_test 'export a10= ; export ; unset a10 ; export' 'grep -v _='
run_test 'export a10=10 ; export ; unset a10 ; export' 'grep -v _='
run_test 'export a10=lala ; export ; unset a10 ; export' 'grep -v _='
run_test 'export a10=?lala%lala; export ; unset a10 ; export' 'grep -v _='
run_test 'export a10=a10a10 ; export ; unset a10 ; export' 'grep -v _='
run_test 'export _a10 ; export ; unset _a10 ; export' 'grep -v _='
run_test 'export _a10= ; export ; unset _a10 ; export' 'grep -v _='
run_test 'export _a10=10 ; export ; unset _a10 ; export' 'grep -v _='
run_test 'export _a10=lala ; export ; unset _a10 ; export' 'grep -v _='
run_test 'export _a10=?lala%lala; export ; unset _a10 ; export' 'grep -v _='
run_test 'export _a10=a10a10 ; export ; unset _a10 ; export' 'grep -v _='


#PWD
run_test 'pwd'
run_test 'pwd test'
run_test 'pwd test lala'
run_test 'pwd "test"'


#CD
mkdir test_cd
mkdir ~/test_cd
run_test 'pwd ; cd ; pwd'
run_test 'pwd ; cd .. ; pwd'
export dir=${PWD%/*} && run_test 'pwd ; cd $dir ; pwd' && unset dir
run_test 'pwd ; cd test_cd ; pwd'
run_test 'pwd ; cd ~/ ; pwd'
run_test 'pwd ; cd ~/test_cd ; pwd'
run_test 'pwd ; cd .. ; pwd ; cd .. ; pwd ; cd ~/ ; pwd'
run_test 'pwd ; cd /'
run_test 'pwd ; cd error ; pwd'
run_test 'pwd ; cd error error ; pwd'
run_test 'pwd ; cd test_cd error ; pwd'
run_test 'pwd ; cd error test_cd error ; pwd'
run_test 'pwd ; cd ~/test_cd error ; pwd'
run_test 'pwd ; cd error ~/test_cd error ; pwd'
rm -rf test_cd
rm -rf ~/test_cd


#EXIT
run_test 'exit'
run_test 'exit | echo lala'
run_test 'exit ; echo lala'
run_test 'exit 0'
run_test 'exit 1'
run_test 'exit 255'
run_test 'exit 256'
run_test 'exit 1000'
run_test 'exit 9223372036854775807'
run_test 'exit +0'
run_test 'exit +1'
run_test 'exit +255'
run_test 'exit +256'
run_test 'exit +1000'
run_test 'exit +9223372036854775807'
run_test 'exit -0'
run_test 'exit -1'
run_test 'exit -255'
run_test 'exit -256'
run_test 'exit -1000'
run_test 'exit -9223372036854775808'
run_test 'exit --1'
run_test 'exit ++1'
run_test 'exit ++1'
run_test 'exit lala'
run_test 'exit ?'
run_test 'exit @@'
run_test 'exit 9223372036854775810'
run_test 'exit -9223372036854775810'

run_return 'exit'
run_return 'exit | echo lala'
run_return 'exit ; echo lala'
run_return 'exit 0'
run_return 'exit 1'
run_return 'exit 255'
run_return 'exit 256'
run_return 'exit 1000'
run_return 'exit 9223372036854775807'
run_return 'exit +0'
run_return 'exit +1'
run_return 'exit +255'
run_return 'exit +256'
run_return 'exit +1000'
run_return 'exit +9223372036854775807'
run_return 'exit -0'
run_return 'exit -1'
run_return 'exit -255'
run_return 'exit -256'
run_return 'exit -1000'
run_return 'exit -9223372036854775808'
run_return 'exit --1'
run_return 'exit ++1'
run_return 'exit ++1'
run_return 'exit lala'
run_return 'exit ?'
run_return 'exit @@'
run_return 'exit 9223372036854775810'
run_return 'exit -9223372036854775810'

#VARIABLES D'ENVIRONNEMENTS
run_test 'export test=lala ; echo $test ; export $test=10 ; echo $lala'
run_test 'export test=lala ; export $test=a10 ; export $lala=test ; unset $lala ; export' 'grep -v _='
run_test 'export a b c ; unset a c ; export' 'grep -v _='
run_test 'export test=echo val=lala ; $test $lala ; export' 'grep -v _='

#PIPE
run_test 'export a | echo lala ; export' 'grep -v _='
run_test 'export | echo lala'
run_test 'unset PWD | echo lala ; export' 'grep -v _='
run_test 'cd .. | echo lala ; export' 'grep -v _='
run_test 'echo test | echo lala'
run_test 'pwd | echo lala'
run_test 'env | echo lala'
run_test 'cat bible.txt | grep testifieth'
#run_test 'find / | grep cores'
run_test 'echo test | cat | cat | cat | cat | cat | grep test'

#PARSING
run_test 'echo \n\n'
run_test 'echo ""' 
run_test 'echo \|' 
run_test 'echo \"\"' 
run_test 'echo \\'
run_test 'echo \\\\' 
run_test 'echo \|\|' 
run_test 'echo \\\|\\\|' 
run_test 'echo \\"\\"' 
run_test 'echo \$ \"' 
run_test 'echo \[ \] \\ \`' 
run_test 'echo \: \@ \< \> \= \?' 
run_test 'echo \"a\"' 
run_test 'echo \\"a\\"' 
run_test 'echo "\\a\\"' 
run_test 'echo \\\"a\"\\' 
run_test 'echo a\\a' 
run_test 'echo a\"\a' 
run_test 'echo $' 
run_test 'echo \$' 
run_test 'echo \\$' 
run_test 'echo $USER' 
run_test 'echo \$USER' 
run_test 'echo \\$USER' 
run_test 'echo \\\$USER' 
run_test 'echo $war' 
run_test 'echo \$war' 
run_test 'echo \\$war' 
run_test 'echo \\\$war' 
run_test 'echo \|\\$USER' 
run_test 'echo \|\\\$USER' 
run_test 'echo \\\"$USER' 
run_test 'echo \|\\$USER' 
run_test 'echo \|\\\$USER' 
run_test 'echo \\\"$USER' 
run_test 'echo \$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|' 
run_test 'echo \$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|' 
run_test 'echo \"\$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|\"' 
run_test 'echo \$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|' 
run_test 'echo \$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|' 
run_test 'echo \\\$ \\\! \\\@ \\\# \\\% \\\^ \\\& \\\* \\\( \\\) \\\_ \\\+ \\\|' 
run_test 'echo \: \! \< \> \= \?' 
run_test 'echo "\: \! \< \> \= \?"' 
run_test 'echo \[ \] \\ \`' 

#REDIRECTIONS
mkdir test_files
run_test 'echo test > a ; cat < a'
run_test 'echo lala >a ; cat <a'
run_test 'echo test > test_files/a ; cat < test_files/a'
run_test 'echo lala >test_files/a ; cat <test_files/a'
run_test 'echo test > b ; echo test add >> b ; cat < b'
run_test 'echo test > b ; rm b ; echo test add >> b ; cat < b'
run_test 'echo test > a ; echo test2 > b ; <a >b ; cat a b'
run_test 'echo test > a ; echo test2 > b ; >a >b <error; cat a b'
run_test 'echo test > a ; echo test2 > b ; rm a ; rm b ; >a >b <error; cat a b'
run_test 'echo test > a ; echo test2 > b ; >a <error b; cat a b'
run_test 'echo test > a ; echo test2 > b ; rm a ; rm b ; >a <error >b ; cat a b'
run_test 'cat <error'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a >test_files/b <error; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; rm test_files/a ; rm test_files/b ; >test_files/a >test_files/b <error; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >test_files/b; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; rm test_files/a ; rm test_files/b ; >test_files/a <error >test_files/b ; cat test_files/a test_files/b'
run_test 'cat <test_files/error'
run_test 'echo test > ../a ; echo test2 > ../b ; >../a >../b <error ; cat ../a ../b'
run_test 'echo test > ../a ; echo test2 > ../b ; rm ../a ; rm ../b ; >../a >../b <error; cat ../a ../b'
run_test 'echo test > ../a ; echo test2 > ../b ; >../a <error >../b ; cat ../a ../b'
run_test 'echo test > ../a ; echo test2 > ../b ; rm ../a ; rm ../b ; >../a <error >../b ; cat ../a ../b'
run_test 'cat <../error'
run_test '<error'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a >>test_files/b <error; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >>test_files/a >test_files/b <error; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >>test_files/a >>test_files/b <error; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >>test_files/b ; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >>test_files/b ; cat test_files/a test_files/b'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; <error >>test_files/a >>test_files/b ; cat test_files/a test_files/b'
delete_file "test_files/a test_files/b"
run_test 'echo test > test_files/a ; echo lala > test_files/b ; >test_files/a >>test_files/b <error; cat test_files/a test_files/b'
delete_file "test_files/a test_files/b"
run_test 'echo test > test_files/a ; echo lala > test_files/b ; >>test_files/a >>test_files/b <error; cat test_files/a test_files/b'
delete_file "test_files/a test_files/b"
run_test '>test_files/a <error >>test_files/b ; cat test_files/a test_files/b'
delete_file "test_files/a test_files/b"
run_test '>test_files/a <error >>test_files/b ; cat test_files/a test_files/b'
delete_file "test_files/a test_files/b"
run_test '<error >>test_files/a >>test_files/b ; cat test_files/a test_files/b'
run_test 'echo lala > a >> a >> a ; echo test >> a ; cat < a'
run_test 'echo lala > a >> a >> a ; echo test >> a ; echo lala > a >> a >> a ; cat < a'
run_test 'echo lala >> a >> a > a ; echo test >> a ; cat < a'
run_test 'echo lala >> a >> a > a ; echo test >> a ; echo lala >> a >> a > a ; cat < a'
run_test 'echo test > a ; echo lala >> a >> a >> a ; echo test >> a ; cat < a'
run_test 'echo test > a ; echo lala >> a >> a >> a ; echo test >> a ; echo lala >> a >> a >> a ; cat < a'
run_test 'echo test > a ; echo lala > b ; rm b ; >>a >>b <error; cat a b'
run_test 'echo test > a ; echo lala > b ; rm b ; >>a <error >> b ; cat a b'
run_test 'echo test > a ; echo lala > b ; rm a ; rm b ; >>a >>b <error; cat a b'
run_test 'echo test > a ; echo lala > b ; rm a ; rm b ; >>a <error >> b ; cat a b'


#$?
run_test 'export a ; echo $?'
run_test 'export % ; echo $?' 
echo "test" > a && run_test 'cat a ; echo $?' && rm a
run_test 'cat a ; echo $?'
run_test 'pwd ; echo $?'
run_test 'export a | echo $?'
run_test 'export % | echo $?' 
run_test 'echo $? ; echo $? ; echo $?'
run_test 'echo $? | echo $? | echo $?'
run_test 'cd error ; echo $?'
run_test 'cd error error ; echo $?'
run_test './error ; echo $?'
run_test '<error ; echo $?'
run_test 'cat <error ; echo $?'
run_test 'cat < ; echo $?'
run_test 'echo test > ; echo $?'
run_test 'echo test >> ; echo $?'
run_return 'exit lala'

#PROGRAM
run_test './prog'
run_test './prog a'
run_test './prog a b'
run_test './prog a b c'
run_test '$PWD/prog'
run_test '$PWD/prog a'
run_test '$PWD/prog b'


#OTHERS
run_test 'touch test_file ; rm test_file'
run_test 'ls'
#run_test 'ls -la'


#EMPTY ENV
echo 'export' | env -i ../minishell | grep -v _= >> diff_minishell.txt
echo 'export' | env -i bash | grep -v _= >> diff_bash.txt

#echo "=================== TEST $test_number ===================" >> diff_minishell.txt
#echo 'export' | env -i ../minishell | grep -v _= >> diff_minishell.txt
#echo "=================== TEST $test_number ===================" >> diff_bash.txt
#echo 'export' | env -i bash | grep -v _= >> diff_bash.txt
#let "test_number+=1"

#echo "=================== TEST $test_number ===================" >> diff_minishell.txt
#echo 'env' | env -i ../minishell | grep -v _= | sort >> diff_minishell.txt
#echo "=================== TEST $test_number ===================" >> diff_bash.txt
#echo 'env' | env -i bash | grep -v _= | sort >> diff_bash.txt
#let "test_number+=1"


#RETURN VALUE FROM PROGRAM
#echo "=================== TEST $test_number ===================" >> diff_minishell.txt
#echo 'echo lala' | ../minishell >> diff_minishell.txt && echo $? >> diff_minishell.txt
#echo "=================== TEST $test_number ===================" >> diff_bash.txt
#echo 'echo lala' | bash >> diff_bash.txt && echo $? >> diff_bash.txt
#let "test_number+=1"

#echo "=================== TEST $test_number ===================" >> diff_minishell.txt
#echo 'export %' | ../minishell | grep -v valid >> diff_minishell.txt ; echo $? >> diff_minishell.txt
#echo "=================== TEST $test_number ===================" >> diff_bash.txt
#echo 'export %' | bash | grep -v valid >> diff_bash.txt ; echo $? >> diff_bash.txt
#let "test_number+=1"


#HUGE CAT
run_test 'cat bible.txt'

################ END SHELL ################
rm -rf test_cd ~/test_cd test_files
delete_file "a b ../a ../b buffer buffer2 prog diff_minishell.txt diff_bash.txt"


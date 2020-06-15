#!/bin/bash

################ VARIABLES GLOBALES ################
test_number=1

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
    cat < buffer
}

run_test()
{

    echo "=================== TEST $test_number ===================" >> diff_minishell.txt
    run_shell '../minishell' "$@" >> diff_minishell.txt

    echo "=================== TEST $test_number ===================" >> diff_bash.txt
    run_shell 'bash' "$@"  >> diff_bash.txt

    let "test_number+=1"
}

################ SETUP SHELL ################
LC_ALL=C
rm -rf diff_minishell.txt diff_bash.txt test_cd ~/test_cd test_files
delete_file "a b ../a ../b"

################ SCRIPT ################

if [ "$1" = "clean" ]
then
    delete_file "diff_minishell.txt diff_bash.txt a b ../a ../b buffer buffer2"
    exit
fi


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
run_test 'echo "test"\\|\\""test" "lala"'
run_test 'echo "test"\"\""\"test" "lala"'
run_test "echo 'test''test''lala'"
run_test "echo 'test'\\'test'\''lala'"
run_test "echo 'test'\\\''test''lala'"
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
run_test 'export %' 'grep -v valid'
run_test 'export !' 'grep -v valid'
run_test 'export +' 'grep -v valid'
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
run_test 'unset %' 'grep -v valid'
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
run_test 'pwd ; cd ; pwd'
run_test 'pwd ; cd .. ; pwd'
export dir=${PWD%/*} && run_test 'pwd ; cd $dir ; pwd' && unset dir
mkdir test_cd && run_test 'pwd ; cd test_cd ; pwd' && rm -rf test_cd
run_test 'pwd ; cd ~/ ; pwd'
mkdir ~/test_cd && run_test 'pwd ; cd ~/test_cd ; pwd' && rm -rf ~/test_cd
run_test 'pwd ; cd .. ; pwd ; cd .. ; pwd ; cd ~/ ; pwd'

#EXIT
run_test 'exit'
run_test 'exit | echo lala'
run_test 'exit ; echo lala'


#VARIABLES D'ENVIRONNEMENTS
run_test 'export test=lala ; echo $test ; export $test=10 ; echo $lala'
run_test 'export test=lala ; export $test=a10 ; export $lala=test ; unset $lala ; export' 'grep -v _='
run_test 'export a b c ; unset a c ; export' 'grep -v _='


#PIPE
run_test 'export a | echo lala ; export' 'grep -v _='
run_test 'export | echo lala'
run_test 'unset PWD | echo lala ; export' 'grep -v _='
run_test 'cd .. | echo lala ; export' 'grep -v _='
run_test 'echo test | echo lala'
run_test 'pwd | echo lala'
run_test 'env | echo lala'
run_test 'cat bible.txt | grep testifieth'
run_test 'find / | grep cores'
run_test 'echo test | cat | cat | cat | cat | cat | grep test'


#REDIRECTIONS
mkdir test_files
run_test 'echo test > a ; cat < a'
run_test 'echo lala >a ; cat <a'
run_test 'echo test > test_files/a ; cat < test_files/a'
run_test 'echo lala >test_files/a ; cat <test_files/a'
run_test 'echo test > a ; echo test2 > b ; <a >b ; cat a b' 'grep -v directory'
run_test 'echo test > a ; echo test2 > b ; >a >b <error; cat a b' 'grep -v directory'
run_test 'rm a ; rm b ; >a >b <error; cat a b' 'grep -v directory'
run_test 'echo test > a ; echo test2 > b ; >a <error b; cat a b' 'grep -v directory'
run_test 'rm a ; rm b ; >a <error >b ; cat a b' 'grep -v directory'
run_test 'cat <error' 'grep -v directory'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a >test_files/b <error; cat test_files/a test_files/b' 'grep -v directory'
run_test 'rm test_files/a ; rm test_files/b ; >test_files/a >test_files/b <error; cat test_files/a test_files/b' 'grep -v directory'
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >test_files/b; cat test_files/a test_files/b' 'grep -v directory'
run_test 'rm test_files/a ; rm test_files/b ; >test_files/a <error >test_files/b ; cat test_files/a test_files/b' 'grep -v directory'
run_test 'cat <test_files/error' 'grep -v directory'
run_test 'echo test > ../a ; echo test2 > ../b ; >../a >../b <error ; cat ../a ../b' 'grep -v directory'
run_test 'rm ../a ; rm ../b ; >../a >../b <error; cat ../a ../b' 'grep -v directory'
run_test 'echo test > ../a ; echo test2 > ../b ; >../a <error >../b ; cat ../a ../b' 'grep -v directory'
run_test 'rm ../a ; rm ../b ; >../a <error >../b ; cat ../a ../b' 'grep -v directory'
run_test 'cat <../error' 'grep -v directory'
#run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a >>test_files/b <error; cat test_files/a test_files/b'


#$?
run_test 'export a ; echo $?'
run_test 'export % ; echo $?' 'grep -v valid'
echo "test" > a && run_test 'cat a ; echo $?' && rm a
run_test 'cat a ; echo $?'
run_test 'pwd ; echo $?'
run_test 'export a | echo $?'
run_test 'export % | echo $?' 'grep -v valid'
run_test 'echo $? ; echo $? ; echo $?'
run_test 'echo $? | echo $? | echo $?'


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


#APPEND FILE
echo "=================== TEST $test_number ===================" >> diff_minishell.txt
echo "test" > b && echo 'echo "test add" >> b ; cat < b' | ../minishell >> diff_minishell.txt
echo "=================== TEST $test_number ===================" >> diff_bash.txt
echo "test" > b && echo 'echo "test add" >> b ; cat < b' | bash >> diff_bash.txt
let "test_number+=1"

echo "=================== TEST $test_number ===================" >> diff_minishell.txt
echo "test" > test_files/b && echo 'echo "test add" >> test_files/b ; cat < test_files/b' | ../minishell >> diff_minishell.txt
echo "=================== TEST $test_number ===================" >> diff_bash.txt
echo "test" > test_files/b && echo 'echo "test add" >> test_files/b ; cat < test_files/b' | bash >> diff_bash.txt
let "test_number+=1"


#EMPTY ENV
echo "=================== TEST $test_number ===================" >> diff_minishell.txt
echo 'export' | env -i ../minishell | grep -v _= >> diff_minishell.txt
echo "=================== TEST $test_number ===================" >> diff_bash.txt
echo 'export' | env -i bash | grep -v _= >> diff_bash.txt
let "test_number+=1"

echo "=================== TEST $test_number ===================" >> diff_minishell.txt
echo 'env' | env -i ../minishell | grep -v _= | sort >> diff_minishell.txt
echo "=================== TEST $test_number ===================" >> diff_bash.txt
echo 'env' | env -i bash | grep -v _= | sort >> diff_bash.txt
let "test_number+=1"


#RETURN VALUE FROM PROGRAM
echo "=================== TEST $test_number ===================" >> diff_minishell.txt
echo 'echo lala' | ../minishell >> diff_minishell.txt && echo $? >> diff_minishell.txt
echo "=================== TEST $test_number ===================" >> diff_bash.txt
echo 'echo lala' | bash >> diff_bash.txt && echo $? >> diff_bash.txt
let "test_number+=1"

echo "=================== TEST $test_number ===================" >> diff_minishell.txt
echo 'export %' | ../minishell | grep -v valid >> diff_minishell.txt ; echo $? >> diff_minishell.txt
echo "=================== TEST $test_number ===================" >> diff_bash.txt
echo 'export %' | bash | grep -v valid >> diff_bash.txt ; echo $? >> diff_bash.txt
let "test_number+=1"


#HUGE CAT
run_test 'cat bible.txt'

################ END SHELL ################
rm -rf test_cd ~/test_cd test_files
delete_file "a b ../a ../b buffer buffer2"

diff --text diff_minishell.txt diff_bash.txt 
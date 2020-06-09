echo "\033[38;5;45m=================== TEST 1 ===================\033[0m"
echo "echo hello" | ./minishell
echo "\033[38;5;45m=================== TEST 2 ===================\033[0m"
echo "env" | ./minishell | grep -av ^"_=" | LC_ALL=C sort
echo "\033[38;5;45m=================== TEST 3 ===================\033[0m"
echo "env" | env -i ./minishell | grep -av ^"_=" | LC_ALL=C sort
echo "\033[38;5;45m=================== TEST 4 ===================\033[0m"
echo "pwd" | ./minishell
echo "\033[38;5;45m=================== TEST 5 ===================\033[0m"
echo "export" | ./minishell | grep -av ^"declare -x _="
echo "\033[38;5;45m=================== TEST 6 ===================\033[0m"
echo "export" | env -i ./minishell | grep -av ^"declare -x _="
echo "\033[38;5;45m=================== TEST 7 ===================\033[0m"
export SHLVL=8 && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 8 ===================\033[0m"
export SHLVL=coucou && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 9 ===================\033[0m"
export SHLVL=0 && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 10 ===================\033[0m"
export SHLVL=12coucou && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 11 ===================\033[0m"
export SHLVL=-18 && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 12 ===================\033[0m"
export SHLVL=+28 && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 13 ===================\033[0m"
export SHLVL=++8 && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 14 ===================\033[0m"
export SHLVL=78+18 && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 15 ===================\033[0m"
export SHLVL= && echo "env" | ./minishell | grep -a SHLVL
echo "\033[38;5;45m=================== TEST 16 ===================\033[0m"
echo "echo \"coucou\"lala" | ./minishell
echo "\033[38;5;45m=================== TEST 17 ===================\033[0m"
echo "echo \"coucou\"\'lala\'" | ./minishell
echo "\033[38;5;45m=================== TEST 18 ===================\033[0m"
echo "echo $PWD" | ./minishell
echo "\033[38;5;45m=================== TEST 19 ===================\033[0m"
echo "echo $\"PWD\"" | ./minishell
echo "\033[38;5;45m=================== TEST 20 ===================\033[0m"
echo "echo $\'PWD\'" | ./minishell
echo "\033[38;5;45m=================== TEST 21 ===================\033[0m"
echo "export PWD=coucou; echo $PWD" | ./minishell
echo "\033[38;5;45m=================== TEST 22 ===================\033[0m"
echo "echo coucou; echo \$_" | ./minishell
echo "\033[38;5;45m=================== TEST 23 ===================\033[0m"
echo "export PWD=coucou; pwd" | ./minishell
echo "\033[38;5;45m=================== TEST 24 ===================\033[0m"
echo "unset PWD; pwd" | ./minishell
echo "\033[38;5;45m=================== TEST 25 ===================\033[0m"
echo "cd ..; echo $PWD; pwd" | ./minishell
echo "\033[38;5;45m=================== TEST 26 ===================\033[0m"
echo "cd ..; echo $OLDPWD" | ./minishell
echo "\033[38;5;45m=================== TEST 27 ===================\033[0m"
echo "unset PWD; echo $OLDPWD" | ./minishell
echo "\033[38;5;45m=================== TEST 28 ===================\033[0m"
echo "unset PWD; cd ..; echo $OLDPWD" | ./minishell
echo "\033[38;5;45m=================== TEST 29 ===================\033[0m"
echo "echo coucou; echo $?" | ./minishell
echo "\033[38;5;45m=================== TEST 30 ===================\033[0m"
echo "ls" | ./minishell
echo "\033[38;5;45m=================== TEST 31 ===================\033[0m"
echo "env | grep PWD" | ./minishell
echo "\033[38;5;45m=================== TEST 32 ===================\033[0m"
echo "cd $HOME; ls" | ./minishell
echo "\033[38;5;45m=================== TEST 33 ===================\033[0m"
echo "export COUCOU=lala LALA=coucou coucou=lulu le12la=truc _12=truc a_a=bada ____=lolo _1_1=ololo bada= relele ; echo $?; env" | ./minishell  | grep -av ^_= | LC_ALL=C sort
echo "\033[38;5;45m=================== TEST 34 ===================\033[0m"
echo "export COUCOU=lala LALA=coucou; unset COUCOU LALA truc; echo $?; env" | ./minishell  | grep -av ^_= | LC_ALL=C sort
echo "\033[38;5;45m=================== TEST 35 ===================\033[0m"
echo 'echo bonjour; echo -n je suis; echo gentil; echo $?' | ./minishell
echo "\033[38;5;45m=================== TEST 36 ===================\033[0m"
echo "echo -n -n One\"argument\"'lo'l; echo \"n\"''ee\"d\"more'?'''\"'\";" | ./minishell
echo "\033[38;5;45m=================== TEST 37 ===================\033[0m"
echo "unset PWD; cd ..; env | grep ^PWD=" | ./minishell
echo "\033[38;5;45m=================== TEST 37b ===================\033[0m"
echo "export %%" | ./minishell
echo "\033[38;5;45m=================== TEST 38 ===================\033[0m"
echo "export test=10" | ./minishell
echo "\033[38;5;45m=================== TEST 39 ===================\033[0m"
echo "export lala=lalalalalalalala test test2=234567" | ./minishell
echo "\033[38;5;45m=================== TEST 40 ===================\033[0m"
echo "export % ; echo $? ; echo test ; echo $?" | ./minishell
echo "\033[38;5;45m=================== TEST 41 ===================\033[0m"
echo "cd .. ; pwd ; cd ; pwd ; cd Desktop ; pwd ; cd /Users/macalex/Desktop/42/ ; pwd ; cd ~/Desktop ; pwd " | ./minishell
echo "\033[38;5;45m=================== TEST 42 ===================\033[0m"
echo "cat | cat | cat " | ./minishell
echo "\033[38;5;45m=================== TEST 43 ===================\033[0m"
echo 'cat tester/minishell_tests.sh | cat | cat | cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat' | ./minishell
echo "\033[38;5;45m=================== TEST 44 ===================\033[0m"
echo 'cat tester/minishell_tests.sh | grep echo | wc; exit | echo RECKT | cat; cat tester/minishell_tests.sh | sort' | ./minishell
echo "\033[38;5;45m=================== TEST 45 ===================\033[0m"
echo 'cat tester/minishell_tests.sh | grep echo; echo $?; cat tester/minishell_tests.sh | grep RECKT | wc; echo $?' | ./minishell
echo "\033[38;5;45m=================== TEST 46 ===================\033[0m"
echo "cat tester/bible.txt | grep testifieth" | ./minishell
echo "\033[38;5;45m=================== TEST 47 ===================\033[0m"
echo "find / | grep /cores" | ./minishell
#echo "\033[38;5;45m=================== TEST 48 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 49 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 50 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 51 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 52 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 53 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 54 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 55 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 56 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 57 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 58 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 59 ===================\033[0m"

#echo "\033[38;5;45m=================== TEST 60 ===================\033[0m"

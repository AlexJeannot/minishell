echo "echo hello" | ./minishell
#echo "echo hello > yours/tmp1.txt" | ./minishell && cat yours/tmp1.txt
#echo "echo bijour > yours/tmp1.txt" | ./minishell && cat yours/tmp1.txt
#echo "echo yo >> yours/tmp1.txt" | ./minishell && cat yours/tmp1.txt
#echo "echo coucou >> yours/tmp2.txt" | ./minishell && cat yours/tmp2.txt
#ls -la yours | grep tmp1.txt | cut -c-10
#ls -la yours | grep tmp2.txt | cut -c-10
echo "env" | ./minishell | grep -v ^_= | LC_ALL=C sort
echo "env" | env -i ./minishell | grep -v ^_= | LC_ALL=C sort
echo "pwd" | ./minishell
echo "export" | ./minishell | grep -v ^"declare -x _=" | LC_ALL=C sort
echo "export" | env -i ./minishell | grep -v ^"declare -x _=" | LC_ALL=C sort
export SHLVL=8 && echo "env" | ./minishell | grep SHLVL
export SHLVL=coucou && echo "env" | ./minishell | grep SHLVL
export SHLVL=0 && echo "env" | ./minishell | grep SHLVL
export SHLVL=12coucou && echo "env" | ./minishell | grep SHLVL
export SHLVL=-18 && echo "env" | ./minishell | grep SHLVL
export SHLVL=+28 && echo "env" | ./minishell | grep SHLVL
export SHLVL=++8 && echo "env" | ./minishell | grep SHLVL
export SHLVL=78+18 && echo "env" | ./minishell | grep SHLVL
export SHLVL= && echo "env" | ./minishell | grep SHLVL
#./minishell srcs/cmds.txt
#./minishell srcs/cmds.txt bada lala
#./minishell < srcs/cmds.txt
#cat srcs/cmds.txt | ./minishell
#echo "echo < srcs/cmds.txt" | ./minishell
#echo "./minishell < srcs/cmds.txt >> yours/tmp3.txt" | ./minishell && cat yours/tmp3.txt
#echo "./minishell srcs/cmds.txt >> yours/tmp3.txt" | ./minishell && cat yours/tmp3.txt
echo "echo \"coucou\"lala" | ./minishell
echo "echo \"coucou\"\'lala\'" | ./minishell
echo "echo $PWD" | ./minishell
echo "echo $\"PWD\"" | ./minishell
echo "echo $\'PWD\'" | ./minishell
echo "export PWD=coucou; echo $PWD" | ./minishell
echo "echo coucou; echo \$_" | ./minishell
echo "export PWD=coucou; pwd" | ./minishell
echo "unset PWD; pwd" | ./minishell
echo "cd ..; echo $PWD; pwd" | ./minishell
echo "cd ..; echo $OLDPWD" | ./minishell
echo "unset PWD; echo $OLDPWD" | ./minishell
echo "unset PWD; cd ..; echo $OLDPWD" | ./minishell
echo "echo coucou; echo $?" | ./minishell
echo "ls" | ./minishell
echo "env | grep PWD" | ./minishell
echo "cd $HOME; ls"
echo "export COUCOU=lala LALA=coucou coucou=lulu le12la=truc _12=truc a_a=bada ____=lolo _1_1=ololo bada= relele ; echo $?; env" | ./minishell  | grep -v ^_= | LC_ALL=C sort
echo "export COUCOU=lala LALA=coucou; unset COUCOU LALA truc; echo $?; env" | ./minishell  | grep -v ^_= | LC_ALL=C sort
echo 'echo bonjour; echo -n je suis; echo gentil; echo $?' | ./minishell
echo "echo -n -n One\"argument\"'lo'l; echo \"n\"''ee\"d\"more'?'''\"'\";" | ./minishell
#echo 'cat tester.sh | grep echo | wc; exit | echo RECKT | cat; cat tester.sh | sort' | ./minishell
#echo 'cat tester.sh | grep echo; echo $?; cat tester.sh | grep RECKT | wc; echo $?' | ./minishell
#echo 'cat tester.sh | cat | cat | cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat' | ./minishell
echo "unset PWD; cd ..; env | grep ^PWD=" | ./minishell
echo \"\" | ./minishell
echo "\\" | ./minishell
echo "\\\"" | ./minishell
echo "\"\"" | ./minishell
echo "" | ./minishell
echo "'" | ./minishell
echo \| | ./minishell
echo \" | ./minishell
echo "\'" | ./minishell
echo "\|"\""" | ./minishell
echo \|\"\\ | ./minishell
echo "\|" | ./minishell
echo "\"\""\" | ./minishell
echo "\"\"" | ./minishell
echo '\\' | ./minishell
echo \\\\ | ./minishell
echo \\ | ./minishell
echo $$ | ./minishell
echo $ | ./minishell
echo \$ | ./minishell
echo '\\\"$USER' | ./minishell
echo "$USER" | ./minishell
echo '$USER' | ./minishell
echo \$USER | ./minishell
echo "\$USER" | ./minishell
echo '\$USER' | ./minishell
echo "\"\|\\\$USER" | ./minishell
echo " \" \' " | ./minishell
echo ' \" \' | ./minishell
echo "\!" "\$" | ./minishell
echo "\$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|" | ./minishell
echo "\: \; \< \> \= \?" | ./minishell
echo "\[ \] \\ \`" | ./minishell
echo '\$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|' | ./minishell
echo '\: \; \< \> \= \?' | ./minishell
echo '\[ \] \\ \`' | ./minishell
echo \$ \! \@ \# \% \^ \& \* \( \) \_ \+ \| | ./minishell
echo \: \; \< \> \= \? | ./minishell
echo \[ \] \\ \` | ./minishell
echo "\$ \" \' " | ./minishell
echo '\$ \" \' | ./minishell
echo "\"" | ./minishell

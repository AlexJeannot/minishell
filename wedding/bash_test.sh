echo "echo hello" | bash
#echo "echo hello > yours/tmp1.txt" | bash && cat yours/tmp1.txt
#echo "echo bijour > yours/tmp1.txt" | bash && cat yours/tmp1.txt
#echo "echo yo >> yours/tmp1.txt" | bash && cat yours/tmp1.txt
#echo "echo coucou >> yours/tmp2.txt" | bash && cat yours/tmp2.txt
#ls -la yours | grep tmp1.txt | cut -c-10
#ls -la yours | grep tmp2.txt | cut -c-10
echo "env" | bash | grep -v ^_= | LC_ALL=C sort
echo "env" | env -i bash | grep -v ^_= | LC_ALL=C sort
echo "pwd" | bash
echo "export" | bash | grep -v ^"declare -x _=" | LC_ALL=C sort
echo "export" | env -i bash | grep -v ^"declare -x _=" | LC_ALL=C sort
export SHLVL=8 && echo "env" | bash | grep SHLVL
export SHLVL=coucou && echo "env" | bash | grep SHLVL
export SHLVL=0 && echo "env" | bash | grep SHLVL
export SHLVL=12coucou && echo "env" | bash | grep SHLVL
export SHLVL=-18 && echo "env" | bash | grep SHLVL
export SHLVL=+28 && echo "env" | bash | grep SHLVL
export SHLVL=++8 && echo "env" | bash | grep SHLVL
export SHLVL=78+18 && echo "env" | bash | grep SHLVL
#export SHLVL= && echo "env" | bash | grep SHLVL
#bash srcs/cmds.txt
#bash srcs/cmds.txt bada lala
#bash < srcs/cmds.txt
#cat srcs/cmds.txt | bash
#echo "echo < srcs/cmds.txt" | bash
#echo "bash < srcs/cmds.txt >> yours/tmp3.txt" | bash && cat yours/tmp3.txt
#echo "bash srcs/cmds.txt >> yours/tmp3.txt" | bash && cat yours/tmp3.txt
echo "echo \"coucou\"lala" | bash
echo "echo \"coucou\"\'lala\'" | bash
echo "echo $PWD" | bash
echo "echo $\"PWD\"" | bash
echo "echo $\'PWD\'" | bash
echo "export PWD=coucou; echo $PWD" | bash
echo "echo coucou; echo \$_" | bash
echo "export PWD=coucou; pwd" | bash
echo "unset PWD; pwd" | bash
echo "cd ..; echo $PWD; pwd" | bash
echo "cd ..; echo $OLDPWD" | bash
echo "unset PWD; echo $OLDPWD" | bash
echo "unset PWD; cd ..; echo $OLDPWD" | bash
echo "echo coucou; echo $?" | bash
echo "ls" | bash
echo "env | grep PWD" | bash
echo "cd $HOME; ls"
echo "export COUCOU=lala LALA=coucou coucou=lulu le12la=truc _12=truc a_a=bada ____=lolo _1_1=ololo bada= relele ; echo $?; env" | bash  | grep -v ^_= | LC_ALL=C sort
echo "export COUCOU=lala LALA=coucou; unset COUCOU LALA truc; echo $?; env" | bash  | grep -v ^_= | LC_ALL=C sort
echo 'echo bonjour; echo -n je suis; echo gentil; echo $?' | bash
echo "echo -n -n One\"argument\"'lo'l; echo \"n\"''ee\"d\"more'?'''\"'\";" | bash
#echo 'cat tester.sh | grep echo | wc; exit | echo RECKT | cat; cat tester.sh | sort' | bash
#echo 'cat tester.sh | grep echo; echo $?; cat tester.sh | grep RECKT | wc; echo $?' | bash
#echo 'cat tester.sh | cat | cat | cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat| cat' | bash
echo "unset PWD; cd ..; env | grep ^PWD=" | bash
echo \"\" | bash
echo "\\" | bash
echo "\\\"" | bash
echo "\"\"" | bash
echo "" | bash
echo "'" | bash
echo \| | bash
echo \" | bash
echo "\'" | bash
echo "\|"\""" | bash
echo \|\"\\ | bash
echo "\|" | bash
echo "\"\""\" | bash
echo "\"\"" | bash
echo '\\' | bash
echo \\\\ | bash
echo \\ | bash
echo $$ | bash
echo $ | bash
echo \$ | bash
echo '\\\"$USER' | bash
echo "$USER" | bash
echo '$USER' | bash
echo \$USER | bash
echo "\$USER" | bash
echo '\$USER' | bash
echo "\"\|\\\$USER" | bash
echo " \" \' " | bash
echo ' \" \' | bash
echo "\!" "\$" | bash
echo "\$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|" | bash
echo "\: \; \< \> \= \?" | bash
echo "\[ \] \\ \`" | bash
echo '\$ \! \@ \# \% \^ \& \* \( \) \_ \+ \|' | bash
echo '\: \; \< \> \= \?' | bash
echo '\[ \] \\ \`' | bash
echo \$ \! \@ \# \% \^ \& \* \( \) \_ \+ \| | bash
echo \: \; \< \> \= \? | bash
echo \[ \] \\ \` | bash
echo "\$ \" \' " | bash
echo '\$ \" \' | bash
echo "\"" | bash

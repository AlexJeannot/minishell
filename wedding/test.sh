sh tester/test_exec_minishell.sh > tester/diff_minishell.txt 2>&1
sh tester/test_exec_bash.sh > tester/diff_bash.txt 2>&1
diff --text tester/diff_minishell.txt tester/diff_bash.txt > tester/diff.txt
cat tester/diff.txt
rename files in batch
find execve_stuff.c run_command.c -exec sh -c 'f="{}"; mv -- "$f" "exc_${f%.c}.c"' \;

to list out files in src
ls . | tr '\n' ' ' | pbcopy

failures:
./minishell
echo > outfile
echo "hellow "world" | grep hello | wc -l

echo undefined $(something) will seg fault

cat < infile < infile < infile << heredoc > outfile

echo $(UNEXISTING STUFF) = memleak
cd with 1 space behind (No such file or directory pops up)

echo $ will expand exit status (should just print $)
unset HOME and cd ~ causes segfault

cd ~/(UNEXISTING STUFF) = memleak -- fixed
export !@ -> event not found (probably don't have to handle this)
export #(works) -> declaration somehow gets out


Need to refresh exit_status for builtins
-> If not when exit status -1, pwd or env will let it remained at 1

export --TEST does not show anything somehow
unset also has to show similar things like export

pressing enter will cause memleak

export @$@##@$#ASDASDASDaASDASDSA=SDADAS

export @@#@#!@#!@#!@#@#!@#@!#@#!@#!@#!@##!@!@#@#!@#@!#!@@!#adskjhasfkjsadhfkjsdhfsadfs=sadkfjhasfjhasdhfsahgfdsf
does not cause memleak

export @' exports -declare somehow


echo hi > output | grep hi | wc -l
Bad file descriptor

cat | cat | ls somehow abit different -> due to waitpid

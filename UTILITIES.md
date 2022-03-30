rename files in batch
find execve_stuff.c run_command.c -exec sh -c 'f="{}"; mv -- "$f" "exc_${f%.c}.c"' \;

to list out files in src
ls . | tr '\n' ' ' | pbcopy
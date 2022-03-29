find execve_stuff.c run_command.c -exec sh -c 'f="{}"; mv -- "$f" "exc_${f%.c}.c"' \;

ls . | tr '\n' ' ' | pbcopy
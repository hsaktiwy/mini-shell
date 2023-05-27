#!/bin/bash

read -p "Enter the command: " command

echo "Output from your minishell:"
output_minishell=$(./minishell "$command")
echo "$output_minishell"

echo "Output from Bash 3.2:"
output_bash=$(bash -c "$command")
echo "$output_bash"

if [[ "$output_minishell" == "$output_bash" ]]; then
    echo "Output matches!"
else
    echo "Output does not match."
fi

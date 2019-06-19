# tinysh
  •	User should be able to enter commands with parameters, but there is no limitation of characters to be entered. 
  •	tinysh executable in shell script which display tinysh > as  its prompt. This might require to override the existing shell prompt.
  •	tinysh is  prompt user with the following prompt when 
  •	tinysh is read the data entered from standard input and parse it.
  •	tinysh is check, detect the command and its arguments.
  •	tinysh is warn the user about erroneous entry detected (unknown commands, commands with wrong/unsupported arguments, or commands without any mandatory arguments). In case of any erroneous entry, tinysh is display the syntax for the given command, if the given command is supported one but with wrong arguments. In case of any unsupported command, tinysh should display unknown command <first_word_given_by_user_as_command> (e.g. abc -f -t, unknown command abc).
  •	tinysh is support the following commands:

  -	cd <path>: changes the directory to the given path. Checks whether if the given path exists or not. Displays warning if not exists.

  -	pwd: prints the current/working directory.

  -	ls -la: lists the files in the current directory. -l stands for list style, -a stands for all files including hidden files and directories.

  -	touch <file> : creates the given file in the current directory. Checks if the given file exists. If exists, overrides it.

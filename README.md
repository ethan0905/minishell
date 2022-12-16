# minishell [![esafar's 42 minishell Score](https://badge42.vercel.app/api/v2/cl6l739qg00490gialxmtgsrk/project/2490871)](https://github.com/JaeSeoKim/badge42)
  
> *The objective of this project is for you to **create a simple shell**. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.*
>
> With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.
  
## 📔 Summary

 - [❓ What to do ?](%EF%B8%8F-what-to-do-)
 - [🧱 Builtins](#-builtins)
 - [⚙️ How to run the project ?](#%EF%B8%8F-how-to-run-the-project-)
 - [📄 Documentation](#-documentation)
 
## ❓ What to do ?

  - commands parsing considering `'` and `"`  
  - commands and files forwarding (`<`, `>`, `>>`)
  - multipipe management (`|`) 
  - environment variables (`$` followed by characters)
  - return code `$?` 
  - signals such as `ctrl-C`, `ctrl-D`, `ctrl-\` 
 
## 🧱 Builtins

  - `echo` (with option `-n`)
  - `cd` (with only relative or absolute path)
  - `pwd`
  - `export`
  - `unset`
  - `env` (without any options and any arguments)
  - `exit`
 
## ⚙️ How to run the project ?

1. Clone the repository:  
`git clone https://github.com/ethan0905/minishell.git`  
2. Compile the project:  
`make -j`  
3. Run the program:  
`./minishell`  
4. Enjoy ;) 

## 📄 Documentation
  
Special thanks to vietdu91 aka emtran, for his on work on that 900 lines test spreadsheet! You can go [here](https://github.com/vietdu91/42_minishell) an leave a star for the work.  
https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit#gid=0  

### bash bible:
https://www.gnu.org/software/bash/manual/bash.html  

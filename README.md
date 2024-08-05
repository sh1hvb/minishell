This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.


## Table of Contents
- [Subject](#subject)
- [Description](#description)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [How to Play](#how-to-play)
## Subject :
<ol style="margin-left: 15px;">
  <li style="font-size: 20px; font-weight: 600; color: red;">
     <a href="https://cdn.intra.42.fr/pdf/pdf/65357/en.subject.pdf" target="_blank" style="color: red; font-size: 15.5px; font-weight: 300; margin-left: 10px;"> subject.pdf </a>
  </li>
</ol>

## Description :
- minishell: A simple Unix shell implementation.

This project is a minimalistic shell that mimics basic functionalities of Unix shells. It supports command execution, piping, redirection, and environment variable management. Designed to provide a hands-on understanding of shell internals and system programming.
  
## Getting Started
### Prerequisites
- To use this program, you need a C compiler (e.g., GCC) and the make utility installed on your system.

### Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/sh1hvb/minishell.git minishell
    cd minishell
    ```
2. Compile the program:
    ```bash
    make  # This will generate the minishell program.
    make clean      # This will remove object files.
    ```
3. Usage :
    <ul>
      <li>Execute in your bash terminal: <code>./minishell </code></li>
       <li>Then, try any command you want. Note that <code>||</code>, <code>&&</code>, and wildcard are not implemented.</li>
      <li>For example:<br>
      <code> cat "<Makefile" "<minishell.h" "|" "grep" ";" </code>
      </li>
    </ul>
    
   

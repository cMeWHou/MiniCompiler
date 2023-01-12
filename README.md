<h1>MiniCompiler</h1>
This project is a simple C-copy of a beautiful self-written compiler: 
<a href="https://gist.github.com/anonymous/1415759">click here.</a>
<br><br>
The list of all available symbols is in file 
<a href="https://github.com/cMeWHou/MiniCompiler/blob/master/include/Lexer/Lexeme.h">
    "Lexer\Lexeme.h".
</a>

<h3>v0.1</h3>
Currently, the compilation of assignment, addition and subtraction expressions is working.
<img src="https://github.com/cMeWHou/MiniCompiler/blob/master/interpreter_example.png?raw=true">

<h3>How to build</h3>
Prerequirements:
<ul>
    <li>GCC 12.2.0</li>
    <li>CMake 3</li>
</ul>

Build:
<ol>
    <li><code>git clone https://github.com/cMeWHou/MiniCompiler.git </code></li>
    <li><code>cd MiniCompiler </code></li>
    <li><code>cmake </code></li>
    <li><code>cd cmake-build-debug </code></li>
    <li><code>MiniCompiler.exe <i>source_file</i> </code></li>
</ol>

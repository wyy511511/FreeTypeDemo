使用提供的 Makefile 来编译程序，确保安装了所有依赖项。 MacOS可以通过brew install安装。

在项目根目录下，运行以下命令来编译程序：
make clean 
make run CHARS="字符1 字符2 字符3" SCALAR="值1 值2 值3 值4"
例如，要渲染字符 "马" 和 "云"，并设置 Scalar 值为黑色背景和完全不透明，可以运行：
make run CHARS="马 云" SCALAR="0 0 0 255"
make run CHARS="马 云" SCALAR="0 0 0 0"
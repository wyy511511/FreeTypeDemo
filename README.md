# 项目名称

该项目用于渲染给定字符序列并生成图像。

## 编译和运行

确保已安装以下依赖项：

- FreeType 库
- OpenCV 库

在 MacOS 上，你可以使用 `brew` 来安装这些依赖项：
'''
brew install freetype
brew install opencv
'''
然后，在项目根目录下，使用提供的 `Makefile` 来编译和运行程序：
'''
make clean
make run CHARS="字符1 字符2 字符3" SCALAR="值1 值2 值3 值4"
'''
例如，要渲染字符 "马" 和 "云"，并设置 Scalar 值为黑色背景和完全不透明，可以运行：

make run CHARS="马 云" SCALAR="0 0 0 255"

另一个例子：

make run CHARS="马 云" SCALAR="0 0 0 0"

## 生成句子



g++ -o sentence sentence.cpp -I/opt/homebrew/include/freetype2 -I/opt/homebrew/opt/opencv/include/opencv4 -L/opt/homebrew/lib -L/opt/homebrew/opt/opencv/lib -lfreetype -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -std=c++17

## 使用方法

确保程序编译成功后，你可以按照以下格式来运行程序：

./sentence "给定的句子" 值1 值2 值3 值4

./sentence "白日依山尽" 100 150 200 255


其中 "给定的句子" 是你想要渲染的字符序列，后面的四个值是 Scalar 类的参数，用于设置图像的颜色和透明度。

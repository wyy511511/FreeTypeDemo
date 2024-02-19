#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
// 初始化 FreeType 库
FT_Library library;
FT_Error error = FT_Init_FreeType(&library);
if (error) {
    std::cerr << "Error initializing FreeType library" << std::endl;
    return 1;
}

// 加载字体文件
FT_Face face;
error = FT_New_Face(library, "test.ttf", 0, &face);
if (error == FT_Err_Unknown_File_Format) {
    std::cerr << "Unsupported font format" << std::endl;
    return 1;
} else if (error) {
    std::cerr << "Error loading font" << std::endl;
    return 1;
}

// 设置字体大小
FT_Set_Pixel_Sizes(face, 0, 50);

// 设置输出图片大小
int image_width = 100;
int image_height = 100;

// 创建空白图片
// 白色字的图 RGB 
// Mat image(image_height, image_width, CV_8UC4, Scalar(255, 255, 255, 0));
Mat image(image_height, image_width, CV_8UC4, Scalar(0, 0, 0, 0));


// 设置绘制起点
int pen_x = 20;
int pen_y = 20;

// 设置要渲染的汉字
wchar_t c = L'你';

// 渲染汉字
error = FT_Load_Char(face, c, FT_LOAD_RENDER);
if (error) {
    std::cerr << "Error loading character" << std::endl;
    return 1;
}

FT_GlyphSlot slot = face->glyph;

// 将渲染的汉字写入图片
auto bitmap = &slot->bitmap;
int rows = bitmap->rows; // 字宽
int cols = bitmap->width; // 字高
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        int ty = pen_y + i;
        int tx = pen_x + j;
        if (ty >= image.rows || tx >= image.cols || ty < 0 || tx < 0)
            continue;
        image.at<Vec4b>(ty, tx)[3] = bitmap->buffer[i * cols + j];
    }
}

// 输出图片
imwrite("output.png", image);

// 释放资源
FT_Done_Face(face);
FT_Done_FreeType(library);

std::cout << "PNG file saved successfully" << std::endl;

return 0;
}
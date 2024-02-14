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
    FT_Set_Pixel_Sizes(face, 0, 16);

    // 设置要渲染的汉字
    wchar_t c = L'你';

    // 渲染汉字
    error = FT_Load_Char(face, c, FT_LOAD_RENDER);
    if (error) {
        std::cerr << "Error loading character" << std::endl;
        return 1;
    }

    FT_GlyphSlot slot = face->glyph;

    // 创建一个图像，用于渲染矢量图
    Mat vector_image(500, 500, CV_8UC4, Scalar(255, 255, 255, 0));

    // 设置绘制起点
    int pen_x = 20;
    int pen_y = 20;

    // 绘制字形
    auto outline = slot->outline;
    for (int i = 0; i < outline.n_contours; i++) {
        int contour_start = outline.contours[i];
        for (int j = contour_start; j < outline.contours[i + 1]; j++) {
            // 获取轮廓点
            FT_Vector point = outline.points[j];
            // 在 vector_image 上绘制轮廓点
            circle(vector_image, Point(pen_x + point.x, pen_y + point.y), 2, Scalar(0, 0, 0, 255), -1);
        }
    }

    // 输出矢量图像
    imwrite("vector_output.png", vector_image);

    // 释放资源
    FT_Done_Face(face);
    FT_Done_FreeType(library);

    std::cout << "Vector PNG file saved successfully" << std::endl;

    return 0;
}

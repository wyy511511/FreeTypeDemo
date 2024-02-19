#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <locale>
#include <codecvt>

using namespace cv;
namespace fs = std::filesystem;

int main() {
    // 初始化 FreeType 库
    FT_Library library;
    FT_Error error = FT_Init_FreeType(&library);
    if (error) {
        std::cerr << "Error initializing FreeType library" << std::endl;
        return 1;
    }

    // 设置字体大小
    int font_size = 50;

    // 输入的字
    std::wstring input_char = L"山";

    // 遍历Fonts马文件夹下的所有字体文件
    fs::path fonts_dir("./Fonts");
    for (const auto& entry : fs::directory_iterator(fonts_dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".ttf") {
            // 加载字体文件
            FT_Face face;
            error = FT_New_Face(library, entry.path().c_str(), 0, &face);
            if (error == FT_Err_Unknown_File_Format) {
                std::cerr << "Unsupported font format" << std::endl;
                continue;
            } else if (error) {
                std::cerr << "Error loading font" << std::endl;
                continue;
            }

            // 设置字体大小
            FT_Set_Pixel_Sizes(face, 0, font_size);

            // 创建空白图片
            Mat image(font_size, font_size, CV_8UC1, Scalar(0));

            // 渲染汉字
            error = FT_Load_Char(face, input_char[0], FT_LOAD_RENDER);
            if (error) {
                std::cerr << "Error loading character" << std::endl;
                continue;
            }

            FT_GlyphSlot slot = face->glyph;

            
            auto bitmap = &slot->bitmap;
            if (bitmap->rows == 0 || bitmap->width == 0) {
                std::cerr << "Empty glyph bitmap" << std::endl;
                FT_Done_Face(face);
                continue;
            }

            if (bitmap->rows < font_size / 2 && bitmap->width < font_size / 2 && slot->bitmap_top == font_size) {
                std::cerr << "Skipping placeholder glyph" << std::endl;
                FT_Done_Face(face);
                continue; 
            }



            // 在控制台上输出0和1的图
            std::cout << "Output for font: " << entry.path().stem().string() << std::endl;
            for (int i = 0; i < font_size; i++) {
                for (int j = 0; j < font_size; j++) {
                    if (i < bitmap->rows && j < bitmap->width) {
                        // 字形区域
                        int idx = i * bitmap->width + j;
                        std::cout << (bitmap->buffer[idx] ? '1' : '0');
                    } else {
                        // 字形外的区域
                        std::cout << '0';
                    }
                }
                std::cout << std::endl;
            }

            // 将渲染的汉字写入图片




            for (int i = 0; i < bitmap->rows; i++) {
                for (int j = 0; j < bitmap->width; j++) {
                    int ty = i;
                    int tx = j + (font_size - bitmap->width) / 2; // 水平居中
                    if (ty >= image.rows || tx >= image.cols || ty < 0 || tx < 0)
                        continue;
                    if (bitmap->buffer[i * bitmap->width + j] != 0)
                        image.at<uchar>(ty, tx) = 255; // 白色
                }
            }

            // 释放资源
            FT_Done_Face(face);

            // 保存图片
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::string output_file = "output_images/" + converter.to_bytes(input_char) + "_" + entry.path().stem().string() + ".png";
            imwrite(output_file, image);

            // 输出ttf文件名称
            std::cout << "TTf File Name: " << entry.path().stem().string() << std::endl;
        }
    }

    // 释放 FreeType 资源
    FT_Done_FreeType(library);

    std::cout << "Images generated successfully" << std::endl;

    return 0;
}

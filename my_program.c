    #include <stdio.h>
    #include <ft2build.h>
    #include FT_FREETYPE_H
     
    int main( int argc, char** argv )
    {
        FT_Library      library;
        FT_Face         face;
        FT_GlyphSlot    slot;
     
        char*  FontPath;
        FontPath = "test.ttf";
     
        FT_Init_FreeType( &library );               /* 定义一个FT库实例 */
     
        FT_New_Face( library, FontPath, 0, &face ); /* 从给定的路径加载字体文件并创建FT字形对象 */
     
        slot = face->glyph;                         /* 获取字形槽对象 */
       
        FT_Set_Pixel_Sizes( face, 50, 25 );         /* 像素宽度，高度 */
     
        FT_Load_Char( face, 'C', FT_LOAD_RENDER );  /* 装载字符 */
     
        printf("rows: %d, cols: %d\n", slot->bitmap.rows, slot->bitmap.width );
     
        for (int y=0; y < slot->bitmap.rows; y++)
        {
            for (int x=0; x < slot->bitmap.width; x++)
            {
                printf("%d", !!slot->bitmap.buffer[ y*slot->bitmap.width + x ] );  
            }
            printf("\n");
        }
     
        FT_Done_Face       ( face );
        FT_Done_FreeType( library );
     
        return 0;
    }
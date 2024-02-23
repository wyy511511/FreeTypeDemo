# 定义文件名列表

file_names = [
    "三.png", "二.png", "云.png", "川.png", "日.png", "林.png", "森.png", "水.png", "氵.png", "泪.png",
    "淋.png", "目.png", "羊.png", "耳.png", "马.png", "鸟.png",
    "三_1_甲骨文 _Oracle Bone Script.png", "二_1_甲骨文 _Oracle Bone Script.png",
    "云_1_甲骨文 _Oracle Bone Script.png", "川_1_甲骨文 _Oracle Bone Script.png",
    "日_1_甲骨文 _Oracle Bone Script.png", "林_1_甲骨文 _Oracle Bone Script.png",
    "森_1_甲骨文 _Oracle Bone Script.png", "水_1_甲骨文 _Oracle Bone Script.png",
    "氵_1_甲骨文 _Oracle Bone Script.png", "泪_1_甲骨文 _Oracle Bone Script.png",
    "淋_1_甲骨文 _Oracle Bone Script.png", "目_1_甲骨文 _Oracle Bone Script.png",
    "羊_1_甲骨文 _Oracle Bone Script.png", "耳_1_甲骨文 _Oracle Bone Script.png",
    "马_1_甲骨文 _Oracle Bone Script.png", "鸟_1_甲骨文 _Oracle Bone Script.png",
    "三_2_金文 - Bronze Inscription.png", "二_2_金文 - Bronze Inscription.png",

]

import os

def list_files(folder_path):
    file_list = []
    # 列出文件夹中的文件名
    files = os.listdir(folder_path)
    # 将文件名转换为字符串并添加到列表中
    for file_name in files:
        file_list.append(str(file_name))
    return file_list

# 指定文件夹路径
folder_path = './output_images'
# 调用函数列出文件并打印列表
file_names = list_files(folder_path)

# print(file_names)
# 初始化字典
sorted_list = sorted(file_names , key=len)
file_names  = sorted_list 
image_groups = {}

# 处理每个文件名
for file_name in file_names:
    # 去除文件扩展名
    name_without_extension = file_name.split('.')[0]
    # 分割文件名以获取关键部分
    parts = name_without_extension.split('_')
    
    if len(parts) == 1:  # 如果只有一个部分，表示是单个字符
        character = parts[0]
        # 将字符添加到字典中，如果不存在
        if character not in image_groups:
            image_groups[character] = []
    else:
        character, stage, description = parts[0], parts[1], '_'.join(parts[2:])
        # 将书写阶段和描述添加到相应字符的列表中
        image_groups[character].append(f"{character}_{stage}_{description}")

# 打印整理后的字典
for character, stages in image_groups.items():
    print(f'"{character}": {stages},')

for character, stages in image_groups.items():
    print(f'"{character}"')
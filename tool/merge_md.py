import os
import re

def merge_md_to_single_md(input_folder, output_md_path):
    # 获取绝对路径
    input_folder = os.path.abspath(input_folder)
    
    # 找到所有 .md 文件
    files = [f for f in os.listdir(input_folder) if f.endswith('.md')]

    if not files:
        print("⚠️ 在指定文件夹中没有找到任何 Markdown (.md) 文件！")
        return

    # ==========================================
    # 核心修改点：使用自然排序（智能识别文件名中的数字）
    # 这样可以确保 2.md 会排在 10.md 前面
    # ==========================================
    files.sort(key=lambda x: [int(c) if c.isdigit() else c for c in re.split(r'(\d+)', x)])
    
    # 💡 提示：如果使用上面这行代码后，你发现顺序依然是“从尾到头”的
    # 请把上面那行代码删掉或注释掉，换成下面这行纯粹的倒序排法：
    # files.sort(reverse=True)

    print(f"🔍 找到 {len(files)} 个 MD 文件，正在按正确顺序合并...")

    # 打开目标文件准备写入 (使用 utf-8 编码防止中文乱码)
    with open(output_md_path, 'w', encoding='utf-8') as outfile:
        for file_name in files:
            file_path = os.path.join(input_folder, file_name)
            
            try:
                # 读取每个小 MD 文件的内容
                with open(file_path, 'r', encoding='utf-8') as infile:
                    content = infile.read()
                    
                    # 写入文件名作为大标题
                    outfile.write(f"\n# {file_name}\n\n")
                    
                    # 写入正文内容
                    outfile.write(content)
                    
                    # 插入分页符
                    outfile.write("\n\n<div style=\"page-break-after: always;\"></div>\n\n")
                    
                print(f"✅ 已合并: {file_name}")
            except Exception as e:
                print(f"❌ 读取失败: {file_name}，错误: {e}")

    print(f"\n🎉 任务完成！合并后的大 MD 文件已保存在: \n{output_md_path}")

# ==========================================
# 在这里修改你的文件夹路径和输出文件名
# ==========================================
if __name__ == "__main__":
    # 存放 MD 文件的文件夹路径
    FOLDER_PATH = r"D:\document\HF-NNNU\code doucmunt\cpp NoteBook" 
    
    # 最终合并出来的 MD 文件保存路径
    OUTPUT_MD = r"D:\document\HF-NNNU\code doucmunt\cpp NoteBook\Print.md"
    
    merge_md_to_single_md(FOLDER_PATH, OUTPUT_MD)
import os
from pypdf import PdfReader, PdfWriter

def extract_pdf_pages(input_path, output_path, pages_to_extract):
    """
    从指定的 PDF 文件中提取特定页码并生成新的 PDF。

    :param input_path: 源 PDF 文件的路径
    :param output_path: 输出的新 PDF 文件的路径
    :param pages_to_extract: 需要提取的页码列表（基于 1 的自然页码，例如第一页就是 1）
    """
    # 检查输入文件是否存在
    if not os.path.exists(input_path):
        print(f"错误: 找不到文件 '{input_path}'")
        return

    reader = PdfReader(input_path)
    writer = PdfWriter()
    total_pages = len(reader.pages)

    print(f"源文件共有 {total_pages} 页。正在提取...")

    for page_num in pages_to_extract:
        # Python 索引从 0 开始，所以需要减 1
        index = page_num - 1 
        
        # 确保页码在合法范围内
        if 0 <= index < total_pages:
            writer.add_page(reader.pages[index])
        else:
            print(f"警告: 页码 {page_num} 超出范围 (1 - {total_pages})，已跳过。")

    # 将提取的页面写入新文件
    with open(output_path, "wb") as output_file:
        writer.write(output_file)
        
    print(f"提取完成！新文件已保存至: {output_path}")

# ================= 实际使用示例 =================
if __name__ == "__main__":
    # 1. 设置输入和输出文件路径
    source_pdf = r"C:\Users\HF\Desktop\左程云算法课_202605241150_34729.pdf"          # 替换为你的源文件路径
    target_pdf = r"C:\Users\HF\Desktop\1111.pdf" # 替换为你想要保存的新文件路径

    # 2. 设置你需要提取的页码（人类阅读习惯：第一页就是 1）
    
    # 示例 A：提取不连续的特定页码（例如提取第 1, 3, 5 页）
    target_pages = [6,7,8,9,13,14]
    target_pages+=list(range(23,39))    
    target_pages+=[44]
    target_pages+=list(range(49,55))
    target_pages+=list(range(56,62))
    
    # 执行提取
    extract_pdf_pages(source_pdf, target_pdf, target_pages)
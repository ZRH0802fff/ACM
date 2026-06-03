import os
import win32com.client
from pypdf import PdfWriter

def merge_ppts_to_pdf(input_folder, output_pdf_path):
    # 将相对路径转换为绝对路径，COM 接口必须使用绝对路径
    input_folder = os.path.abspath(input_folder)
    output_pdf_path = os.path.abspath(output_pdf_path)

    # 1. 启动 PowerPoint 应用程序
    try:
        powerpoint = win32com.client.Dispatch("PowerPoint.Application")
    except Exception as e:
        print("❌ 无法启动 PowerPoint，请确保你的电脑已安装 Microsoft PowerPoint。")
        return

    pdf_files = []
    
    # 获取所有 PPT/PPTX 文件并按名称排序
    # 忽略以 "~$" 开头的系统临时隐藏文件
    files = [f for f in os.listdir(input_folder) 
             if f.endswith(('.ppt', '.pptx')) and not f.startswith('~')]
    files.sort()

    if not files:
        print("⚠️ 在指定文件夹中没有找到任何 PPT 或 PPTX 文件！")
        powerpoint.Quit()
        return

    print(f"🔍 找到 {len(files)} 个幻灯片文件，正在转换为 PDF...")

    # 2. 逐个转换 PPT 为 PDF
    for file_name in files:
        ppt_path = os.path.join(input_folder, file_name)
        pdf_path = os.path.splitext(ppt_path)[0] + ".pdf"
        
        try:
            # 打开 PPT 文件 (WithWindow=False 表示后台打开)
            presentation = powerpoint.Presentations.Open(ppt_path, WithWindow=False)
            
            # 另存为 PDF (参数 32 代表 PDF 格式)
            presentation.SaveAs(pdf_path, 32)
            presentation.Close()
            
            pdf_files.append(pdf_path)
            print(f"✅ 已转换: {file_name}")
        except Exception as e:
            print(f"❌ 转换失败: {file_name}，错误: {e}")

    # 退出 PowerPoint 程序
    powerpoint.Quit()

    if not pdf_files:
        print("没有成功转换任何文件，合并终止。")
        return

    # 3. 合并所有的 PDF
    print("\n🔄 正在合并 PDF 文件...")
    merger = PdfWriter()
    
    for pdf_path in pdf_files:
        merger.append(pdf_path)
        
    with open(output_pdf_path, "wb") as output_file:
        merger.write(output_file)
        
    # 4. 清理转换过程中产生的临时单个 PDF 文件（可选）
    print("🧹 正在清理临时文件...")
    for pdf_path in pdf_files:
        try:
            os.remove(pdf_path)
        except Exception as e:
            print(f"⚠️ 无法删除临时文件: {pdf_path}, {e}")

    print(f"\n🎉 任务完成！最终合并的 PDF 文件已保存在: \n{output_pdf_path}")

# ==========================================
# 在这里修改你的文件夹路径和输出文件名
# ==========================================
if __name__ == "__main__":
    # 存放 PPT 的文件夹路径 (Windows 路径建议前面加 r，防止转义)
    FOLDER_PATH = r"D:\document\HF-NNNU\code doucmunt\zuo\ppt2" 
    
    # 最终合并出来的 PDF 文件保存路径
    OUTPUT_PDF = r"D:\document\HF-NNNU\code doucmunt\zuo\print.pdf"
    
    merge_ppts_to_pdf(FOLDER_PATH, OUTPUT_PDF)
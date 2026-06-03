import os
import shutil
from pathlib import Path

def clean_project(root_dir):
    root = Path(root_dir)
    deleted_files = 0
    deleted_dirs = 0

    # 你想干掉的文件后缀（Win的exe，Mac的out/o，Python的缓存，Java的class）
    target_extensions = {'.exe', '.out', '.o', '.pyc', '.pyo', '.class'}
    
    # 你想干掉的特定文件（比如 Mac 烦人的隐藏文件）
    target_specific_files = {'.DS_Store'}
    
    # 你想干掉的整个文件夹
    target_dirs = {'__pycache__'}

    print(f"🧹 开始扫描并清理目录: {root.resolve()} ...\n")

    # rglob('*') 会递归遍历当前文件夹及所有子文件夹
    for path in root.rglob('*'):
        try:
            # 1. 匹配并删除文件
            if path.is_file() and (path.suffix in target_extensions or path.name in target_specific_files):
                path.unlink()
                print(f"🗑️ 已删除文件: {path.name}")
                deleted_files += 1
                
            # 2. 匹配并删除文件夹
            elif path.is_dir() and path.name in target_dirs:
                shutil.rmtree(path)
                print(f"📂 已删除文件夹: {path.name}/")
                deleted_dirs += 1
                
        except Exception as e:
            # 防止因为权限问题报错卡死
            pass 

    print(f"\n✨ 清理完毕！共干掉了 {deleted_files} 个文件 和 {deleted_dirs} 个垃圾文件夹。")

if __name__ == "__main__":
    # '.' 代表清理当前 cleaner.py 所在的同级目录及其所有子目录
    clean_project('.')
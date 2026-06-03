import os
import shutil
from pathlib import Path

def clean_project(root_dir):
    root = Path(root_dir)
    deleted_files = 0
    deleted_dirs = 0

    target_extensions = {'.exe', '.out', '.o', '.pyc', '.pyo', '.class'}
    target_specific_files = {'.DS_Store'}
    target_dirs = {'__pycache__'}

    print(f"🧹 开始扫描并清理目录: {root.resolve()} ...\n")

    for path in root.rglob('*'):
        try:
            # 升级点：增加 path.name.startswith('._') 的判断
            if path.is_file() and (path.suffix in target_extensions or path.name in target_specific_files or path.name.startswith('._')):
                path.unlink()
                print(f"🗑️ 已删除 Mac 幽灵/缓存文件: {path.name}")
                deleted_files += 1
                
            elif path.is_dir() and path.name in target_dirs:
                shutil.rmtree(path)
                print(f"📂 已删除文件夹: {path.name}/")
                deleted_dirs += 1
                
        except Exception as e:
            pass 

    print(f"\n✨ 清理完毕！共干掉了 {deleted_files} 个文件 和 {deleted_dirs} 个垃圾文件夹。")

if __name__ == "__main__":
    clean_project('.')
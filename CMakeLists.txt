cmake_minimum_required(VERSION 3.20)
project(ACM)

set(CMAKE_CXX_STANDARD 17)

# 自动扫描所有 .cpp 文件
file(GLOB_RECURSE files "*.cpp")
foreach(file ${files})
    # 核心魔法升级：使用文件的绝对路径生成 MD5 哈希值，确保绝对不含中文
    string(MD5 hash_name ${file})
    # 截取前 8 位字符，防止内部名字太长
    string(SUBSTRING ${hash_name} 0 8 short_hash)

    # 用 run_ + 哈希码 作为安全的内部编译目标名
    add_executable(run_${short_hash} ${file})
endforeach()
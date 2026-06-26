class Book:
    def __init__(self,tt,at,pr):
        self.title=tt
        self.author=at
        self.price=pr
    def show_info(self):
        print(f"书名: {self.title}, 作者: {self.author}, 价格: {self.price}")

class EBook(Book):
    def download(self):
        print(f"正在下载电子书：{self.title}")

class PaperBook(Book):
    def borrow(self):
        print(f"正在借阅纸质书：{self.title}")


ebook = EBook("Python基础", "张三", 39.9)
paper = PaperBook("数据结构", "李四", 58.0)

ebook.show_info()
ebook.download()

paper.show_info()
paper.borrow()
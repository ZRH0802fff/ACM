class Student:
    def __init__(self,name,id,sc):
        self.name=name
        self.student_id=id
        self.score=sc
    def show_info(self):
        print(f"姓名: {self.name}, 学号: {self.student_id}, 成绩: {self.score}")
    def is_pass(self):
        if self.score>=60:
            return True
        else:
            return False

s = Student("Tom", "2024001", 85)
s.show_info()
print(s.is_pass())
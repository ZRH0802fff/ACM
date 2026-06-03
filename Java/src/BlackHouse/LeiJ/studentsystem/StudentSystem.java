package BlackHouse.LeiJ.studentsystem;

import java.util.ArrayList;
import java.util.Scanner;

public class StudentSystem {
    //main
    public static void main(String[] args) {
        ArrayList<Student> list = new ArrayList<>();
        Scanner sc = new Scanner(System.in);
        while (true) {
            System.out.println("-----------------欢迎来到学生管理系统-------------------");
            System.out.println("1:添加学生");
            System.out.println("2:删除学生");
            System.out.println("3:修改学生");
            System.out.println("4:查询学生");
            System.out.println("5:退出");
            System.out.println("请输入您的选择：");
            String choose = sc.next();
            switch (choose){
                case"1":
                    addStudent(list);
                    break;
                case"2":
                    deleteStudent(list);
                    break;
                case"3":
                    updateStudent(list);
                    break;
                case"4":
                    queryStudent(list);
                    break;
                case"5":
                    System.out.println("退出");
                    System.exit(0);
                default:
                    System.out.println("没有这个选项");
            }
        }
    }


    //添加学生
    public static void addStudent(ArrayList<Student>list){
        Scanner sc = new Scanner(System.in);
        Student stu=new Student();
        System.out.println("添加学生");
        String id=null;
        while (true) {
            System.out.println("请输入学生的id");
            id=sc.next();
            boolean flag=contains(list,id);
            if(flag)
                System.out.println("id已存在，请重新输入");

            else{
                stu.setId(id);
                break;
            }
        }
        System.out.println("请输入学生的姓名:");
        String name = sc.next();
        stu.setName(name);

        System.out.println("请输入学生的年龄:");
        int age = sc.nextInt();
        stu.setAge(age);

        System.out.println("请输入学生的住址:");
        String address = sc.next();
        stu.setAddress(address);

        list.add(stu);
        System.out.println("学生信息添加成功！");
    }


    //删除学生
    public static void deleteStudent(ArrayList<Student> list){
        System.out.println("删除学生");
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入要删除的学生id:");
        String id=sc.next();
        int  index =check(list,id);
        if(index!=-1){
            list.remove(index);
            System.out.println("学生信息删除成功！");
        }else{
            System.out.println("id不存在，删除失败");
        }
    }


    //修改学生
    public static void updateStudent(ArrayList<Student>list ){
        System.out.println("修改学生");
        Scanner sc=new Scanner(System.in);
        System.out.println("请输入要修改的学生id:");
        String id=null;
        while (true) {
            id=sc.next();
            boolean flag=contains(list,id);
            int index=check(list,id);
            if(flag){
                Student stu=list.get(index);
                System.out.println("请输入学生的姓名:");
                String name = sc.next();
                stu.setName(name);

                System.out.println("请输入学生的年龄:");
                int age = sc.nextInt();
                stu.setAge(age);

                System.out.println("请输入学生的住址:");
                String address = sc.next();
                stu.setAddress(address);

                System.out.println("学生信息修改成功！");
                break;
            }else{
                System.out.println("id不存在,请重新输入");
            }
        }
    }


    //查询学生
    public static void queryStudent(ArrayList<Student>list){
        System.out.println("查询学生");
        if(list.size()==0){
            System.out.println("当前无学生信息，请添加后查询");
            return ;
        }
        System.out.println("id\t\t姓名\t年龄\t家庭住址");
        for (int i = 0; i < list.size(); i++) {
            Student stu=list.get(i);
            System.out.println(stu.getId() + "\t" + stu.getName() + "\t" + stu.getAge() + "\t" + stu.getAddress());
        }
    }

    //查询是否存在
    public static boolean contains(ArrayList<Student>list ,String id){
        for (int i = 0; i < list.size(); i++) {
            if(id.equals(list.get(i).getId()))
                return true;
        }
        return false;
    }


    //查询学号并返回下标
    public static int check(ArrayList<Student>list,String id){
        for (int i = 0; i < list.size(); i++) {
            if(id.equals(list.get(i).getId()))
                return i;
        }
        return -1;
    }
}

package test;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class MyJFrame extends JFrame implements ActionListener {

    JButton jtb1 =new JButton("111");
    JButton jtb2 =new JButton("222");

    public MyJFrame(){
        //设置界面的宽高
        this.setSize(603, 680);
        //设置界面的标题
        this.setTitle("拼图单机版 v1.0");
        //设置界面置顶
        this.setAlwaysOnTop(true);
        //设置界面居中
        this.setLocationRelativeTo(null);
        //设置关闭模式
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        //取消默认的居中放置，只有取消了才会按照XY轴的形式添加组件
        this.setLayout(null);

        //设置按钮1
        jtb1.setBounds(0,0,100,50);
        jtb1.addActionListener(this);

        //设置按钮2
        jtb2.setBounds(100,0,100,50);
        jtb2.addActionListener(this);

        this.getContentPane().add(jtb1);
        this.getContentPane().add(jtb2);

        //让整个界面显示出来
        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object soure=e.getSource();
        if(soure==jtb1){
            jtb1.setSize(200,200);
        } else if (soure==jtb2) {
            Random r=new Random();
            jtb2.setLocation(r.nextInt(500),r.nextInt(500));
        }
    }
}







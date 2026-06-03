package ui;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Random;

public class GameJFrame extends JFrame implements KeyListener ,ActionListener{

    int[][] data = new int[4][4];

    //记录空白格子的坐标
    int x,y;

    //记录当前路径的图片
    String path="image/animal/animal3/";

    //统计步数
    int count=0;

    int[][] win = {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
            {13,14,15,0}
    };
    JMenuItem replayItem=new JMenuItem("重新游戏");
    JMenuItem reLoginItem=new JMenuItem("重新登录");
    JMenuItem closeItem=new JMenuItem("关闭游戏");

    JMenuItem accountItem=new JMenuItem("微信");

    JMenuItem vxItem=new JMenuItem("微信支付");
    JMenuItem zfbItem=new JMenuItem("支付宝支付");

    public GameJFrame(){
        //初始化界面
        initJFrame();

        //初始化菜单
        initJMenuBar();

        //初始化数据
        initData();

        //初始化图片
        initImage();

        //最后显示窗口
        this.setVisible(true);

    }

    //初始化数据
    private void initData() {
        int[] tempArr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        Random r =new Random();
        for (int i = 0; i < 16; i++) {
            int index=r.nextInt(16);
            int temp=tempArr[i];
            tempArr[i]=tempArr[index];
            tempArr[index]=temp;
        }
        for (int i = 0; i < tempArr.length; i++) {
            if(tempArr[i]==0){
                x=i/4;
                y=i%4;
            }
                data[i / 4][i % 4] = tempArr[i];

        }
    }

    //初始化图片
    private void initImage(){

        this.getContentPane().removeAll();

        //判断是否胜利
        if (victory()) {
            //显示胜利的图标
            JLabel winJLabel = new JLabel(new ImageIcon("image/win.png"));
            winJLabel.setBounds(203,283,197,73);
            this.getContentPane().add(winJLabel);
        }

        //添加步数统计界面
        JLabel stepCount=new JLabel("步数"+count);
        stepCount.setBounds(50,30,100,20);
        this.getContentPane().add(stepCount);

        //加载图片
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                int num=data[i][j];
                JLabel jLabel =new JLabel(new ImageIcon(path+num +".jpg"));
                jLabel.setBounds(j*105+83,i*105+134,105,105);
                //给图片添加边框
                jLabel.setBorder(new BevelBorder(1));
                this.getContentPane().add(jLabel);
            }
        }

        //添加背景图片
        JLabel background=new JLabel(new ImageIcon("image\\background.png"));
        background.setBounds(40,40,508,560);

        //把背景图片添加到界面中
        this.getContentPane().add(background);

        this.getContentPane().repaint();
    }

    //初始化菜单
    private void initJMenuBar() {
        JMenuBar jMenuBar=new JMenuBar();

        JMenu functionJMenu=new JMenu("功能");
        JMenu aboutJMenu=new JMenu("关于我们");
        JMenu valueJMenu=new JMenu("充值入口");

        functionJMenu.add(replayItem);
        functionJMenu.add(reLoginItem);
        functionJMenu.add(closeItem);

        aboutJMenu.add(accountItem);

        valueJMenu.add(vxItem);
        valueJMenu.add(zfbItem);

        //给条目绑定事件
        replayItem.addActionListener(this);
        reLoginItem.addActionListener(this);
        closeItem.addActionListener(this);
        accountItem.addActionListener(this);

        jMenuBar.add(functionJMenu);
        jMenuBar.add(aboutJMenu);
        jMenuBar.add(valueJMenu);

        this.setJMenuBar(jMenuBar);
    }

    private void initJFrame() {
        this.setSize(603,680);//界面大小
        this.setTitle("拼图 v1.0");//标题
        this.setAlwaysOnTop(true);//界面置顶
        this.setLocationRelativeTo(null);//界面居中
        this.setDefaultCloseOperation(3);//关闭方式
        this.setLayout(null);//取消默认的居中放置，只有取消了才会按照XY轴的形式添加组件
        this.addKeyListener(this);
    }

    //判断是否胜利
    public boolean victory(){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (data[i][j]!=win[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {
        int code=e.getKeyCode();
        if(code==65){
            this.getContentPane().removeAll();
            JLabel all=new JLabel(new ImageIcon(path +"all.jpg"));
            all.setBounds(83,134,420,420);
            this.getContentPane().add(all);
            JLabel background = new JLabel(new ImageIcon("image/background.png"));
            background.setBounds(40, 40, 508, 560);
            this.getContentPane().add(background);
            this.getContentPane().repaint();
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

        if(victory()){
            return ;
        }

        int code=e.getKeyCode();
        if(code==37){
            if(y==3) return ;
            System.out.println("向左移动");
            data[x][y]=data[x][y+1];
            data[x][y+1]=0;
            y++;
            initImage();
            count++;
        }else if (code == 38) {
            if(x==3) return;
            System.out.println("向上移动");
            //逻辑：
            //把空白方块下方的数字往上移动
            //x，y  表示空白方块
            //x + 1， y 表示空白方块下方的数字
            //把空白方块下方的数字赋值给空白方块
            data[x][y] = data[x + 1][y];
            data[x + 1][y] = 0;
            x++;
            //调用方法按照最新的数字加载图片
            initImage();
            count++;
        } else if (code == 39) {
            if(y==0) return;
            System.out.println("向右移动");
            //逻辑：
            //把空白方块左方的数字往右移动
            data[x][y] = data[x][y - 1];
            data[x][y - 1] = 0;
            y--;
            //每移动一次，计数器就自增一次。
            initImage();
            count++;
        } else if (code == 40) {
            if(x==0) return;
            System.out.println("向下移动");
            //逻辑：
            //把空白方块上方的数字往下移动
            data[x][y] = data[x - 1][y];
            data[x - 1][y] = 0;
            x--;
            //调用方法按照最新的数字加载图片
            initImage();
            count++;
        }else if(code==65){
            initImage();
        }else if(code==87){
            data = new int[][]{
                    {1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12},
                    {13,14,15,0}
            };
            initImage();
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object obj = e.getSource();
        //判断
        if(obj == replayItem){
            System.out.println("重新游戏");
            //计步器清零
            count = 0;
            //再次打乱二维数组中的数据
            initData();
            //重新加载图片
            initImage();
        }else if(obj == reLoginItem){
            System.out.println("重新登录");
            //关闭当前的游戏界面
            this.setVisible(false);
            //打开登录界面
            new LoginJFrame();
        }else if(obj == closeItem){
            System.out.println("关闭游戏");
            //直接关闭虚拟机即可
            System.exit(0);
        }else if(obj == accountItem){
            System.out.println("公众号");

            //创建一个弹框对象
            JDialog jDialog = new JDialog();
            //创建一个管理图片的容器对象JLabel
            JLabel jLabel = new JLabel(new ImageIcon("image/about.png"));
            //设置位置和宽高
            jLabel.setBounds(0,0,258,258);
            //把图片添加到弹框当中
            jDialog.getContentPane().add(jLabel);
            //给弹框设置大小
            jDialog.setSize(344,344);
            //让弹框置顶
            jDialog.setAlwaysOnTop(true);
            //让弹框居中
            jDialog.setLocationRelativeTo(null);
            //弹框不关闭则无法操作下面的界面
            jDialog.setModal(true);
            //让弹框显示出来
            jDialog.setVisible(true);
        }
    }
}

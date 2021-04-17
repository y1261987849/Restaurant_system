package com.source;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Vector;

public class Flight_JFrame extends JFrame implements ActionListener
{
    protected Flight_JPanel fli_panel;
    private DefaultTableModel tablemodel;
    public static JTable jtable;
    private JLabel Search_tip;
    protected JButton Add, Del, Search, Update, Exit;
    protected JComboBox<String> combox;
    private static Vector<String> storage;
    public int num; //文件
    public static int cnt; //表格中指向下一个

    public Flight_JFrame() throws Exception {
        super("航班信息管理");
        this.setSize(1350, 650);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        this.getContentPane().add(split);
        this.fli_panel = new Flight_JPanel();
        split.add(this.fli_panel);
        split.setDividerLocation(325);
        split.setOneTouchExpandable(false);

        JPanel rpanel = new JPanel(new BorderLayout());
        String[] titles = {"航班号", "起飞时间", "降落时间", "起飞城市", "降落城市", "航班票价", "票价折扣", "余票数量"};
        this.tablemodel = new DefaultTableModel(titles, 200)
        {
            public boolean isCellEditable(int row, int column)
            {
                return false;
            }
        };
        jtable = new JTable(this.tablemodel);
        rpanel.add(new JScrollPane(jtable));

        JPanel cmdpanel = new JPanel();
        rpanel.add(cmdpanel, "South");
        cmdpanel.add(Add = new JButton("添加"));
        cmdpanel.add(Del = new JButton("删除选中项"));
        cmdpanel.add(Update = new JButton("修改选中项"));
        cmdpanel.add(Search_tip = new JLabel("查找关键字"));
        String[] str = {"航班号", "起飞降落城市"};
        cmdpanel.add(this.combox = new JComboBox<String>(str));
        cmdpanel.add(Search = new JButton("查找"));
        cmdpanel.add(Exit = new JButton("返回"));
        split.add(rpanel);

        storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/fli_info.txt"));
        for (int i = 0; i < storage.size(); i++)
        {
            String[] s = storage.get(i).split("\\s+");
            tablemodel.setValueAt(s[0] , num, 0);
            tablemodel.setValueAt(s[1], num, 1);
            tablemodel.setValueAt(s[2], num, 2);
            tablemodel.setValueAt(s[3], num, 3);
            tablemodel.setValueAt(s[4], num, 4);
            tablemodel.setValueAt(Double.parseDouble(s[5]), num, 5);
            tablemodel.setValueAt(Double.parseDouble(s[6]), num, 6);
            tablemodel.setValueAt(Integer.parseInt(s[7]), num, 7);
            num++;
            cnt++;
        }

        Add.addActionListener(this);
        Del.addActionListener(this);
        Update.addActionListener(this);
        this.combox.addActionListener(this);
        Search.addActionListener(this);
        Exit.addActionListener(this);
        jtable.addMouseListener(new java.awt.event.MouseAdapter()
        {
            public void mouseClicked(MouseEvent e)
            {
                int n = jtable.getSelectedRow();
                if (n == -1 || n >= cnt)
                {
                    JOptionPane.showMessageDialog(null, "请选择正确的编辑对象!");
                }
                Flight_JPanel.id_text.setText(jtable.getValueAt(n, 0).toString());
                Flight_JPanel.takeofftime_text.setText(jtable.getValueAt(n, 1).toString());
                Flight_JPanel.arrivaltime_text.setText(jtable.getValueAt(n, 2).toString());
                Flight_JPanel.takeoffcity_text.setText(jtable.getValueAt(n, 3).toString());
                Flight_JPanel.arrivalcity_text.setText(jtable.getValueAt(n, 4).toString());
                Flight_JPanel.price_text.setText(jtable.getValueAt(n, 5).toString());
                Flight_JPanel.dis_text.setText(jtable.getValueAt(n, 6).toString());
                Flight_JPanel.tnum_text.setText(jtable.getValueAt(n, 7).toString());
            }
        });

        this.setVisible(true);
    }

    public void addToTable(Flight new_fli)
    {
        tablemodel.setValueAt(new_fli.fli_id, cnt, 0);
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd-HH:mm");
        tablemodel.setValueAt(dtf.format(new_fli.takeoff_time), cnt, 1);
        tablemodel.setValueAt(dtf.format(new_fli.arrival_time), cnt, 2);
        tablemodel.setValueAt(new_fli.takeoff_city, cnt, 3);
        tablemodel.setValueAt(new_fli.arrival_city, cnt, 4);
        tablemodel.setValueAt(String.valueOf(new_fli.price), cnt, 5);
        tablemodel.setValueAt(String.valueOf(new_fli.dis), cnt, 6);
        tablemodel.setValueAt(String.valueOf(new_fli.t_num), cnt, 7);
        cnt++;
    }

    public static void save()
    {
        try {
            FileIO.Write("/Users/yindongpeng/Java/src/com/source/fli_info.txt", storage);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    public void queryId(String str)
    {
        int c = 0;
        for (int i = 0; i < storage.size(); i++)
        {
            String[] t = storage.get(i).split("\\s+");
            if (str.equals(t[0]))
            {
                tablemodel.setValueAt(t[0], c, 0);
                tablemodel.setValueAt(t[1], c, 1);
                tablemodel.setValueAt(t[2], c, 2);
                tablemodel.setValueAt(t[3], c, 3);
                tablemodel.setValueAt(t[4], c, 4);
                tablemodel.setValueAt(t[5], c, 5);
                tablemodel.setValueAt(t[6], c, 6);
                tablemodel.setValueAt(t[7], c, 7);
                c++;
            }
        }
    }

    public void queryCity(String[] str)
    {
        int c = 0;
        for (int i = 0; i < storage.size(); i++)
        {
            String[] t = storage.get(i).split("\\s+");
            if (str[0].equals(t[3]) && str[1].equals(t[4]))
            {
                tablemodel.setValueAt(t[0], c, 0);
                tablemodel.setValueAt(t[1], c, 1);
                tablemodel.setValueAt(t[2], c, 2);
                tablemodel.setValueAt(t[3], c, 3);
                tablemodel.setValueAt(t[4], c, 4);
                tablemodel.setValueAt(t[5], c, 5);
                tablemodel.setValueAt(t[6], c, 6);
                tablemodel.setValueAt(t[7], c, 7);
                c++;
            }
        }
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object o = e.getSource();
        if (o == Add)
        {
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd-HH:mm");
            Flight new_fli = new Flight(Flight_JPanel.id_text.getText(), LocalDateTime.parse(Flight_JPanel.takeofftime_text.getText(), dtf), LocalDateTime.parse(Flight_JPanel.arrivaltime_text.getText(), dtf), Flight_JPanel.takeoffcity_text.getText(), Flight_JPanel.arrivalcity_text.getText(), Double.parseDouble(Flight_JPanel.price_text.getText()), Double.parseDouble(Flight_JPanel.dis_text.getText()), Integer.parseInt(Flight_JPanel.tnum_text.getText()));
            storage.add(num, new_fli.toString());
            num++;
            addToTable(new_fli);
            save();
            JOptionPane.showMessageDialog(null, "添加成功!");
        }
        else if (o == Del)
        {
            storage.removeElementAt(jtable.getSelectedRow());
            num--;
            tablemodel.removeRow(jtable.getSelectedRow());
            cnt--;
            save();
            JOptionPane.showMessageDialog(null, "删除成功!");

        }
        else if (o == Search)
        {
            int i = this.combox.getSelectedIndex();
            //查找到后，将表格中显示的所有信息先清除，再显示出符合查找关键字的信息
            tablemodel.setRowCount(0); //清除
            tablemodel.setRowCount(200); //重新扩展表格行

            if (i == 0)
            {
                String str = Flight_JPanel.id_text.getText();
                queryId(str);
            }
            else if (i == 1)
            {
                String[] str = new String[2];
                str[0] = Flight_JPanel.takeoffcity_text.getText();
                str[1] = Flight_JPanel.arrivalcity_text.getText();
                queryCity(str);
            }
        }
        else if (o == Update)
        {
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd-HH:mm");
            Flight new_fli = new Flight(Flight_JPanel.id_text.getText(), LocalDateTime.parse(Flight_JPanel.takeofftime_text.getText(), dtf), LocalDateTime.parse(Flight_JPanel.arrivaltime_text.getText(), dtf), Flight_JPanel.takeoffcity_text.getText(), Flight_JPanel.arrivalcity_text.getText(), Double.parseDouble(Flight_JPanel.price_text.getText()), Double.parseDouble(Flight_JPanel.dis_text.getText()), Integer.parseInt(Flight_JPanel.tnum_text.getText()));
            storage.removeElementAt(jtable.getSelectedRow());
            storage.add(new_fli.toString());
            tablemodel.removeRow(jtable.getSelectedRow());
            cnt--;
            addToTable(new_fli);
            save();

            JOptionPane.showMessageDialog(null, "更新信息成功!");
        }
        else if (o == Exit)
        {
            dispose();
        }
    }
}

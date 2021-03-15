package com.source;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Vector;

public class ManageJFrame extends JFrame implements ListSelectionListener, ActionListener
{
    private JMenuBar menubar = new JMenuBar();
    private JMenu filemenu = new JMenu("File");
    private JMenuItem save = new JMenuItem("Save");
    private JComboBox<String> combox; //查询标准组合框
    private JLabel tip; //请输入学生姓名的提示
    private JTextField name; //学生姓名文本框
    private JButton search;
    private JButton edit;
    private JButton add;
    private JButton delete;
    private DefaultTableModel tablemodel;
    private JTable table;
    private Vector<String> storage;

    int num = 0; //存储中的学生数量
    int count = 0; //表格显示的学生数量

    public ManageJFrame() throws Exception {
        super("考试报名管理系统");
        this.setBounds(300, 240, 800, 360);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        JSplitPane split = new JSplitPane(JSplitPane.VERTICAL_SPLIT); //垂直分割窗格
        this.getContentPane().add(split);
        split.setEnabled(false);
        split.setDividerLocation(40);
        split.setOneTouchExpandable(false);

        filemenu.add(save);
        menubar.add(filemenu);
        this.setJMenuBar(menubar);

        //上部命令行面板
        JPanel toppanel = new JPanel(new FlowLayout());
        split.add(toppanel);
        String[] str = {"精确查询", "模糊查询"};
        this.combox = new JComboBox<String>(str);
        toppanel.add(combox);
        toppanel.add(tip = new JLabel("请输入学生姓名"));
        toppanel.add(name = new JTextField(20));
        toppanel.add(search = new JButton("查询"));
        toppanel.add(edit = new JButton("编辑"));
        toppanel.add(add = new JButton("添加"));
        toppanel.add(delete = new JButton("删除"));


        //底部显示表格
        String[] titles = {"准考证号", "姓名", "性别", "年龄", "成绩"};
        this.tablemodel = new DefaultTableModel(titles, 2000);
        table = new JTable((this.tablemodel));
        split.add(new JScrollPane(table));

        search.addActionListener(this);
        edit.addActionListener(this);
        add.addActionListener(this);
        delete.addActionListener(this);
        save.addActionListener(this);

        this.setVisible(true);

        storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/info.txt"));

        for (int i = 0; i < storage.size(); i++)
        {
            String[] s = storage.get(i).split("\\s+");
            tablemodel.setValueAt(s[0] , num, 0);
            tablemodel.setValueAt(s[1], num, 1);
            tablemodel.setValueAt(s[2], num, 2);
            tablemodel.setValueAt(Integer.parseInt(s[3]), num, 3);
            tablemodel.setValueAt(Float.parseFloat(s[4]), num, 4);
            num++;
            count++;
        }
    }

    @Override
    public void valueChanged(ListSelectionEvent e)
    {

    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        switch (e.getActionCommand())
        {
            case "查询":
                int opt = this.combox.getSelectedIndex();
                if (opt == 0) //精确查询
                {
                    int j;
                    for (j = 0; j < storage.size(); j++)
                    {
                        String[] t = storage.get(j).split("\\s+");
                        if (name.getText().equals(t[1]))
                        {
                            table.setRowSelectionInterval(j, j);
                            break;
                        }
                    }

                    if (j == storage.size())
                    {
                        JOptionPane.showMessageDialog(null, "未查找到该同学!");
                    }
                }
                else if (opt == 1) //模糊查询
                {
                    int j;
                    for (j = 0; j < storage.size(); j++)
                    {
                        String[] t = storage.get(j).split("\\s+");
                        if (t[1].contains(name.getText()))
                        {
                            table.setRowSelectionInterval(j, j);
                            break;
                        }
                    }

                    if (j == storage.size())
                    {
                        JOptionPane.showMessageDialog(null, "未查找到相关同学!");
                    }
                }
                break;

            case "编辑":
                int n = table.getSelectedRow();
                if (n == -1 || n >= count)
                {
                    JOptionPane.showMessageDialog(null, "请选择正确的编辑对象!");
                    break;
                }
                EditDialog editDialog = new EditDialog();
                for (int j = 0; j < 5; j++)
                {
                    editDialog.texts[j].setText(table.getValueAt(n, j).toString());
                }
                editDialog.yes.addActionListener(this);
                break;

            case "添加":
                AddDialog addDialog = new AddDialog();
                addDialog.yes.addActionListener(this);
                break;

            case "删除":
                storage.removeElementAt(table.getSelectedRow());
                tablemodel.removeRow(table.getSelectedRow());
                break;
        }

        if (e.getSource() == AddDialog.yes)
        {
            String id = AddDialog.texts[0].getText();
            String name = AddDialog.texts[1].getText();
            String gender = AddDialog.texts[2].getText();
            int age = Integer.parseInt(AddDialog.texts[3].getText());
            float score = Float.parseFloat(AddDialog.texts[4].getText());
            Stu new_stu = new Stu(id, name, gender, score, age);

            storage.add(num, new_stu.toString());
            num++;

            addToTable(new_stu);

            JOptionPane.showMessageDialog(null, "添加成功!");
        }
        else if (e.getSource() == EditDialog.yes)
        {
            String id = EditDialog.texts[0].getText();
            String name = EditDialog.texts[1].getText();
            String gender = EditDialog.texts[2].getText();
            int age = Integer.parseInt(EditDialog.texts[3].getText());
            float score = Float.parseFloat(EditDialog.texts[4].getText());
            Stu new_stu = new Stu(id, name, gender, score, age);

            storage.removeElementAt(table.getSelectedRow());
            storage.add(new_stu.toString());

            addToTable(new_stu);
            tablemodel.removeRow(table.getSelectedRow());

            JOptionPane.showMessageDialog(null, "编辑成功!");
        }
        else if (e.getSource() == save)
        {
            try {
                FileIO.Write("/Users/yindongpeng/Java/src/com/source/info.txt", storage);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }finally
            {
                JOptionPane.showMessageDialog(null, "保存成功!");
            }
        }
    }

    public void addToTable(Stu new_stu)
    {
        tablemodel.setValueAt(new_stu.id, count, 0);
        tablemodel.setValueAt(new_stu.name, count, 1);
        tablemodel.setValueAt(new_stu.gender, count, 2);
        tablemodel.setValueAt(new_stu.age, count, 3);
        tablemodel.setValueAt(new_stu.score, count, 4);
        count++;
    }
}

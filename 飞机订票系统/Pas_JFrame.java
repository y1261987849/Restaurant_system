package com.source;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.Vector;

public class Pas_JFrame extends JFrame implements ActionListener
{
    protected Pas_JPanel pas_panel;
    private DefaultTableModel tablemodel;
    public static JTable jtable;
    protected JButton Add, Update, Exit;
    private static Vector<String> storage;
    public int num;
    public static int cnt;

    public Pas_JFrame() throws Exception
    {
        super("乘客信息管理");
        this.setSize(700, 200);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        this.getContentPane().add(split);
        this.pas_panel = new Pas_JPanel();
        split.add(this.pas_panel);
        split.setDividerLocation(250);
        split.setOneTouchExpandable(false);

        JPanel rpanel = new JPanel(new BorderLayout());
        String[] titles = {"乘客ID", "乘客姓名", "订票数量"};
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
        cmdpanel.add(Update = new JButton("修改选中项"));
        cmdpanel.add(Exit = new JButton("返回"));
        split.add(rpanel);

        storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/pas_info.txt"));
        for (int i = 0; i < storage.size(); i++)
        {
            String[] s = storage.get(i).split("\\s+");
            tablemodel.setValueAt(s[0] , num, 0);
            tablemodel.setValueAt(s[1], num, 1);
            tablemodel.setValueAt(s[s.length - 1], num, 2);
            num++;
            cnt++;
        }

        Add.addActionListener(this);
        Update.addActionListener(this);
        Exit.addActionListener(this);

        jtable.addMouseListener(new java.awt.event.MouseAdapter()
        {
            public void mouseClicked(MouseEvent e)
            {
                int n = jtable.getSelectedRow();
                if (n == -1 || n >= cnt)
                {
                    jtable.clearSelection();
                    JOptionPane.showMessageDialog(null, "请选择正确的编辑对象!");
                }
                Pas_JPanel.id_text.setText(jtable.getValueAt(n, 0).toString());
                Pas_JPanel.name_text.setText(jtable.getValueAt(n, 1).toString());
            }
        });

        this.setVisible(true);
    }

    public void addToTable(Passenger new_pas)
    {
        tablemodel.setValueAt(new_pas.pas_id, cnt, 0);
        tablemodel.setValueAt(new_pas.name, cnt, 1);
        tablemodel.setValueAt(new_pas.num, cnt, 2);
        cnt++;
    }

    public static void save()
    {
        try {
            FileIO.Write("/Users/yindongpeng/Java/src/com/source/pas_info.txt", storage);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        //在ord_storage中查找乘客id, 更新Passenger对象的订单编号信息
        Object o = e.getSource();
        if (o == Add)
        {
            String pas_id = Pas_JPanel.id_text.getText();
            Vector<String> ord_storage = null;
            try {
                ord_storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/ord_info.txt"));
            } catch (Exception exception) {
                exception.printStackTrace();
            };
            Passenger new_pas = new Passenger(pas_id, Pas_JPanel.name_text.getText());
            new_pas.ord_id = new String[20];
            new_pas.num = 0;
            for(int i = 0; i < ord_storage.size(); i++)
            {
                String[] t = ord_storage.get(i).split("\\s+");
                if (pas_id.equals(t[1]))
                {
                    new_pas.ord_id[new_pas.num] = t[0];
                    new_pas.num++;
                }
            }
            storage.add(num, new_pas.toString());
            num++;
            addToTable(new_pas);
            save();
            JOptionPane.showMessageDialog(null, "添加成功!");
        }
        else if (o == Update)
        {
            Vector<String> ord_storage = null;
            try {
                ord_storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/ord_info.txt"));
            } catch (Exception exception) {
                exception.printStackTrace();
            };
            Passenger new_pas = new Passenger(Pas_JPanel.id_text.getText(), Pas_JPanel.name_text.getText());
            new_pas.ord_id = new String[20];
            new_pas.num = 0;
            for(int i = 0; i < ord_storage.size(); i++)
            {
                String[] t = ord_storage.get(i).split("\\s+");
                if (new_pas.pas_id.equals(t[1]))
                {
                    new_pas.ord_id[new_pas.num] = t[0];
                    new_pas.num++;
                }
            }
            storage.removeElementAt(jtable.getSelectedRow());
            storage.add(new_pas.toString());
            tablemodel.removeRow(jtable.getSelectedRow());
            cnt--;
            addToTable(new_pas);
            save();
            JOptionPane.showMessageDialog(null, "更改信息成功!");
        }
        else if (o == Exit)
        {
            dispose();
        }
    }
}

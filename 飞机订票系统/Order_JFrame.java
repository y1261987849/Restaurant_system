package com.source;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.Vector;

public class Order_JFrame extends JFrame implements ActionListener
{
    protected Order_JPanel order_panel;
    private DefaultTableModel tablemodel;
    public static JTable jtable;
    protected JButton Add, Update, Exit;
    private Vector<String> storage;
    public int num;
    public static int cnt;

    public Order_JFrame() throws Exception {
        super("订单信息管理");
        this.setSize(800, 400);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        this.getContentPane().add(split);
        this.order_panel = new Order_JPanel();
        split.add(this.order_panel);
        split.setDividerLocation(250);
        split.setOneTouchExpandable(false);

        JPanel rpanel = new JPanel(new BorderLayout());
        String[] titles = {"订单号", "乘客ID", "乘客姓名", "航班号", "订单状态"};
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
        cmdpanel.add(Add = new JButton("订票"));
        cmdpanel.add(Update = new JButton("修改选中项"));
        cmdpanel.add(Exit = new JButton("返回"));
        split.add(rpanel);

        storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/ord_info.txt"));
        for (int i = 0; i < storage.size(); i++)
        {
            String[] s = storage.get(i).split("\\s+");
            tablemodel.setValueAt(s[0] , num, 0);
            tablemodel.setValueAt(s[1], num, 1);
            tablemodel.setValueAt(s[2], num, 2);
            tablemodel.setValueAt(s[3], num, 3);
            tablemodel.setValueAt(s[4], num, 4);
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
                Order_JPanel.id_text.setEditable(false);
                Order_JPanel.pasid_text.setEditable(false);
                Order_JPanel.name_text.setEditable(false);
                Order_JPanel.fliid_text.setEditable(false);
                int n = jtable.getSelectedRow();
                if (n == -1 || n >= cnt)
                {
                    jtable.clearSelection();
                    JOptionPane.showMessageDialog(null, "请选择正确的编辑对象!");
                    Order_JPanel.id_text.setEditable(true);
                    Order_JPanel.pasid_text.setEditable(true);
                    Order_JPanel.name_text.setEditable(true);
                    Order_JPanel.fliid_text.setEditable(true);
                }
                Order_JPanel.id_text.setText(jtable.getValueAt(n, 0).toString());
                Order_JPanel.pasid_text.setText(jtable.getValueAt(n, 1).toString());
                Order_JPanel.name_text.setText(jtable.getValueAt(n, 2).toString());
                Order_JPanel.fliid_text.setText(jtable.getValueAt(n, 3).toString());
                Order_JPanel.status_text.setText(jtable.getValueAt(n, 4).toString());
            }
        });

        this.setVisible(true);
    }

    public void addToTable(Order new_ord)
    {
        tablemodel.setValueAt(new_ord.ord_id, cnt, 0);
        tablemodel.setValueAt(new_ord.pas_id, cnt, 1);
        tablemodel.setValueAt(new_ord.name, cnt, 2);
        tablemodel.setValueAt(new_ord.fli_id, cnt, 3);
        tablemodel.setValueAt(new_ord.status, cnt, 4);
        cnt++;
    }

    private void save()
    {
        try {
            FileIO.Write("/Users/yindongpeng/Java/src/com/source/ord_info.txt", storage);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void save(String path, Vector<String> storage)
    {
        try {
            FileIO.Write("/Users/yindongpeng/Java/src/com/source/" + path, storage);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object o = e.getSource();
        if (o == Add)
        {
            //读取航班号，判断航班号当天有无余票，有 -> 添加；无 -> 搜索（根据起飞降落城市）并推荐其他航班号
            String fli_id = Order_JPanel.fliid_text.getText();
            Vector<String> fli_storage = null;
            try {
                fli_storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/fli_info.txt"));
            } catch (Exception exception) {
                exception.printStackTrace();
            }

            for (int i = 0; i < fli_storage.size(); i++)
            {
                String[] t = fli_storage.get(i).split("\\s+");
                if (fli_id.equals(t[0]))
                {
                    if (Integer.parseInt(t[7]) > 0)
                    {

                        Order new_ord = new Order(Order_JPanel.id_text.getText(), Order_JPanel.pasid_text.getText(), Order_JPanel.name_text.getText(), fli_id, Order_JPanel.status_text.getText());
                        storage.add(num, new_ord.toString());
                        num++;
                        addToTable(new_ord);
                        save();

                        /*
                        int t_num = Integer.parseInt(t[7]);
                        t_num--;
                        fli_storage.get(i).split("\\s+")[7] = String.valueOf(t_num);
                        save("fli_info.txt", fli_storage);

                        Vector<String> pas_storage = null;
                        try {
                            pas_storage = new Vector<String>(FileIO.Read("/Users/yindongpeng/Java/src/com/source/pas_info.txt"));
                        } catch (Exception exception) {
                            exception.printStackTrace();
                        }
                        for (int j = 0; j < pas_storage.size(); i++)
                        {
                            String[] temp = pas_storage.get(j).split("\\s+");
                            if (Order_JPanel.pasid_text.getText().equals(temp[0]))
                            {
                                int temp_num = Integer.parseInt(temp[2]);
                                temp_num++;
                                pas_storage.get(j).split("\\s+")[2] = String.valueOf(temp_num);
                            }
                        }
                        save("pas_info.txt", pas_storage);

                         */

                        JOptionPane.showMessageDialog(null, "下单成功!");
                    }
                    else
                    {
                        String rec = "";
                        for (int j = 0; j < fli_storage.size(); j++)
                        {
                            String[] tmp = fli_storage.get(j).split("\\s+");
                            if ((t[3].equals(tmp[3]) && t[4].equals(tmp[4]) && Integer.parseInt(tmp[7]) > 0))
                            {
                                rec = rec + tmp[0] + " ";
                            }
                        }
                        if (rec.length() != 0)
                            JOptionPane.showMessageDialog(null, "所选航班已无余票! 推荐选择以下航班:\n" + rec + ".");
                        else
                            JOptionPane.showMessageDialog(null, "所选航班已无余票且无合适的备选方案!");
                    }
                    break;
                }
            }
        }
        else if (o == Update)
        {
            Order new_ord = new Order(Order_JPanel.id_text.getText(), Order_JPanel.pasid_text.getText(), Order_JPanel.name_text.getText(), Order_JPanel.fliid_text.getText(), Order_JPanel.status_text.getText());
            storage.removeElementAt(jtable.getSelectedRow());
            storage.add(new_ord.toString());
            tablemodel.removeRow(jtable.getSelectedRow());
            cnt--;
            addToTable(new_ord);
            save();

            JOptionPane.showMessageDialog(null, "更新信息成功!");
        }
        else if (o == Exit)
        {
            dispose();
        }
    }
}

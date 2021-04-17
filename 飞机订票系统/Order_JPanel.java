package com.source;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class Order_JPanel extends JPanel
{
    private JLabel id_tip, pasid_tip, name_tip, fliid_tip, status_tip;
    public static JTextField id_text, pasid_text, name_text, fliid_text, status_text;

    public Order_JPanel()
    {
        this.setBorder(new TitledBorder("订单信息"));
        this.setLayout(new GridLayout(5, 2));

        this.add(id_tip = new JLabel("订单号", JLabel.CENTER));
        this.add(id_text = new JTextField("请输入订单号", 60));
        this.add(pasid_tip = new JLabel("乘客ID", JLabel.CENTER));
        this.add(pasid_text = new JTextField("请输入乘客ID", 60));
        this.add(name_tip = new JLabel("乘客姓名", JLabel.CENTER));
        this.add(name_text = new JTextField("请输入乘客姓名", 60));
        this.add(fliid_tip = new JLabel("航班号", JLabel.CENTER));
        this.add(fliid_text = new JTextField("请输入航班号", 60));
        this.add(status_tip = new JLabel("订单状态", JLabel.CENTER));
        this.add(status_text = new JTextField("请输入订单状态", 60));

        this.setVisible(true);
    }
}

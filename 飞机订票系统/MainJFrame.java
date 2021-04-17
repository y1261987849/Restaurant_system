package com.source;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class MainJFrame extends JFrame implements ActionListener {
    private JLabel Welcome;
    private JButton Flight_op, Order_op, Pas_op, Exit;

    public MainJFrame() {
        super("飞机订票系统");
        this.setLayout(new GridLayout(5, 1));
        this.setSize(300, 500);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        Welcome = new JLabel("欢迎使用飞机订票系统!", JLabel.CENTER);
        Welcome.setVerticalTextPosition(JLabel.TOP);
        this.add(Welcome);
        this.add(Flight_op = new JButton("航班情况管理"));
        this.add(Order_op = new JButton("订单情况管理"));
        this.add(Pas_op = new JButton("乘客信息管理"));
        this.add(Exit = new JButton("退出系统"));

        Flight_op.addActionListener(this);
        Order_op.addActionListener(this);
        Pas_op.addActionListener(this);
        Exit.addActionListener(this);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object o = e.getSource();
        if (o == this.Flight_op)
        {
            try {
                new Flight_JFrame();
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
        else if (o == this.Order_op)
        {
            try {
                new Order_JFrame();
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
        else if (o == this.Pas_op)
        {
            try {
                new Pas_JFrame();
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
        else if (o == Exit)
        {
            dispose();
        }
    }
}

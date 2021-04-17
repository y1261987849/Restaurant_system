package com.source;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class Pas_JPanel extends JPanel
{
    private JLabel id_tip, name_tip;
    public static JTextField id_text, name_text;

    public Pas_JPanel()
    {
        this.setBorder(new TitledBorder("乘客信息"));
        this.setLayout(new GridLayout(2, 2));

        this.add(id_tip = new JLabel("乘客ID", JLabel.CENTER));
        this.add(id_text = new JTextField("请输入乘客ID", 60));
        this.add(name_tip = new JLabel("乘客姓名", JLabel.CENTER));
        this.add(name_text = new JTextField("请输入乘客姓名", 60));

        this.setVisible(true);
    }
}

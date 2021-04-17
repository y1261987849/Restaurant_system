package com.source;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class Flight_JPanel extends JPanel
{
    private JLabel id_tip, takeofftime_tip, arrivaltime_tip, takeoffcity_tip, arrivalcity_tip, price_tip, dis_tip, tnum_tip;
    public static JTextField id_text, takeofftime_text, arrivaltime_text, takeoffcity_text, arrivalcity_text, price_text, dis_text, tnum_text;

    public Flight_JPanel()
    {
        this.setBorder(new TitledBorder("航班信息"));
        this.setLayout(new GridLayout(8, 2));

        this.add(id_tip = new JLabel("航班号", JLabel.CENTER));
        this.add(id_text = new JTextField("请输入航班号", 60));

        this.add(takeofftime_tip = new JLabel("起飞时间", JLabel.CENTER));
        this.add(takeofftime_text = new JTextField("yyyy/MM/dd-HH:mm", 60));
        this.add(arrivaltime_tip = new JLabel("降落时间", JLabel.CENTER));
        this.add(arrivaltime_text = new JTextField("yyyy/MM/dd-HH:mm", 60));

        this.add(takeoffcity_tip = new JLabel("起飞城市", JLabel.CENTER));
        this.add(takeoffcity_text = new JTextField("请输入起飞城市", 60));
        this.add(arrivalcity_tip = new JLabel("降落城市", JLabel.CENTER));
        this.add(arrivalcity_text = new JTextField("请输入降落城市", 60));

        this.add(price_tip = new JLabel("票价", JLabel.CENTER));
        this.add(price_text = new JTextField("请输入票价", 60));
        this.add(dis_tip = new JLabel("折扣", JLabel.CENTER));
        this.add(dis_text = new JTextField("请输入折扣", 60));
        this.add(tnum_tip = new JLabel("余票数量", JLabel.CENTER));
        this.add(tnum_text = new JTextField("请输入余票数量(单位: 张)", 60));

        this.setVisible(true);
    }
}

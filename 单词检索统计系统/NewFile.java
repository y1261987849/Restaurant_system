package com.source;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class NewFile extends JFrame implements ActionListener
{
    private JLabel tip;
    private JTextField fileName;
    private JTextArea fileContent;
    private JButton yes, exit;

    public NewFile()
    {
        super("建立文件");
        this.setSize(400, 450);
        this.setLocationRelativeTo(null);
        this.setLayout(new BorderLayout());
        this.setDefaultCloseOperation(HIDE_ON_CLOSE);

        JPanel top, mid, bot;
        top = new JPanel(new FlowLayout(FlowLayout.CENTER));
        top.add(tip = new JLabel("文件名: ", Label.RIGHT));
        top.add(fileName = new JTextField("请输入文件名", 15));
        mid = new JPanel(new FlowLayout(FlowLayout.CENTER));
        mid.add(fileContent = new JTextArea(20, 30));
        fileContent.setEditable(true);
        fileContent.setLineWrap(true);
        fileContent.setWrapStyleWord(true);
        bot = new JPanel(new FlowLayout(FlowLayout.CENTER));
        bot.add(yes = new JButton("确认"));
        bot.add(exit = new JButton("取消"));
        this.add(top, "North");
        this.add(mid, "Center");
        this.add(bot, "South");

        yes.addActionListener(this);
        exit.addActionListener(this);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        if (e.getSource() == yes)
        {
            String file = fileName.getText();
            String str = fileContent.getText();
            try {
                FileIO.Write("/Users/yindongpeng/Java/src/com/source/" + file, str);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
            JOptionPane.showMessageDialog(null, "创建文件成功!");
        }
        else if(e.getSource() == exit)
            dispose();
    }
}

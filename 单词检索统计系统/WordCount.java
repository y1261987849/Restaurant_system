package com.source;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

public class WordCount extends JFrame implements ActionListener
{
    private JLabel file_tip, word_tip;
    private JTextField fileName, pattern;
    private JTextArea output;
    private JButton yes, exit;
    public WordCount()
    {
        super("单词计数");
        this.setSize(700, 400);
        this.setLocationRelativeTo(null);
        this.setLayout(new BorderLayout());
        this.setDefaultCloseOperation(HIDE_ON_CLOSE);

        JPanel top, mid, bot;
        top = new JPanel(new FlowLayout(FlowLayout.CENTER));
        top.add(file_tip = new JLabel("文件名: ", Label.RIGHT));
        top.add(fileName = new JTextField("请输入要检索的文本文件名", 15));
        top.add(word_tip = new JLabel("单词: ", Label.RIGHT));
        top.add(pattern = new JTextField("请输入要检索统计的单词", 15));
        mid = new JPanel(new FlowLayout(FlowLayout.CENTER));
        mid.add(output = new JTextArea(20, 30));
        output.setEditable(false);
        output.setLineWrap(true);
        output.setWrapStyleWord(true);
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
            String str = pattern.getText();
            Vector<String> text = new Vector();
            try {
                text = FileIO.Read("/Users/yindongpeng/Java/src/com/source/" + file);
            } catch (Exception exception) {
                exception.printStackTrace();
            }

            output.removeAll();
            int cnt = 0;
            for (int i = 0; i < text.size(); i++)
            {
                cnt += Sunday_algorithm.count(text.get(i), str);
            }
            if (cnt != 0)
                output.setText("该单词在文本中出现了 " + cnt + " 次.");
            else
                JOptionPane.showMessageDialog(null, "该单词在此文本文件中不存在!\n");
        }
        else if(e.getSource() == exit)
            dispose();
    }
}

package com.source;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainJFrame extends JFrame implements ListSelectionListener, ActionListener
{

    private JButton newFile_button, wordCount_button, wordSearch_button, Exit_button;

    public MainJFrame()
    {
        super("单词检索统计");
        this.setSize(400, 500);
        this.setLocationRelativeTo(null);
        this.setLayout(new GridLayout(4, 1));
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        this.add(newFile_button = new JButton("建立文件"));
        this.add(wordCount_button = new JButton("单词计数"));
        this.add(wordSearch_button = new JButton("单词定位"));
        this.add(Exit_button = new JButton("退出程序"));

        newFile_button.addActionListener(this);
        wordCount_button.addActionListener(this);
        wordSearch_button.addActionListener(this);
        Exit_button.addActionListener(this);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object o = e.getSource();
        if (o == newFile_button)
        {
            new NewFile();
        }
        else if (o == wordCount_button)
        {
            new WordCount();
        }
        else if (o == wordSearch_button)
        {
            new WordSearch();
        }
        else if (o == Exit_button)
        {
            System.exit(0);
        }

    }

    @Override
    public void valueChanged(ListSelectionEvent e) {

    }
}
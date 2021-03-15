package com.source;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
public class EditDialog extends JDialog implements ActionListener
{
    private JPanel p;
    protected static JButton yes;
    protected static JButton no;
    protected static JTextField[] texts = new JTextField[5];
    public EditDialog()
    {
        setTitle("Edit Student");
        this.setSize(300, 300);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        p = new JPanel(new GridLayout(6, 2));
        String[] str = {"准考证号", "姓名", "性别", "年龄", "成绩"};
        for (int i = 0; i < 5; i++)
        {
            p.add(new JLabel(str[i], JLabel.CENTER));
            p.add(texts[i] = new JTextField());
        }
        p.add(yes = new JButton("确认"));
        p.add(no = new JButton("取消"));
        this.getContentPane().add(p);

        yes.addActionListener(this);
        no.addActionListener(this);
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        if(yes == e.getSource()) {
            dispose();
        }
        else if(no == e.getSource()) {
            dispose();
        }
    }
}

package com.qst.dms.ui;

import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import com.qst.dms.entity.User;
import com.qst.dms.service.UserService;

public class LoginFrame extends JFrame {

    private static final String SUCCESS_HINT = "成功提示";
    private static final String FAIL_HINT = "错误提示";

    private JPanel rootLayout;

    private JLabel userTextView,pwdTextView;
    private JTextField userEditText;
    private JPasswordField pwdEditText;
    private JButton loginButton,resetButton,registButton;

    private UserService userService;
    
    private LoginFrame loginFrame;

    public LoginFrame() {
        super("登录");

        userService = new UserService();

        rootLayout = new JPanel(new GridLayout(3,1));
        userTextView = new JLabel("用户名：");
        pwdTextView = new JLabel("密    码：");
        userEditText = new JTextField(16);
        pwdEditText = new JPasswordField(16);
        loginButton = new JButton("登录");
        loginButton.addActionListener(new LoginListener());
        resetButton = new JButton("重置");
        resetButton.addActionListener(new ResetListener());
        registButton = new JButton("注册");
        registButton.addActionListener(new RegistListener());

        JPanel Linear1 = new JPanel(new FlowLayout(FlowLayout.LEFT));
        Linear1.add(userTextView);
        Linear1.add(userEditText);
        JPanel Linear2 = new JPanel(new FlowLayout(FlowLayout.LEFT));
        Linear2.add(pwdTextView);
        Linear2.add(pwdEditText);
        JPanel Linear3 = new JPanel(new FlowLayout(FlowLayout.CENTER));
        Linear3.add(loginButton);
        Linear3.add(resetButton);
        Linear3.add(registButton);

        rootLayout.add(Linear1);
        rootLayout.add(Linear2);
        rootLayout.add(Linear3);

        this.add(rootLayout);
        this.setSize(300,200);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setVisible(true);

        loginFrame = this;
    }

    private class LoginListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String userName = userEditText.getText().trim();
            String pwd = new String(pwdEditText.getPassword());

            User user = userService.findUserByName(userName);

            if (user == null){
                JOptionPane.showMessageDialog(null, "用户不存在！", FAIL_HINT, JOptionPane.ERROR_MESSAGE);
            } else if(user.getPassword().equals(pwd)){
                new MainFrame_temp();
                loginFrame.dispose();
            } else {
                JOptionPane.showMessageDialog(null, "密码错误！", FAIL_HINT, JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private class ResetListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            userEditText.setText("");
            pwdEditText.setText("");
        }
    }

    private class RegistListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            new RegistFrame();
        }
    }

    public static void main(String[] args) {
        new LoginFrame();
    }
}

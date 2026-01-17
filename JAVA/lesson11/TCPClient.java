package lesson11;

import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class TCPClient {
    public static final String HOST = "localhost"; // 服务器地址
    public static final int PORT = 5000; // 服务器端口

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> createAndShowGui());
    }

    private static void createAndShowGui() {
        JFrame frame = new JFrame("TCP Client");
        JTextField input = new JTextField(30);
        JTextArea log = new JTextArea(10, 40);
        log.setEditable(false);
        JButton sendBtn = new JButton("发送");

        sendBtn.addActionListener(e -> {
            String text = input.getText();
            if (text == null || text.isEmpty()) return;
            try (Socket socket = new Socket(HOST, PORT);
                 BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(), "UTF-8"));
                 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream(), "UTF-8"))) {
                out.write(text);
                out.newLine();
                out.flush();
                String resp = in.readLine();
                log.append("Sent: " + text + "\n");
                log.append("Server: " + resp + "\n");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(frame, "通信错误: " + ex.getMessage());
            }
        });

        JPanel top = new JPanel();
        top.add(input);
        top.add(sendBtn);

        frame.getContentPane().add(top, BorderLayout.NORTH);
        frame.getContentPane().add(new JScrollPane(log), BorderLayout.CENTER);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}


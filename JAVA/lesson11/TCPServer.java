package lesson11;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**编写一个服务器和客户端程序。在他们之间实现TCP通信。
 * 程序启动后，客户端程序在窗口的文本框中输入内容。
 * 点击发送按钮时向服务器端发送文本框中的文本。服务器端收到信息后。反馈 ok。
 * 并在控制台窗口显示。 */
public class TCPServer {
    public static final int PORT = 5000; // 服务器监听端口 
    // 为什么是 5000： 因为 5000 以上的端口号通常不会被系统保留，可以自由使用。

    public static void main(String[] args) throws IOException {
        // 用 server socket 监听指定端口的连接请求 并创建socket连接
        try (ServerSocket server = new ServerSocket(PORT)) {  
            System.out.println("Server listening on port " + PORT);
            while (true) {
                Socket client = server.accept();
                new Thread(new Handler(client)).start();
            }
        }
    }

    /**
     * 处理客户端连接的处理器
     */
    static class Handler implements Runnable {
        private final Socket socket; // 与客户端通信的套接字

        Handler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() { // 处理客户端请求
            try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream(), "UTF-8"));
                 BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(), "UTF-8"))) {
                String line;
                while ((line = in.readLine()) != null) {
                    System.out.println("Received: " + line);

                    try { // 等待1秒再回复
                        Thread.sleep(1000); 
                    } catch (InterruptedException ie) {
                        Thread.currentThread().interrupt();
                    }

                    out.write("ok");
                    out.newLine();
                    out.flush();
                }
            } catch (IOException e) {
                System.err.println("Client handler error: " + e.getMessage());
            } finally {
                try {
                    socket.close();
                } catch (IOException ignored) {
                }
            }
        }
    }
}


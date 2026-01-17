package lesson11;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;


/**编写一个客户端和服务器端程序实现UDP通信。
 * 服务器端向特定客户地址每隔5秒发送一个数据包。
 * 单客户端启动后，能接收到服务器端发出的信息。
 * 并在控制台中显示。 */
public class UDPServer {
    private static final int SERVER_PORT = 9000;
    private DatagramSocket socket;
    private volatile InetAddress clientAddress = null;
    private volatile int clientPort = -1;
    private final ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();
    private ScheduledFuture<?> future;

    public void start() throws Exception {
        socket = new DatagramSocket(SERVER_PORT);
        System.out.println("Server started on port " + SERVER_PORT + ", waiting for client registration...");

        byte[] buf = new byte[1024];
        while (true) {
            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            socket.receive(packet);
            String msg = new String(packet.getData(), 0, packet.getLength(), "UTF-8").trim();
            System.out.println("Received from " + packet.getAddress() + ":" + packet.getPort() + " -> " + msg);

            if ("register".equalsIgnoreCase(msg)) {
                clientAddress = packet.getAddress();
                clientPort = packet.getPort();
                System.out.println("Registered client: " + clientAddress + ":" + clientPort);
                startSending();
            } else if ("unregister".equalsIgnoreCase(msg)) {
                System.out.println("Client unregistered.");
                stopSending();
            }
        }
    }

    private void startSending() {
        if (future != null && !future.isCancelled()) return;
        future = scheduler.scheduleAtFixedRate(() -> {
            try {
                if (clientAddress == null) return;
                String text = "服务器消息: " + System.currentTimeMillis();
                byte[] data = text.getBytes("UTF-8");
                DatagramPacket p = new DatagramPacket(data, data.length, clientAddress, clientPort);
                socket.send(p);
                System.out.println("Sent to " + clientAddress + ":" + clientPort + " -> " + text);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }, 0, 5, TimeUnit.SECONDS);
    }

    private void stopSending() {
        if (future != null) future.cancel(false);
        clientAddress = null;
        clientPort = -1;
    }

    public static void main(String[] args) throws Exception {
        new UDPServer().start();
    }
}

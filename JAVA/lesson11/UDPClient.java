package lesson11;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class UDPClient {
    private static final String SERVER_HOST = "localhost";
    private static final int SERVER_PORT = 9000;

    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket(); // use same socket for send+receive
        InetAddress serverAddr = InetAddress.getByName(SERVER_HOST);

        // send registration to server (server will use packet.getAddress()/getPort())
        byte[] reg = "register".getBytes("UTF-8");
        DatagramPacket regPkt = new DatagramPacket(reg, reg.length, serverAddr, SERVER_PORT);
        socket.send(regPkt);
        System.out.println("Sent registration to server " + SERVER_HOST + ":" + SERVER_PORT + " from local port " + socket.getLocalPort());

        byte[] buf = new byte[2048];
        DatagramPacket recv = new DatagramPacket(buf, buf.length);
        while (true) {
            try {
                socket.receive(recv);
                String msg = new String(recv.getData(), 0, recv.getLength(), "UTF-8");
                System.out.println("Received from server " + recv.getAddress() + ":" + recv.getPort() + " -> " + msg);
            } catch (Exception e) {
                e.printStackTrace();
                socket.close();
                break;
            }
        } 
    }
}

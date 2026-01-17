package lesson11;

import java.net.*;
//import java.io.*;

public class test {
    public static void main(String[] args) throws UnknownHostException {

        InetAddress address = InetAddress.getByName("www.gorecenter.com");
        System.out.println(address.getHostAddress());
        
        int a = 5, b = 5;
        if(a <= 5.0 && b >= 5.0) {
            System.out.println("Hello World");
        } else {
            System.out.println("WDNMD");
        }
    }
}

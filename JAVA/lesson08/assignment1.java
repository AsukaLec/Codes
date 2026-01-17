package lesson08;

import java.util.*;
import java.io.*;

/**
 * 1、关闭Microsoft VS Code，然后使用任意压缩软件，把Microsoft VS Code文件夹及文件夹下的所有压缩缩成一个Microsoft VS Code.zip 保存到D盘下面。
 * 分别使用 FileInputStream / FileOutputStream 及 BufferInputStream/BufferOutputStream 实现文件的复制。并输出两种方式复制文件的效率
 * 
 * 2、创建编写一个User类（id ，name，gender， toString（）），创建10User类的对象，
 * 然后通过输出流把对象写到盘 users.dat 文件中，
 * 然后在通过输入流把保存在users.dat文件中对象读取出来，并在控制台打印输出每个对象的信息。
 * 
 * 3、提高题：（选择完成）下载 作业文件.rar 解压后，打开 test05.java 和test06.java，根据里面的提示运用所学知识完成代码编写测试通过。
 */
public class assignment1 {
    public static void main(String[] args) {
        //task 1
        String sourcePath = "JAVA\\lesson08\\Microsoft VS Code.zip";
        String destPath1 = "JAVA\\lesson08\\Microsoft VS Code_copy1.zip";
        String destPath2 = "JAVA\\lesson08\\Microsoft VS Code_copy2.zip";

        // Using FileInputStream and FileOutputStream
        long startTime1 = System.currentTimeMillis();   
        try (FileInputStream fis = new FileInputStream(sourcePath);
            FileOutputStream fos = new FileOutputStream(destPath1)) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }    
        long endTime1 = System.currentTimeMillis();
        System.out.println("FileInputStream/FileOutputStream time: " + (endTime1 - startTime1) + " ms");

        // Using BufferedInputStream and BufferedOutputStream
        long startTime2 = System.currentTimeMillis();
        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(sourcePath));BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(destPath2))) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = bis.read(buffer)) != -1) {
                bos.write(buffer, 0, bytesRead);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        long endTime2 = System.currentTimeMillis();
        System.out.println("BufferedInputStream/BufferedOutputStream time: " + (endTime2 - startTime2) + " ms");
        System.out.println();

        //task 2
        //using Random to create 10 User objects
        List<User> users = new ArrayList<>();
        Random rand = new Random();
        String[] names = {"Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Hannah", "Ian", "Jane"};
        String[] genders = {"Male", "Female"};
        for (int i = 0; i < 10; i++) {
            int id = i + 1;
            String name = names[rand.nextInt(names.length)];
            String gender = genders[rand.nextInt(genders.length)];
            users.add(new User(id, name, gender));
        }
        // Write User objects to users.dat
        String userFilePath = "JAVA\\lesson08\\users.dat";  
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(userFilePath))) {
            for (User user : users) {
                oos.writeObject(user);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        // Read User objects from users.dat and print to console
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(userFilePath))) {
            for (int i = 0; i < 10; i++) {
                User user = (User) ois.readObject();
                System.out.println(user);
            }
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }

    }
}

class User implements Serializable {
    private int id;
    private String name;
    private String gender;
    public User(int id, String name, String gender) {
        this.id = id;
        this.name = name;
        this.gender = gender;
    }
    @Override
    public String toString() {
        return "User [id=" + id + ", name=" + name + ", gender=" + gender + "]";
    }   
}

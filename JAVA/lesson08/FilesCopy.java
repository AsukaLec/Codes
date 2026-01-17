package lesson08;

import java.io.*;

/**
 * 使用Path和Files工具类编写一个FilesCopy类，
 * 该类包含一个静态方法filesCopy（Path from，Path to），
 * 实现把from目录中的文件（文件包括：文件、子文件夹及子文件夹中的文件）复制到to目录中
 */
public final class FilesCopy {

    private static final int BUF = 8192;   

    /**检查当前路径指向的是文件夹还是文件
     * 若是文件夹 则继续递归
     * 若是文件 则执行复制操作
    */
    public static void Copy(File src, File dest) throws IOException {
        // 检查源文件/目录是否存在
        if (!src.exists()) throw new FileNotFoundException(src.getAbsolutePath());
        // 当个文件直接复制
        if (src.isFile()) {  
            copySingleFile(src, dest);
            return;
        }

        // 遍历子文件和子目录
        File[] children = src.listFiles();
        // for(File file : children){
        //     System.out.println("正在复制: " + file.getAbsolutePath());
        // }

        if (children == null) return;

        // 递归复制子文件和子目录
        for (File child : children) {
            File newDest = new File(dest, child.getName()); //新建目标文件或目录
            if (child.isDirectory()) {
                Copy(child, newDest);         // 递归
            } else {
                copySingleFile(child, newDest);   // 复制文件
            }
        }
    }

    /*复制单个文件*/
    private static void copySingleFile(File srcFile, File destFile) throws IOException {
        //防止同名文件覆盖
        if (destFile.exists() && destFile.isDirectory()) {
            destFile = new File(destFile, srcFile.getName());
        }

        // 保证父目录存在
        File parent = destFile.getParentFile();
        if (parent != null && !parent.exists() && !parent.mkdirs()) {
            throw new IOException("无法创建目录 " + parent);
        }

        // 复制数据
        try (InputStream  in  = new BufferedInputStream (new FileInputStream (srcFile), BUF);
             OutputStream out = new BufferedOutputStream(new FileOutputStream(destFile), BUF)) {

            byte[] buf = new byte[BUF];
            int len;
            while ((len = in.read(buf)) != -1) {
                out.write(buf, 0, len);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        File src  = new File("E:/CODES/JAVA");
        File dest = new File("E:/CODES/JAVA_BACKUP_IO");
        Copy(src, dest);
        System.out.println("复制完成！");
    }
}



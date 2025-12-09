from moviepy import VideoFileClip

def convert_mp4_to_mp3(mp4_file, mp3_file):
    """
    将 MP4 文件转换为 MP3 文件
    :param mp4_file: 输入的 MP4 文件路径
    :param mp3_file: 输出的 MP3 文件路径
    """
    # 使用 VideoFileClip 打开视频文件
    video = VideoFileClip(mp4_file)
    
    # 提取音频并保存为 MP3 文件
    video.audio.write_audiofile(mp3_file)
    
    # 关闭视频文件
    video.close()
    print(f"转换完成，MP3 文件已保存到：{mp3_file}")

# 示例用法
mp4_file = "E:\\code for vs code\\py\\someThingFun\\test1.mp4"  # 替换为你的 MP4 文件路径
mp3_file = "E:\\code for vs code\\py\\someThingFun\\output.mp3"   # 替换为你想要保存的 MP3 文件路径
convert_mp4_to_mp3(mp4_file, mp3_file)


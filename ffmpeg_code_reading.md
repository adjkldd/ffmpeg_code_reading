# ffmpeg 源码阅读之路

## 编译最初的源代码

```sh
git checkout 9aeeeb63f7 -b initial
```

这样checkout出来的代码不能通过编译，需要执行一下步骤： 

1. 注释掉 libav/common.h 里面的 log2 函数 

2. 终端执行以下命令 

```sh
sudo apt install libv4l-dev
cd /usr/include
ln -s libv4l1-videodev.h linux/videodev.h
```
现在执行 `make` 就能成功了



## 运行最初版 ffmpeg

**ffmpeg** 是最新版本；**./ffmpeg** 是此次编译的版本，该版本不能运行在现代 Linux 系统

### 产生数据源

* 视频 oceans.flv 的音视频格式为：
  * 音频： 采样率 48000HZ
  * 视频：fps 为24，宽高：960x400

* 获取原始音频

  `ffmpeg -i ../oceans.flv  -t 10 -f s16le -acodec pcm_s16le out.pcm`

* 获取原始视频

  ```sh
  ffmpeg -i ../oceans.flv -c:v rawvideo -pix_fmt yuv420p out.yuv
  ffmpeg -s 960x400 -pix_fmt yuv420p -i out.yuv -t 10 -c copy -f segment -segment_time 0.01 yuv/frames%d.yuv
  for f in `ls yuv/*`; do ./get_yuv_compo $f -s 960x400; done
  ```

### 运行最初版编码

* 音频

  `./ffmpeg -vn -ac 2 -ar 44100  -ab 128 /home/ldd/volte/foo/foo.rm /home/ldd/volte/foo/out.pcm`

* 视频

  `./ffmpeg -s 960x400 -r 24 -b 200 -an /home/ldd/volte/foo/foo.rm /home/ldd/volte/foo/yuv/frames`

* 音视频

  `./ffmpeg -s 960x400 -r 24 -ac 2 -ar 44100 -b 200 -ab 128 /home/ldd/volte/foo/foo.rm /home/ldd/volte/foo/yuv/frames /home/ldd/volte/foo/out.pcm`
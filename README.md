# IYUV_i420_Decoder
1. 有YUV三个通道
2. Y是height*width bytes
3. U是height*width/4 bytes
4. V是height*width/4 bytes
* 坐标转换:
```C++
auto pixData = raw[width*height * 5 / 4 + int((i / 2)*width / 2 + j / 2)];
```

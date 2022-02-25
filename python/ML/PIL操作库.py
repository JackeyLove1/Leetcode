# 打开显示图片
from PIL import Image

image = Image.open('2092.jpg')
image.show()
image.save('1.jpg')
print(image.mode, image.size, image.format)
# RGB (481, 321) JPEG

# 转换图片格式
# 任何支持的图片模式都可以直接转为彩色模式或者灰度模式，
# 但是，若是想转化为其他模式，则需要借助一个中间模式（通常是彩色）来进行过转
image.show()
grey_image = image.convert('L') # L为灰度
grey_image.show()

# 通道分离合并
# 彩色图像可以分离出 R、G、B 通道，但若是灰度图像，则返回灰度图像本身。
# 然后，可以将 R、G、B 通道按照一定的顺序再合并成彩色图像。
r, g, b = image.split()
im = Image.merge('RGB', (b, g, r))

# 图片剪裁，旋转和改变大小
box = (100, 100, 300, 300)
region = image.crop(box)
region = region.transpose(Image.ROTATE_180)
image.paste(region, box)
image.show()
im = image.resize((300, 300))
im = image.rotate(45)  # 逆时针旋转 45 度
im = image.transpose(Image.FLIP_LEFT_RIGHT) # 左右翻转
im = im.transpose(Image.FLIP_TOP_BOTTOM)# 上下翻转

# 像素值操作
out = image.point(lambda i: i * 1.2) # 对每个像素值乘以 1.2

source = image.split()
out = source[0].point(lambda i: i > 128 and 255) # 对 R 通道进行二值化

# 和numpy之间转化
array = np.array(image)
print(array.shape) #(321, 481, 3)
out = Image.fromarray(array)

# 将numpy转化为PIL
import matplotlib.image as mpimg
from PIL import Image
lena = mpimg.imread('lena.png') # 这里读入的数据是 float32 型的，范围是0-1
im = Image.fromarray(np.uinit8(lena*255))


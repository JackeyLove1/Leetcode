# 使用cv2
import cv2
img_new = cv2.resize(image, (width_new, height_new))

# 使用pillow
import pillow
    def letterbox_image(self, image, size):  # 将图片剪裁到size大小
        if self.input_shape[-1] == 1:
            image = image.convert("RGB")
        iw, ih = image.size
        w, h = size
        scale = min(w / iw, h / ih)
        nw = int(iw * scale)
        nh = int(ih * scale)

        image = image.resize((nw, nh), Image.BICUBIC)
        new_image = Image.new('RGB', size, (128, 128, 128))  # 生成一个新的图像
        new_image.paste(image, ((w - nw) // 2, (h - nh) // 2)) 
        if self.input_shape[-1] == 1:
            new_image = new_image.convert("L")
        return new_image

# tensor和image相互转化
# torch.Tensor -> PIL.Image.
import PIL
image = PIL.Image.fromarray(torch.clamp(tensor * 255, min=0, max=255
    ).byte().permute(1, 2, 0).cpu().numpy())
image = torchvision.transforms.functional.to_pil_image(tensor)  # Equivalently way

# PIL.Image -> torch.Tensor.
tensor = torch.from_numpy(np.asarray(PIL.Image.open(path))
    ).permute(2, 0, 1).float() / 255
tensor = torchvision.transforms.functional.to_tensor(PIL.Image.open(path))  # Equivalently way

# np.ndarray -> PIL.Image.
image = PIL.Image.fromarray(ndarray.astypde(np.uint8))

# PIL.Image -> np.ndarray.
ndarray = np.asarray(PIL.Image.open(path))


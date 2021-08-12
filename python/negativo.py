import sys

def read(path):
    image = open(path)
    lines = image.readlines()
    return lines


def comments_count(image, index):
    while image[index][0] == "#":
        index += 1
    return index


def get_props(image, index):
    width, height = image[index].split()
    index += 1
    maxlevel = image[index]
    return int(width), int(height), int(maxlevel), index


def transform_in_array(file, index):
    image = []
    while index < len(file):
        line = file[index].split()
        for pixel in line:
            image.append(pixel)
        index += 1
    return image

def write_image(name, extension, width, heigth, maxlevel):
    out = open(f"{name}.pgm", "w")
    out.write(f"{extension}\n")
    out.write("# processado por Bruno R Santos\n")
    out.write(f"{width} {heigth}\n")
    out.write(f"{maxlevel}\n")
    for pixel in image:
        out.writelines(f"{ml - int(pixel):<3} ")
    out.write("\n")
    out.close()



if __name__ == "__main__":
    file = read("stanford.pgm")

    extension = file[0].split()[0]
    if(extension != "P2"):
        print("arquivo não suportado.")
        sys.exit()

    index = comments_count(file, 1)

    wd, hg, ml, index = get_props(file, index)

    image = transform_in_array(file, index)

    write_image("out",extension, wd, hg, ml)

    

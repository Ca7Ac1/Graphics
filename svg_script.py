# <g transform ="translate(0.000000,472.000000) scale(0.100000,-0.100000)"
# fill="#000000" stroke="none">

input_file = "v36.svg"
output_file = "gallery_script"

info = []
with open(input_file) as f:
    info = f.read()

    info = info.strip('"')

    while "\n" in info:
        info = info.replace("\n", " ")

    while "  " in info:
        info = info.replace("  ", " ")

    while '""' in info:
        info = info.replace('""', '"')

info = info.split('"')
script_info = ""


for i in info:
    prev_x = 0.0
    prev_y = 0

    curr_x = 0.0
    curr_y = 0

    scale_x = .1
    scale_y = -.1

    translate_x = 0.0
    translate_y = 472.0

    j = 0

    cmd = i.split(" ")

    while j < len(cmd):
        if cmd[j] == "M":
            prev_x = int(cmd[j + 1])
            prev_y = int(cmd[j + 2])

            curr_x = int(cmd[j + 1])
            curr_y = int(cmd[j + 2])

            j += 3

        elif cmd[j] == 'l':
            j += 1

            while (cmd[j].isnumeric() or (cmd[j][1:].isnumeric() and cmd[j][0] == '-')):
                x = int(cmd[j]) + curr_x
                y = int(cmd[j + 1]) + curr_y

                script_info += f"line\n{int(curr_x * scale_x)} {int(curr_y * scale_y)} 0 {int(x * scale_x)} {int(y * scale_y)} 0\n"

                curr_x = x
                curr_y = y

                j += 2

        elif cmd[j] == 'c':
            j += 1

            while (cmd[j].isnumeric() or (cmd[j][1:].isnumeric() and cmd[j][0] == '-')):
                try:
                    x0 = int(cmd[j]) + curr_x
                    y0 = int(cmd[j + 1]) + curr_y
                    x1 = int(cmd[j + 2]) + curr_x
                    y1 = int(cmd[j + 3]) + curr_y
                    x2 = int(cmd[j + 4]) + curr_x
                    y2 = int(cmd[j + 5]) + curr_y
                except:
                    print(cmd)
                    quit()

                script_info += f"bezier\n{int(curr_x * scale_x + translate_x)} {int(curr_y * scale_y + translate_y)} {int(x0 * scale_x + translate_x)} {int(y0 * scale_y + translate_y)} {int(x1 * scale_x + translate_x)} {int(y1 * scale_y + translate_y)} {int(x2 * scale_x + translate_x)} {int(y2 * scale_y + translate_y)}\n"

                curr_x = x2
                curr_y = y2

                j += 6

        elif cmd[j] == 'z':
            script_info += f"line\n{int(curr_x * scale_x + translate_x)} {int(curr_y * scale_y + translate_y)} 0 {int(prev_x * scale_x + translate_x)} {int(prev_y * scale_y + translate_y)} 0\n"
            j += 1

        else:
            print("bad: " + cmd[j])
            quit()

script_info += "save\ngallery.ppm"

with open(output_file, 'w') as f:
    f.write(script_info)

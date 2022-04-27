input_file = "model"
output_file = "gallery_code"

info = []
with open(input_file) as f:
    info = f.read()

    info = info.split('\n')

vectors = []
faces = []
for i in info:
    if i.split(" ")[0] == 'v':
        vectors.append(i.split(" ")[1:])
    elif i.split(" ")[0] == 'f':
        faces.append(i.split(" ")[1:])

output_info = ""

actual_faces = []

for i in range(len(faces)):
    for j in range(len(faces[i])):
        faces[i][j] = faces[i][j][:faces[i][j].find("/")]

for i in faces:
    try:
        output_info += f'''g3d.addPolygon({vectors[int(i[0]) - 1][0]}, {vectors[int(i[0]) - 1][1]}, {vectors[int(i[0]) - 1][2]},
                                        {vectors[int(i[1]) - 1][0]}, {vectors[int(i[1]) - 1][1]}, {vectors[int(i[1]) - 1][2]},
                                        {vectors[int(i[2]) - 1][0]}, {vectors[int(i[2]) - 1][1]}, {vectors[int(i[2]) - 1][2]});\n'''
    except Exception as e:
        print(i)
        print(e)


with open(output_file, 'w') as f:
    f.write(output_info)
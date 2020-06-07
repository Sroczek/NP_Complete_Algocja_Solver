import os
import re

output_file = ""

def concat(files):
    res = ""
    for file in files:
        f = open("./src/" + file)
        for line in f:
            if line[:2] != "//"\
                    and re.search("#include \".*\"", line) is None\
                    and line[:3] != "#if"\
                    and line[:3] != "#un"\
                    and line[:3] != "#en"\
                    and line[:3] != "#de":
                res += line
            else:
                print(line)
    return res

# h = list(filter( lambda x: x[-1] == 'h', os.listdir("./src")))
cpp = list(filter( lambda x: x[-1] == 'p' and x != "main.cpp", os.listdir("./src")))

output_file += concat(["Exercise.h", "Node.h", "Graph.h", "Algorythm.h", "InputReader.h"])
output_file += concat(cpp)
output_file += concat(["main.cpp"])

imports = set()
of = ""
for line in output_file.split("\n"):
    if len(line) < 1:
        of += "\n"
        continue
    if line[0] == '#':
        imports.add(line + "\n")
    else:
        of += line + "\n"

im = ""
for i in imports:
    im += i

output_file = im + of

# usuniecie zduplikowanych newLine
res = ""
flag = False
for line in output_file.split("\n"):
    if not flag and len(line) == 0:
        flag = True
        res += "\n"
        continue

    if flag and len(line) == 0:
        continue

    if flag and len(line) > 0:
        flag = False

    res += line + "\n"

output_file = res

f = open("algo.cpp", "w")
f.write(output_file)
f.close()

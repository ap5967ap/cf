f=open('cp.py','r')
output='exec("".join(chr(len(i)) for i in "'
for l in f.readlines():
    for ch in l:
        output+=(" "*ord(ch))
        output+=chr(9)
output=output[:-1]+'".split("	")))'
f.close()
with open('cp1.py','w') as g:
    g.write(output)
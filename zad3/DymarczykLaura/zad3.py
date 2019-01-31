
f = open("test.txt", "r")
line = f.read()
f.close()

splited = line.split("\n")
count = splited[0]
graph=[]

for i in range(int(count)):
    graph.append([])
    
for j in range(int(count)):
    for k in range(int(count)):
        graph[j].append(0)

for l in range(len(splited)-1):
    tmp = splited[l+1].split(" ")
    graph[int(tmp[0])][int(tmp[1])] = 1
    graph[int(tmp[1])][int(tmp[0])] = 1

print(graph)

def bronk2(R, P, X, g):
    if not any((P, X)):
        yield R
    for v in P[:]:
        R_v = R + [v]
        P_v = [v1 for v1 in P if v1 in N(v, g)]
        X_v = [v1 for v1 in X if v1 in N(v, g)]
        for r in bronk2(R_v, P_v, X_v, g):
            yield r
        P.remove(v)
        X.append(v)
def N(v, g):
    return [i for i, n_v in enumerate(g[v]) if n_v]

print(list(bronk2([], [0,1,2,3,4], [], graph)))

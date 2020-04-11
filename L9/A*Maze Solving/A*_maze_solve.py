import sys
import pickle
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np
from fibheap import Node, Fheap


if len(sys.argv) < 2:
	print(f'Usage : python3 {sys.argv[0]} inputFileName')
	exit(0)

with open(sys.argv[1],'rb') as f:
	maze = pickle.load(f)

n = len(maze)
m = len(maze[0])

def out_format(points):
	res = ""
	for point in points:
		res += str(point) + "->"

	res = res[:(-1)*len("->")]
	return res



print('''
Please Choose A Heuristic For The A* Algorithm:
	1. Manhattan Distance
	2. Diagonal Distance
	3. Euclidean Distance
''')

option = input()[0]

if option != '1' and option != '2' and option != '3':
	print("Please Enter a correct option next time :)")
	exit(0)

def check(point):
    if point[0] >= 0 and point[0] < m and point[1] >= 0 and point[1] < n:
        if maze[point[1]][point[0]] == 1:
            return True
    return False

source = input("Enter source coordinates separated by a space : ")
source = source.split(' ')
source = (int(source[0]),int(source[1]))

if check(source) != True:
	print("Invalid point for source")

destination = input("Enter destination coordinates separated by a space : ")
destination = destination.split(' ')
destination = (int(destination[0]),int(destination[1]))

if check(destination) != True:
	print("Invalid point for destination")

infinity = 2**32 - 1




def get_adjacency(node):
    adj = []
    x = node.x
    y = node.y

    if check(((x,y+1))):
        adj.append(((x,y+1)))
    if check(((x,y-1))):
        adj.append(((x,y-1)))

    if check(((x+1,y))):
        adj.append(((x+1,y)))
    if check(((x+1,y+1))):
        adj.append(((x+1,y+1)))
    if check(((x+1,y-1))):
        adj.append(((x+1,y-1)))

    
    if check(((x-1,y))):
        adj.append(((x-1,y)))
    if check(((x-1,y+1))):
        adj.append(((x-1,y+1)))
    if check(((x-1,y-1))):
        adj.append(((x-1,y-1)))

    return adj

queue = Fheap()

node_dict = {}

for y in range(n):
	for x in range(m):
		if y == source[1] and x == source[0]:
			node = Node(destination[1],destination[0],x,y,0,option)
			node.val = 0
			queue.insert(node)
			node_dict.update({(x,y):node})

		elif maze[y][x] != 0:
			node = Node(destination[1],destination[0],x,y,infinity,option)
			queue.insert(node)
			node_dict.update({(x,y):node})

is_visited = [[False for x in range(m)] for y in range(n)]

while True:
	node = queue.extract_min()
	is_visited[node.y][node.x] = True
	if node == node_dict[(m-1,n-1)]:
		break

	adj = get_adjacency(node)

	for point in adj:
		if is_visited[point[1]][point[0]]:
			continue

		p = node_dict[point]
		if node.val + 1 < p.val:
			p.parent = node
			p.val = node.val + 1
			queue.decrease_key(p, p.val + p.distance)

arr = []
node = node_dict[destination]
while True:
	if node == None:
		break
	arr.append(node)
	node = node.parent

arr.reverse()
print("Steps : {}".format(len(arr)-1))
print(out_format(arr))

maze[source[1]][source[0]] = 0.25
maze[destination[1]][destination[0]] = 0.75
arr = arr[1:-1]
for p in arr:
	maze[p.y][p.x] = 0.5

colors = [(0,"black"),(0.25,"green"),(0.5,"blue"),(0.75,"red"),(1,"white")]
mycmap = mcolors.LinearSegmentedColormap.from_list("my_colormap", colors)



plt.imshow(maze, cmap = mycmap)

ax = plt.gca();

# Major ticks
ax.set_xticks(np.arange(0, m, 1));
ax.set_yticks(np.arange(0, n, 1));

# Labels for major ticks
ax.set_xticklabels(np.arange(0, m, 1));
ax.set_yticklabels(np.arange(0, n, 1));

# Minor ticks
ax.set_xticks(np.arange(-0.5, m, 1), minor=True);
ax.set_yticks(np.arange(-0.5, n, 1), minor=True);

# Gridlines based on minor ticks
ax.grid(which='minor', color='grey', linestyle='-', linewidth=2)
ax.invert_yaxis()
plt.show()
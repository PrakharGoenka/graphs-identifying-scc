from graphviz import Digraph


def createVisualization(nodes, edges, ext, path):
    graph = Digraph()
    graph.format = ext

    for i in range(nodes):
        graph.node(str(i))
    
    for [src, dest] in edges:
        graph.edge(str(src), str(dest))

    graph.render(path, view='True')
    
if __name__ == "__main__":
    userInput = ''
    with open('input.txt') as f:
        userInput = f.read()
    userInput = userInput.split(' ')
    print(userInput)
    createVisualization(4, [[0, 1], [1, 2], [2, 3], [0, 3]], 'svg', 'visuaal.gv')

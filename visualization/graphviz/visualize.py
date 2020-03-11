from graphviz import Digraph


def createVisualization(nodes, edges, ext, path):
    graph = Digraph()
    graph.format = ext

    for i in range(nodes):
        graph.node(str(i))
    
    for [src, dest] in edges:
        graph.edge(str(src), str(dest))

    graph.render(path, view='True')


def getGraph(path):
    lines = []
    userInput = []  
    with open(path) as f:
        lines = f.readlines()
    
    for line in lines:
        userInput.append(line.split())

    nodes = int(userInput[0][0])
    degree = int(userInput[0][1])
    
    edges = []
    for [src, dest] in userInput[1: degree+1]:
        edges.append([int(src), int(dest)])
    
    return nodes, edges
    
    
if __name__ == "__main__":
    nodes, edges = getGraph('input.txt')
    createVisualization(nodes, edges, 'svg', 'visual.gv')

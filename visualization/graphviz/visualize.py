from graphviz import Digraph

# function to create visualization
def createVisualization(nodes, edges, ext, path):
    graph = Digraph()
    graph.format = ext

    # add nodes
    for i in range(nodes):
        graph.node(str(i))
    
    # add edges
    for [src, dest] in edges:
        graph.edge(str(src), str(dest))

    graph.render(path, view='True')
    

# method to read user input from file and build graph
# parameter: path of the user input file
# returns: number of nodes, and list of edges
def getGraph(path):
    lines = []
    with open(path) as f:
        lines = f.readlines()
    
    userInput = [] # list of lists of space split lines
    for line in lines:
        userInput.append(line.split())

    # nodes and edges given in 1st line of user input
    nodes = int(userInput[0][0])
    degree = int(userInput[0][1])
    
    edges = [] # list of lists to store edges
    for [src, dest] in userInput[1: degree+1]: # edges start from 2nd line
        edges.append([int(src), int(dest)])
    
    return nodes, edges
    
    
if __name__ == "__main__":
    nodes, edges = getGraph('input.txt')
    createVisualization(nodes, edges, 'svg', 'visual.gv')

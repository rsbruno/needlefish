import queue


class HuffmanNode(object):
    def __init__(self, left=None, right=None, root=None):
        self.left = left
        self.right = right
        self.root = root

    def children(self):
        return (self.left, self.right)

    def preorder(self, path=None):
        if path is None:
            path = []
        if self.left is not None:
            if isinstance(self.left[1], HuffmanNode):
                self.left[1].preorder(path+[0])
            else:
                print(self.left, path+[0])
        if self.right is not None:
            if isinstance(self.right[1], HuffmanNode):
                self.right[1].preorder(path+[1])
            else:
                print(self.right, path+[1])

    def decode(self, arrCode):
        aux = self
        decoded = ""
        code = ""
        for c in arrCode:
            if(c == 0):
                aux = aux.left[1]
            elif(c == 1):
                aux = aux.right[1]
            code = code + str(c)     
            if(isinstance(aux, str)):
                decoded = decoded + aux
                code =  code + "-" 
                aux = self
        print(code)
        return decoded


freq = [
    (22, 'a'), (17, 'b'), (2, 'c'), (1, 'd')]


def encode(frequencies):
    p = queue.PriorityQueue()
    for item in frequencies:
        p.put(item)

    # invariant that order is ascending in the priority queue
    # p.size() gives list of elements
    while p.qsize() > 1:
        left, right = p.get(), p.get()
        node = HuffmanNode(left, right)
        p.put((left[0]+right[0], node))
    return p.get()


node = encode(freq)
print(node[1].decode([0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,
0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1]))

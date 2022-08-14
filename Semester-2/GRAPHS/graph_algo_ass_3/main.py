import copy
import random
import time


class Graph:
    def __init__(self, m=set(), n=set()):
        self.inbound = dict()
        self.outbound = dict()
        self.costs = dict()
        for vertex in m:
            self.add_vertex(vertex)
        for edge in n:
            self.add_edge(edge[0], edge[1], set_cost_to_edge())

    def add_vertex(self, vertex):
        self.inbound[vertex] = list()
        self.outbound[vertex] = list()

    def add_edge(self, starting_point, ending_point, value):
        if starting_point not in self.outbound.keys():
            self.add_vertex(starting_point)
        self.outbound[starting_point].append(ending_point)
        if ending_point not in self.inbound.keys():
            self.add_vertex(ending_point)
        self.inbound[ending_point].append(starting_point)
        if (starting_point, ending_point) not in self.costs.keys():
            self.costs[(starting_point, ending_point)] = value
        else:
            raise ValueError("Edge already exists!")

    def set_cost(self, starting_point, ending_point, value):
        self.costs[(starting_point, ending_point)] = value

    def get_cost(self, starting_point, ending_point):
        return self.costs[(starting_point, ending_point)]

    def get_number_vertices(self):
        return len(self.inbound.keys())

    def parse_vertices(self):
        return [x for x in self.inbound.keys()]

    def parse_nout(self, x):
        return [y for y in self.outbound[x]]

    def parse_nin(self, x):
        return [y for y in self.inbound[x]]

    def get_in_out_degree(self, x):
        in_deg = len(self.inbound[x])
        out_deg = len(self.outbound[x])
        return in_deg, out_deg

    def parse_graph(self):
        print("Outbound vertices:")
        start = time.time()
        for x in self.outbound.keys():
            for y in self.outbound[x]:
                pass
        print("Finished in %sms" % (1000 * (time.time() - start),))
        print("Inbound vertices:")
        start = time.time()
        for x in self.inbound.keys():
            for y in self.inbound[x]:
                pass
        print("Finished in %sms" % (1000 * (time.time() - start),))

    def remove_edge(self, starting_point, ending_point):
        """
        removes an edge from the graph and from the costs dictionary
        :param starting_point: a vertex of the graph
        :param ending_point:a vertex of the graph
        :return:
        """
        remove_key = self.costs.pop((starting_point, ending_point), None)
        if remove_key is None:
            raise ValueError("Edge was not in the graph")

    def remove_vertex(self, vertex):
        """
        removes a vertex from the graph
        :param vertex:
        :return:
        """
        for starting_vertex in self.inbound[vertex]:
            self.costs.pop((starting_vertex, vertex))
        for ending_vertex in self.outbound[vertex]:
            self.costs.pop((vertex, ending_vertex))
        self.inbound.pop(vertex)
        self.outbound.pop(vertex)

    def is_isolated(self, vertex):
        """
        returns true if the vertex has no inbounds and outbounds
        :param vertex: a vertex in the graph
        :return: true or false
        """
        return len(self.inbound[vertex]) == 0 and len(self.outbound[vertex]) == 0

    def is_edge(self, x, y):
        """
        checks in (x,y) is an edge
        :param x: a vertex in the graph
        :param y: a vertex in the graph
        :return:
        """
        return (x, y) in self.costs.keys()

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.costs.keys():
            repository_list_form.append(f"({item[0]},{item[1]}), cost:{self.costs[item]}")
        return repository_list_form

    def get_all_edges(self):
        """
        This function returns the contents of the repository in form of a list of objects
        :return: a list of objects
        """
        repository_list_form = list()
        for item in self.costs.keys():
            repository_list_form.append((item, self.costs[item]))
        return repository_list_form

    def copy_graph(self):
        """
        this function creates another graph object with the same edges, vertices and costs of an instance
        :return: graph object
        """
        return Graph(set(self.inbound.keys()), set(self.costs.keys()))


class WolfGoatCabbageGraph:
    def is_edge(self, x, y):
        for tmp in x.parse_neighbours():
            if tmp == y:
                return True
        return False

    def parse_vertices(self):
        for st in range(16):
            tmp = st
            d = dict()
            for key in ["w", "g", "c", "b"]:
                d[key] = (tmp % 2 == 1)
                tmp = tmp // 2
            state = WolfGoatCabbageState(d)
            if state.is_valid():
                yield state

    def parse_nout(self, x):
        return x.parse_neighbours()

    def parse_nin(self, x):
        return x.parse_neighbours()

    def initial_state(self):
        return WolfGoatCabbageState({key: False for key in ["w", "g", "c", "b"]})

    def final_state(self):
        return WolfGoatCabbageState({key: True for key in ["w", "g", "c", "b"]})


class WolfGoatCabbageState:
    def __init__(self, dictionary):
        self.__dict = copy.copy(dictionary)

    def __str__(self):
        result = "|"
        for key, value in self.__dict.items():
            if value:
                result = result + key
            else:
                result = key + result
        return result

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        return isinstance(other, WolfGoatCabbageState) and self.__dict == other.__dict

    def __hash__(self):  # IEN137
        val = 0
        for key in ["w", "g", "c", "b"]:
            val = val * 2
            if self.__dict[key]:
                val = val + 1
        return val

    def parse_neighbours(self):
        """
        Returns an iterable with the states that can be reached in one move from the current one
        :return:
        """
        for key in ["w", "g", "c", "b"]:
            if self.__dict['b'] == self.__dict[key]:
                copy_state_dict = copy.copy(self.__dict)
                copy_state_dict['b'] = not copy_state_dict['b']
                if key != 'b':
                    copy_state_dict[key] = not copy_state_dict[key]
                copy_state = WolfGoatCabbageState(copy_state_dict)
                if copy_state.is_valid():
                    yield copy_state

    def is_valid(self):
        """
        Returns true if nobody eats anybody in the current state
        :return:
        """
        if self.__dict['g'] == self.__dict['b']:
            return True
        return self.__dict['g'] != self.__dict['w'] and self.__dict['g'] != self.__dict['c']


def build_random_graph(n, m):
    """
    builds a random graph
    :param n: integer
    :param m: integer
    :return: a graph
    """
    edges = set()
    while len(edges) < m:
        x = random.randrange(n)
        y = random.randrange(n)
        edges.add((x, y))
    vertices = set()
    for x in range(n):
        vertices.add(x)
    return Graph(vertices, edges)


def set_cost_to_edge():
    """
    this function returns a random integer from 1 to 100 which can be assigned to an edge as its cost
    :return: integer
    """
    return random.randint(1, 100)


def load_file(file_name):
    """
    Reads the information about a graph from a file, in the required form.
    :param file_name: a string, a valid file name
    :return: a graph object
    """
    graph = Graph()
    file = open(file_name, "rt")  # rt -> read, text-mode
    vertices_and_edges = file.readline()
    vertices = vertices_and_edges.split(" ")[0]
    for i in range(int(vertices)):
        graph.add_vertex(i)
    for line in file.readlines():
        starting_point, ending_point, cost = line.split(sep=' ')
        cost = cost.strip('\n')
        graph.add_edge(int(starting_point), int(ending_point), int(cost))
    file.close()
    return graph


def save_file(graph, file_name):
    """
    Writes the information about a graph in a file, in the required form.
    :param graph: a graph object which contains a dictionary with edges as keys
    :param file_name: a string, a valid file name
    :return: none
    """
    file = open(file_name, "wt")  # wt -> write, text-mode
    number_vertices = len(graph.inbound.keys())
    number_edges = len(graph.costs.keys())
    file.write(str(number_vertices) + ' ' + str(number_edges))
    for edge in graph.costs.keys():
        file.write(str(edge[0]) + ' ' + str(edge[1]) + ' ' + str(graph.costs[edge]) + "\n")
    file.close()


def bfs_forward(g, s):
    """
    Performs a BFS of the graph g starting from vertex t.
    Returns a pair of dictionaries, (dist, next)
    where the keys are the accessible vertices
    and the values are the distances from start to the vertex and,
    respectively, the next vertex on the optimal path.
    """
    queue = [s]
    queue_start = 0
    distances = {}
    prev = {s: None}
    visited = set()
    visited.add(s)
    distances[s] = 0
    while queue_start < len(queue):
        current = queue[queue_start]
        for x in g.parse_nout(current):
            if x not in visited:
                visited.add(x)
                queue.append(x)
                distances[x] = distances[current] + 1
                prev[x] = current
        queue_start += 1
    return distances, prev


def bfs_backward(g, distance_list, visited_list, to_v):
    visited_list[to_v] = 1
    paths = list()
    for i in g.inbound[to_v]:
        if visited_list[i] == 0:
            paths.append(i)
    if len(paths) == 0:
        return
    for i in paths:
        if g.is_edge(i, to_v):
            if distance_list[i] > distance_list[to_v] + 1:
                distance_list[i] = distance_list[to_v] + 1
            bfs_backward(g, distance_list, visited_list, i)


def shortest_path_bw(g, from_v, to_v):
    distance = dict()
    visited = dict()
    for i in g.inbound.keys():
        visited[i] = 0
        distance[i] = 99999
    for i in g.inbound[to_v]:
        distance[i] = 1
    distance[to_v] = 0
    bfs_backward(g, distance, visited, to_v)
    path = [from_v]
    for vertex in distance:
        if distance[vertex] == distance[from_v] - 1 and g.is_edge(from_v, vertex):
            path.append(vertex)
            from_v = vertex
    if len(path) == 1:
        # print("there is no path between those two vertices")
        return
    return path


def shortest_path_fw(g, s, t):
    """
    Computes the shortest path (minimum number of edges) in graph get
    from vertex s to vertex t.
    Returns a list of vertices starting with s and ending with t.
    If s==t the function will return [s]. If there is no path, it returns
    None
    """
    dist, _ = bfs_forward(g, s)
    if t not in dist:
        return None

    path = []
    current_vertex = t
    while current_vertex != s:
        path.append(current_vertex)
        for neighbour in g.parse_nin(current_vertex):
            if neighbour in dist and dist[neighbour] == dist[current_vertex] - 1:
                current_vertex = neighbour
                break
    path.append(s)
    path.reverse()
    return path


def test_wolf_goat_cabbage():
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    print(shortest_path_fw(g, s, t))


def Ford_algorithm(g, s, t):
    """
    This function creates and uses 2 dictionaries, one for retaining the path chosen and one for the distances to
    each vertex from the source vertex s
    :param g: a Graph object
    :param s: a vertex from the graph
    :return: two dictionaries, one with the minimum cost walk(number) as value to the vertex as key
    """
    dist = dict()
    prev = dict()
    prev[s] = -1
    for x in g.inbound.keys():
        dist[x] = 1000000
    dist[s] = 0
    changed = True
    while changed:
        changed = False
        for (x, y) in g.costs.keys():
            if dist[y] > dist[x] + g.costs[(x, y)]:
                dist[y] = dist[x] + g.costs[(x, y)]
                prev[y] = x
                changed = True
    return dist, prev


def bfs_forward(g, s):
    """
    Performs a BFS of the graph g starting from vertex t.
    Returns a pair of dictionaries, (dist, next)
    where the keys are the accessible vertices
    and the values are the distances from start to the vertex and,
    respectively, the next vertex on the optimal path.
    """
    queue = [s]
    queue_start = 0
    distances = {}
    prev = {s: None}
    visited = set()
    visited.add(s)
    distances[s] = 0
    while queue_start < len(queue):
        current = queue[queue_start]
        for x in g.parse_nout(current):
            if x not in visited:
                visited.add(x)
                queue.append(x)
                distances[x] = distances[current] + 1
                prev[x] = current
        queue_start += 1
    return distances, prev


def topo_sort_prev(g):
    X = g.copy_graph()
    sorted = list()
    start = 0
    q = list()
    count = dict()
    for x in X.inbound.keys():
        count[x] = X.get_in_out_degree(x)[0]
        if count[x] == 0:
            q.append(x)
    while start < len(q):
        x = q[start]
        start += 1
        sorted.append(x)
        for y in X.outbound[x]:
            count[y] = count[y] - 1
            if count[y] == 0:
                q.append(y)
    if len(sorted) < len(X.inbound.keys()):
        sorted = []
    return sorted


def print_create_graph_menu():
    print("1. to load the graph repo from the file\n"
          "2. to build random graph\n"
          "0. to exit")


def print_menu():
    print("3. to write the graph repo to a file\n"
          "4. to display the graph\n"
          "5. to create a copy of the graph\n"
          "6. to get the in and out degree of a vertex\n"
          "7. to parse graph\n"
          "8. to add a vertex\n"
          "9. to add an edge\n"
          "10. to remove a vertex\n"
          "11. to remove an edge\n"
          "12. to update the cost of an edge\n"
          "13. to check if there is an edge between two vertices\n"
          "14. to display the number of vertices\n"
          "15. to display all the vertices\n"
          "16. to display a list with the lowest cost walk between two vertices\n"
          "0. to exit")


def valid(file_name):
    """
    Checks if a file_name is valid aka .txt appears in its name
    file_name: a string
    :return true or false
    """
    file_name_tokens = file_name.split(sep=".")
    if len(file_name_tokens) == 2:
        if file_name_tokens[1] == 'txt':
            return True
    return False


def main():
    # graph_repo = Graph()
    while True:
        print_create_graph_menu()
        user_command = input(">>")
        if user_command == '1':
            file_name = "digraph_ex1.txt"
            graph_repo = load_file(file_name)
            # file_name_2 = input("file name: ")
            # if valid(file_name_2):
            #     graph_repo = load_file(file_name_2)
            # else:
            #     print("please introduce a valid file name")
        elif user_command == '2':
            no_vertices = input("no_vertices: ")
            no_edges = input("no_edges: ")
            if no_edges.isnumeric() and no_vertices.isnumeric():
                graph_repo = build_random_graph(int(no_vertices), int(no_edges))
            else:
                print("please introduce integers")
                break
        elif user_command == '0':
            print("thank you")
            break
        else:
            print("please introduce a valid option next time")
        while True:
            print_menu()
            user_command = input(">>")
            try:
                if user_command == '3':
                    save_file(graph_repo, "digraph_ex1_output.txt")
                elif user_command == '4':
                    for edge in graph_repo.get_all_str():
                        print(edge)
                elif user_command == '5':
                    new_graph = graph_repo.copy_graph()
                    for edge in new_graph.get_all_str():
                        print(edge)
                elif user_command == '6':
                    vertex = int(input("vertex: "))
                    print(
                        f"in_degree: {graph_repo.get_in_out_degree(vertex)[0]} out_degree: {graph_repo.get_in_out_degree(vertex)[0]}")
                elif user_command == '7':
                    graph_repo.parse_graph()
                elif user_command == '8':
                    vertex = int(input("vertex: "))
                    print(graph_repo.add_vertex(vertex))
                elif user_command == '9':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    cost_answer = input("type 'yes' if u want to add a cost, otherwise it will be generated randomly")
                    if cost_answer == "yes":
                        cost = int(input("cost: "))
                    else:
                        cost = set_cost_to_edge()
                    graph_repo.add_edge(starting_vertex, ending_vertex, cost)
                elif user_command == '10':
                    vertex = int(input("vertex: "))
                    print(graph_repo.remove_vertex(vertex))
                elif user_command == '11':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    graph_repo.remove_edge(starting_vertex, ending_vertex)
                elif user_command == '12':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    new_cost = int(input("new cost: "))
                    graph_repo.set_cost(starting_vertex, ending_vertex, new_cost)
                elif user_command == '13':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    print(graph_repo.is_edge(starting_vertex, ending_vertex))
                elif user_command == '14':
                    print(graph_repo.get_number_vertices())
                elif user_command == '15':
                    print(graph_repo.parse_vertices())
                elif user_command == '16':
                    print(topo_sort_prev(graph_repo))
                elif user_command == '0':
                    print("thank you")
                    break
                else:
                    print("please introduce a valid option")
            except ValueError as ve:
                print(ve)

    file_name = "digraph_ex1.txt"
    graph_repo = load_file(file_name)
    print(topo_sort_prev(graph_repo))

    # file_name = "digraph_ex2.txt"
    # graph_repo = load_file(file_name)
    # print(graph_repo.get_all_edges())
    # print(graph_repo.get_all_str())
    # print(graph_repo.get_in_out_degree(0))
    # graph_repo.parse_graph()
    # print(graph_repo.is_edge(2, 3))
    # graph_repo = build_random_graph(9, 6)
    # print(graph_repo.get_all_edges())
    # graph_repo.parse_graph()
    # new_graph = graph_repo.copy_graph()
    # new_graph.add_edge(19, 20, 5)
    # print(new_graph.get_all_str())
    # new_graph.set_cost(19, 20, 1000)
    # print(new_graph.get_all_str())


main()

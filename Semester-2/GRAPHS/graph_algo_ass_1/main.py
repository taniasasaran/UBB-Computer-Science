import copy
import random
import time


class Graph:
    def __init__(self, m=set(), n=set()):
        """
        this function is the constructor for the graph class
        :param m: set of vertices, empty if not specified in the constructor function
        :param n: set of edges, empty if not specified in the constructor function
        """
        self.inbound = dict()
        self.outbound = dict()
        self.costs = dict()
        for vertex in m:
            self.add_vertex(vertex)
        for edge in n:
            self.add_edge(edge[0], edge[1], set_cost_to_edge())

    def add_vertex(self, vertex):
        """
        it adds the vertex as a key in both the inbound and outbound dictionaries an initializes their values with an empty list
        :param vertex:
        :return: nothing
        """
        self.inbound[vertex] = list()
        self.outbound[vertex] = list()

    def add_edge(self, starting_point, ending_point, value):
        """
        checks if the vertices are part of the graph(aka are keys in the inbound and outbound dictionaries), adds them
        if necessary and then adds the edge to the costs dictionary with the value assigned
        :param starting_point: vertex
        :param ending_point: vertex
        :param value: integer
        :return: raises ValueError if edge already exists
        """
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
        """
        this function assigns a value in the costs dictionary to a specified edge(specified points)
        :param starting_point: vertex
        :param ending_point: vertex
        :param value: integer
        :return: raises ValueError if the edge doesnt exist
        """
        if self.is_edge(starting_point, ending_point):
            self.costs[(starting_point, ending_point)] = value
        else:
            raise ValueError("edge is not in the graph")

    def get_cost(self, starting_point, ending_point):
        """
        this function returns the cost of an edge
        :param starting_point: vertex
        :param ending_point: vertex
        :return: integer
        """
        return self.costs[(starting_point, ending_point)]

    def get_number_vertices(self):
        """
        :return: Returns the number of vertices.
        """
        return len(self.inbound.keys())

    def parse_vertices(self):
        """
        :return: returns a list of all the edges in the graph
        """
        return [x for x in self.inbound.keys()]

    def parse_nout(self, x):
        """
        :param x: vertex
        :return: Returns the outbound list of the vertex x
        """
        if x not in self.outbound.keys():
            raise ValueError("vertex not in graph")
        return [y for y in self.outbound[x]]

    def parse_nin(self, x):
        """
        :param x: vertex
        :return: Returns the inbound list of x
        """
        if x not in self.inbound.keys():
            raise ValueError("vertex not in graph")
        return [y for y in self.inbound[x]]

    def get_in_out_degree(self, x):
        """
        :param x: vertex
        :return: Returns the in and out degrees of a given vertex. Raises ValueError if vertex does not exist.
        """
        if x not in self.outbound.keys():
            raise ValueError("vertex not in graph")
        in_deg = len(self.inbound[x])
        out_deg = len(self.outbound[x])
        return in_deg, out_deg

    def parse_graph(self):
        """
        This function parses the inbound and outbound lists of all vertices in the graph and show how much time it took
        :return:
        """
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
        Removes an edge from the graph. The endpoints lose each other from their in/outbound lists.
        Raises ValueError if the edge does not exist.
        :param starting_point: vertex
        :param ending_point: vertex
        :return: none
        """
        remove_key = self.costs.pop((starting_point, ending_point), None)
        if remove_key is None:
            raise ValueError("Edge was not in the graph")

    def remove_vertex(self, vertex):
        """
        removes a vertex from the graph as well as all the edges to or from that vertex from the costs dictionary
        :param vertex: a vertex of the graph
        :return:
        """
        if vertex not in self.outbound.keys():
            raise ValueError("vertex not in graph")
        for starting_vertex in self.inbound[vertex]:
            self.costs.pop((starting_vertex, vertex))
        for ending_vertex in self.outbound[vertex]:
            self.costs.pop((vertex, ending_vertex))
        self.inbound.pop(vertex)
        self.outbound.pop(vertex)

    def is_edge(self, x, y):
        """
        checks in (x,y) is an edge
        :param x: vertex
        :param y:vertex
        :return: true or false
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
    file.readline()
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


def ui():
    # graph_repo = Graph()
    while True:
        print_create_graph_menu()
        user_command = input(">>")
        if user_command == '1':
            file_name = "digraph_ex1.txt"
            file_name_2 = input("file name: ")
            if valid(file_name_2):
                graph_repo = load_file(file_name_2)
            else:
                print("please introduce a valid file name")
            # graph_repo = load_file(file_name)
        elif user_command == '2':
            no_vertices = input("no_vertices: ")
            no_edges = input("no_edges: ")
            if no_edges.isnumeric() and no_vertices.isnumeric():
                graph_repo = build_random_graph(int(no_vertices), int(no_edges))
            else:
                print("please introduce integers")
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
                elif user_command == '0':
                    print("thank you")
                    break
                else:
                    print("please introduce a valid option")
            except ValueError as ve:
                print(ve)

    file_name = "digraph_ex1.txt"
    graph_repo = load_file(file_name)
    print(graph_repo.get_all_edges())
    print(graph_repo.get_all_str())
    print(graph_repo.get_in_out_degree(0))
    graph_repo.parse_graph()
    print(graph_repo.is_edge(2, 3))
    graph_repo = build_random_graph(9, 6)
    print(graph_repo.get_all_edges())
    graph_repo.parse_graph()
    new_graph = graph_repo.copy_graph()
    new_graph.add_edge(19, 20, 5)
    print(new_graph.get_all_str())
    new_graph.set_cost(19, 20, 1000)
    print(new_graph.get_all_str())


def main():
    ui()


main()

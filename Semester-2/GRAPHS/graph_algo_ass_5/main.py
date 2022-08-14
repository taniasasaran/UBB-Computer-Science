import copy
import random
import time

# a5- pb1
from itertools import combinations


class Graph:
    def __init__(self, m=set(), n=set()):
        self.neighbours = dict()
        self.edges = list()
        for vertex in m:
            self.add_vertex(vertex)
        for edge in n:
            i = min(edge[0], edge[1])
            j = min(edge[0], edge[1])
            self.add_edge(i, j)

    def add_vertex(self, vertex):
        if vertex in self.neighbours.keys():
            raise ValueError("Vertex is already in the graph")
        self.neighbours[vertex] = list()

    def add_edge(self, starting_point, ending_point):
        if (starting_point, ending_point) not in self.edges:
            self.edges.append((min(starting_point, ending_point), max(starting_point, ending_point)))
        else:
            raise ValueError("Edge already exists!")
        if starting_point not in self.neighbours.keys():
            self.add_vertex(starting_point)
        self.neighbours[starting_point].append(ending_point)
        if ending_point not in self.neighbours.keys():
            self.add_vertex(ending_point)
        self.neighbours[ending_point].append(starting_point)

    def get_number_vertices(self):
        return len(self.neighbours.keys())

    def parse_vertices(self):
        return [x for x in self.neighbours.keys()]

    def parse_neighbours(self, x):
        if x not in self.neighbours.keys():
            raise ValueError("Vertex not part of the graph")
        return [y for y in self.neighbours[x]]

    def get_degree(self, x):
        if x not in self.neighbours.keys():
            raise ValueError("Vertex not part of the graph")
        degree = len(self.neighbours[x])
        return degree

    def parse_graph(self):
        print("Edges:")
        start = time.time()
        for edge in self.edges:
            pass
        print("Finished in %sms" % (1000 * (time.time() - start),))

    def remove_edge(self, starting_point, ending_point):
        """
        removes an edge from the graph and from the costs dictionary
        :param starting_point: a vertex of the graph
        :param ending_point:a vertex of the graph
        :return:
        """
        if (min(starting_point, ending_point), max(starting_point, ending_point)) in self.edges:
            self.edges.remove((min(starting_point, ending_point), max(starting_point, ending_point)))
        else:
            raise ValueError("Edge was not in the graph")
        if starting_point in self.neighbours[ending_point]:
            self.neighbours[ending_point].remove(starting_point)
        if ending_point in self.neighbours[starting_point]:
            self.neighbours[starting_point].remove(ending_point)

    def remove_vertex(self, vertex):
        """
        removes a vertex from the graph
        :param vertex:
        :return:
        """
        if vertex not in self.neighbours.keys():
            raise ValueError("Vertex not part of the graph")
        for starting_vertex in self.neighbours[vertex]:
            self.edges.remove((min(starting_vertex, vertex), max(starting_vertex, vertex)))
            self.neighbours[starting_vertex].remove(vertex)
        self.neighbours.pop(vertex)

    def is_isolated(self, vertex):
        """
        returns true if the vertex has no inbounds and outbounds
        :param vertex: a vertex in the graph
        :return: true or false
        """
        return len(self.neighbours[vertex]) == 0

    def is_edge(self, x, y):
        """
        checks in (x,y) is an edge
        :param x: a vertex in the graph
        :param y: a vertex in the graph
        :return:
        """
        return (min(x, y), max(x, y)) in self.edges

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.edges:
            repository_list_form.append(f"({item[0]},{item[1]})")
        return repository_list_form

    def get_all_edges(self):
        """
        This function returns the contents of the repository in form of a list of objects
        :return: a list of objects
        """
        repository_list_form = list()
        for item in self.edges:
            repository_list_form.append(item)
        return repository_list_form

    def copy_graph(self):
        """
        this function creates another graph object with the same edges, vertices and costs of an instance
        :return: graph object
        """
        return Graph(set(self.neighbours.keys()), set(self.edges))


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
        starting_point, ending_point = line.split(sep=' ')
        ending_point.strip('\n')
        graph.add_edge(int(starting_point), int(ending_point))
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
    number_vertices = len(graph.neighbours.keys())
    number_edges = len(graph.edges)
    file.write(str(number_vertices) + ' ' + str(number_edges))
    for edge in graph.edges:
        file.write(str(edge[0]) + ' ' + str(edge[1]) + "\n")
    file.close()


def k_cliques(graph):
    # we see that in a k-clique, if we have a subset of (k-1) vertices, the set will be a clique
    # i used that idea in the following algorithm:

    # start with 2-cliques
    cliques = [{i} for i in graph.neighbours.keys()]
    k = 1

    while cliques:
        # yield the result and come back after finishing working with that result
        yield k, cliques

        # merge k-cliques into (k+1)-cliques:
        # search for possible (k+1)-cliques among the sets that have the intersection = (k-1)
        cliques_1 = set()
        for u, v in combinations(cliques, 2):
            w = u ^ v  # union - intersection
            if len(w) == 2 and graph.is_edge(*w):
                cliques_1.add(tuple(u | w))  # union of u(k elems) and w(2 elems) sets

        cliques = [set(clique) for clique in cliques_1]
        k += 1


def find_clique_maximum_size(graph):
    max_size = 1
    result = ""
    for k, cliques in k_cliques(graph):
        result = f"{k}-cliques = {len(cliques)}, {cliques}."
        max_size += 1
    print(result)


def print_create_graph_menu():
    print("1. to load the graph repo from the file\n"
          "2. to build random graph\n"
          "0. to exit")


def print_menu():
    print("3. to write the graph repo to a file\n"
          "4. to display the graph\n"
          "5. to create a copy of the graph\n"
          "6. to get the degree of a vertex\n"
          "7. to parse graph\n"
          "8. to add a vertex\n"
          "9. to add an edge\n"
          "10. to remove a vertex\n"
          "11. to remove an edge\n"
          "13. to check if there is an edge between two vertices\n"
          "14. to display the number of vertices\n"
          "15. to display all the vertices\n"
          "16. to find clique of maximum size\n"
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
            # file_name = "digraph_ex2.txt"
            # file_name = "digraph_ex3.txt"

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
            break
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
                        f"degree: {graph_repo.get_degree(vertex)}")
                elif user_command == '7':
                    graph_repo.parse_graph()
                elif user_command == '8':
                    vertex = int(input("vertex: "))
                    print(graph_repo.add_vertex(vertex))
                elif user_command == '9':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    graph_repo.add_edge(starting_vertex, ending_vertex)
                elif user_command == '10':
                    vertex = int(input("vertex: "))
                    print(graph_repo.remove_vertex(vertex))
                elif user_command == '11':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    graph_repo.remove_edge(starting_vertex, ending_vertex)
                elif user_command == '13':
                    starting_vertex = int(input("starting_vertex: "))
                    ending_vertex = int(input("ending_vertex: "))
                    print(graph_repo.is_edge(starting_vertex, ending_vertex))
                elif user_command == '14':
                    print(graph_repo.get_number_vertices())
                elif user_command == '15':
                    print(graph_repo.parse_vertices())
                elif user_command == "16":
                    find_clique_maximum_size(graph_repo)
                elif user_command == '0':
                    print("thank you")
                    break
                else:
                    print("please introduce a valid option")
            except ValueError as ve:
                print(ve)

    # file_name = "digraph_ex1.txt"
    # graph_repo = load_file(file_name)
    # print(topo_sort_prev(graph_repo))

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
    # cliques = list(map(set, cliques_1))


main()

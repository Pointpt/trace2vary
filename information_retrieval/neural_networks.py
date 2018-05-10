# -*- coding: utf-8 -*-
import numpy

"""SPLTrac: SPL Traceability Experimental Suite

Author: Tassio Vale
Website: www.tassiovale.com
Contact: tassio.vale@ufrb.edu.br
"""


class Node:
    """Graph node implementation for the neural network."""

    def __init__(self, node_id, act_level=0.0):
        self.id = node_id
        self.activation_level = act_level
        self.adjacent = {}

    def update_neighbor(self, neighbor, weight=0.0):
        if neighbor in self.adjacent:
            self.adjacent[neighbor] += weight
        else:
            self.adjacent[neighbor] = weight

    def get_connections(self):
        return self.adjacent.keys()

    def get_id(self):
        return self.id

    def get_neighbor_edge_weight(self, neighbor):
        if neighbor in self.adjacent:
            return self.adjacent[neighbor]
        else:
            return None

    def get_activation_level(self):
        return self.activation_level

    def update_activation_level(self, act_level):
        self.activation_level += act_level


pass


class Graph:
    """Graph implementation for the neural network."""

    def __init__(self):
        self.node_dict = {}
        self.num_nodes = 0

    def __iter__(self):
        return iter(self.node_dict.values())

    def add_node(self, node_id, activation_level=0.0):
        self.num_nodes += 1
        new_node = Node(node_id, activation_level)
        self.node_dict[node_id] = new_node
        return new_node

    def get_node(self, node_id):
        if node_id in self.node_dict:
            return self.node_dict[node_id]
        else:
            return None

    def update_edge(self, source_node, dest_node, new_dest_act_level, weight=0.0):
        if source_node not in self.node_dict:
            self.add_node(source_node)
        if dest_node not in self.node_dict:
            self.add_node(dest_node)
        self.node_dict[dest_node].update_activation_level(new_dest_act_level)
        self.node_dict[source_node].update_neighbor(self.node_dict[dest_node], weight)
        self.node_dict[dest_node].update_neighbor(self.node_dict[source_node], weight)

    def get_nodes(self):
        return self.node_dict.keys()


pass


def create_neural_network(pre_processor, features):
    """This variability_impl_technology calculates the similarity of relevant documents
    for a given feature (and related synonyms)."""

    neural_network = Graph()
    sum_query_weights = 0.0
    sum_document_term_weights = {}

    # calculating norm of query and document vectors
    for document in pre_processor.get_documents().keys():
        document_term_weight = 0.0
        for (term_node_object, index_by_term) in pre_processor.get_inverted_index().items():
            if term_node_object in features and document in index_by_term:
                index_by_term = pre_processor.get_inverted_index()[term_node_object]
                term_document_ocurrences = pre_processor.get_docs_per_term(term_node_object)
                sum_query_weights += \
                    numpy.square(numpy.math.log((pre_processor.get_num_files() /
                                                 term_document_ocurrences), 2))
                document_term_weight += numpy.square(1 + numpy.math.log(index_by_term[document].frequency, 2))
        if document_term_weight != 0.0:
            sum_document_term_weights[document] = numpy.sqrt(document_term_weight)
    sum_query_weights = numpy.sqrt(sum_query_weights)

    # initial activations
    for document in pre_processor.get_documents().keys():
        for (term_node_object, index_by_term) in pre_processor.get_inverted_index().items():
            if term_node_object in features and document in index_by_term:
                index_by_term = pre_processor.get_inverted_index()[term_node_object]
                term_document_ocurrences = pre_processor.get_docs_per_term(term_node_object)
                idf = numpy.math.log((pre_processor.get_num_files() / term_document_ocurrences), 2)
                tf = 1 + numpy.math.log(index_by_term[document].frequency, 2)

                if sum_query_weights != 0:
                    wiq = idf / sum_query_weights
                else:
                    wiq = 0

                if sum_document_term_weights[document] != 0:
                    wij = tf / sum_document_term_weights[document]
                else:
                    wij = 0

                neural_network.add_node(term_node_object, wiq)
                neural_network.add_node(document, 0.0)
                neural_network.update_edge(term_node_object, document, wiq * wij, wij)

    with open('information_retrieval/neural_network_iterations.dat', "r") as iterations_file:
        iterations = int(iterations_file.readline())
        iterations_file.close()

        # performing automatic iterations
        for i in range(1, iterations+1):
            for node_id in neural_network.get_nodes():
                if node_id in pre_processor.get_documents():
                    document_node = neural_network.get_node(node_id)
                    for term_node in document_node.get_connections():
                        if term_node.get_id() in features:
                            edge_weight = document_node.get_neighbor_edge_weight(term_node.get_id())
                            if edge_weight is not None:
                                term_node.update_activation_level(document_node.get_activation_level() * edge_weight)
                                document_node.update_activation_level(term_node.get_activation_level() * edge_weight)

    return neural_network


def neural_network_calculation(neural_network, document):
    """Method used for tests to check the similarity value of documents to the respective features."""

    document_node = neural_network.get_node(document)

    if document_node is not None:
        return document_node.get_activation_level()
    else:
        return 0

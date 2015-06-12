/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2015  lLars (Ole) Hollenbach  <lohlive@online.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "graph.h"

Graph::Node::Node(const QVariant& dataNew) :
    data(dataNew)
{}

Graph::Node::~Node()
{
    while(links_.count() > 0) {
        delete links_[0];
        links_.removeFirst();
    }
}

const QList< Graph::Link* >* Graph::Node::allLinks() const
{
    return &links_;
}

Graph::NodeID::NodeID(Graph* graph, int id) :
    graph_(graph), id_(id)
{}

Graph::NodeID::NodeID(const Graph::NodeID& other) :
    graph_(other.graph_), id_(other.id_)
{}

Graph::Link* Graph::NodeID::connect(Graph::NodeID other, const QVariant& data)
{
    Link* newLink = new Graph::Link(*this, other, data);
    this->node()->links_.append(newLink);
    other.node()->links_.append(newLink);
}

Graph::Node* Graph::NodeID::node()
{
    return graph_->nodeByID(*this);
}

bool Graph::NodeID::operator==(Graph::NodeID other) const
{
    return graph_ == other.graph_ && id_ == other.id_;
}

Graph::NodeID Graph::NodeID::null()
{
    return NodeID(0, -1);
}

Graph::Link::Link(Graph::NodeID node_1, Graph::NodeID node_2, QVariant dataNew) :
    node1_(node_1), node2_(node_2), data(dataNew)
{}

Graph::Link::~Link()
{
    node1_.node()->links_.removeAll(this);
    node2_.node()->links_.removeAll(this);
}

void Graph::Link::disconnect()
{
    delete this;
}

Graph::NodeID Graph::Link::otherNode(Graph::NodeID thisNode)
{
    if(node1() == thisNode) {
        return node2();
    } else if( node2() == thisNode) {
        return node1();
    }
    return NodeID::null();
}

Graph::NodeID Graph::Link::node1()
{
    return node1_;
}

Graph::NodeID Graph::Link::node2()
{
    return node2_;
}

Graph::Graph():
    QObject()
{}

Graph::~Graph()
{
    while(nodes_.count() > 0) {
        if(nodes_.first() != 0) {
            delete nodes_.first();
        }
        nodes_.removeFirst();
    }
}

Graph::NodeID Graph::addNode(const QVariant& data)
{
    Node* newNode = new Node(data);
    bool foundFreeSlot = false;
    for(int i = 0; i < nodes_.count(); i++) {
        if(nodes_.at(i) == 0) {
            foundFreeSlot = true;
            nodes_[i] = newNode;
            return NodeID(this, i);
        }
    }
    if(!foundFreeSlot) {
        nodes_.append(newNode);
        return NodeID(this, nodes_.count() - 1);
    }
}

int Graph::removeNode(const Graph::NodeID node)
{
    Q_ASSERT_X(node.graph_ == this, __PRETTY_FUNCTION__,
               "the node you want to remove is in another graph!");
    delete nodes_[node.id_];
    if(node.id_ == nodes_.count() - 1) {
        nodes_.removeLast();
    } else {
        nodes_[node.id_] = 0;
    }
}

QList< Graph::NodeID > Graph::searchNode(QVariant searchData)
{
    QList<NodeID> out;
    for(int i = 0; i < nodes_.count(); i++) {
	if(nodes_[i] != 0 && nodes_[i]->data == searchData) {
	    out.append(NodeID(this, i));
	}
    }
    return out;
}

Graph::Node* Graph::nodeByID(Graph::NodeID id)
{
    Q_ASSERT_X(id.graph_ == this, __PRETTY_FUNCTION__,
               "the node you want to access is in another graph!");
    return nodes_[id.id_];
}

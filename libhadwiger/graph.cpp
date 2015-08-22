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

using namespace Hadwiger;

namespace Hadwiger
{
class PrivateGraphNode
{
public:
    PrivateGraphNode(const QVariantHash &data);
    ~PrivateGraphNode();
    QList<PrivateGraphLink *> links;
    QVariantHash data;
};

class PrivateGraphLink
{
public:
    PrivateGraphLink(const QVariantHash &data, const int nodeIndex1, const int nodeIndex2, Graph *graph);
    QVariantHash data;
    int node1Idx;
    int node2Idx;
    Graph *graph;
};

class LinkPrivate
{
public:
    PrivateGraphLink *linkPtr;
};
class NodePrivate
{
public:
    Graph *graph;
    int index;
};

class GraphPrivate
{
public:
    QList<PrivateGraphNode *> nodes;
};
};

PrivateGraphNode::PrivateGraphNode(const QVariantHash &data) :
    data(data)
{}

PrivateGraphNode::~PrivateGraphNode()
{
    while (!links.isEmpty()) {
        Link tmp(links[0]);
        tmp.disconnect();
    }
}

PrivateGraphLink::PrivateGraphLink
(const QVariantHash &data, const int nodeIndex1, const int nodeIndex2, Graph *graph) :
    data(data), node1Idx(nodeIndex1), node2Idx(nodeIndex2), graph(graph)
{}

Node::Node() :
    d_ptr(new NodePrivate)
{
    Q_D(Node);
    d->graph = 0;
    d->index = -1;
}

Node::Node(const Node &other) :
    d_ptr(new NodePrivate)
{
    Q_D(Node);
    d->graph = other.d_func()->graph;
    d->index = other.d_func()->index;
}

Node::Node(Graph *graph, int id) :
    d_ptr(new NodePrivate)
{
    Q_D(Node);
    d->graph = graph;
    d->index = id;
}

Node::~Node()
{
    delete d_ptr;
}

Link Node::connect(const Node &other, const QVariantHash &data)
{
    Q_D(Node);
    PrivateGraphLink *pLink = new PrivateGraphLink(data, d->index, other.d_func()->index, d->graph);
    PrivateGraphNode *thisPrivate = d->graph->nodeByIndex(d->index);
    PrivateGraphNode *otherPrivate = d->graph->nodeByIndex(other.d_func()->index);
    thisPrivate->links.append(pLink);
    otherPrivate->links.append(pLink);
    return Link(pLink);
}

QList< Link > Node::links()
{
    Q_D(Node);
    QList<Link> out;
    QList<PrivateGraphLink *> rawLinks = d->graph->nodeByIndex(d->index)->links;
    foreach (PrivateGraphLink * rawLink, rawLinks) {
        out.append(Link(rawLink));
    }
    return out;
}

const QVariant Node::value(const QString &key) const
{
    Q_D(const Node);
    return d->graph->nodeByIndex(d->index)->data.value(key);
}

const QVariant &Node::operator[](const QString &key) const
{
    Q_D(const Node);
    return d->graph->nodeByIndex(d->index)->data[key];
}

void Node::insert(const QString &key, const QVariant &value)
{
    Q_D(Node);
    d->graph->nodeByIndex(d->index)->data.insert(key, value);
}

int Node::remove(const QString &key)
{
    Q_D(Node);
    return d->graph->nodeByIndex(d->index)->data.remove(key);
}

bool Node::isNull()
{
    Q_D(Node);
    return d->graph == 0 || d->index < 0;
}

bool Node::operator==(const Node &other) const
{
    Q_D(const Node);
    return d->graph == other.d_func()->graph && d->index == other.d_func()->index;
}

Node &Node::operator=(const Node &other)
{
    Q_D(Node);
    new(this) Node(other);
    return *this;
}

Link::Link() :
    d_ptr(new LinkPrivate)
{
    Q_D(Link);
    d->linkPtr = 0;
}

Link::Link(const Link &other) :
    d_ptr(new LinkPrivate)
{
    Q_D(Link);
    d->linkPtr = other.d_func()->linkPtr;
}

Link::Link(PrivateGraphLink *pPtr) :
    d_ptr(new LinkPrivate)
{
    Q_D(Link);
    d->linkPtr = pPtr;
}

Link::~Link()
{
    delete d_ptr;
}

void Link::disconnect()
{
    Q_D(Link);
    PrivateGraphNode *node1 = d->linkPtr->graph->nodeByIndex(d->linkPtr->node1Idx);
    PrivateGraphNode *node2 = d->linkPtr->graph->nodeByIndex(d->linkPtr->node2Idx);
    node1->links.removeAll(d->linkPtr);
    node2->links.removeAll(d->linkPtr);
    delete d->linkPtr;
    d->linkPtr = 0;
}

const QVariant Link::value(const QString &key) const
{
    Q_D(const Link);
    return d->linkPtr->data.value(key);
}

const QVariant &Link::operator[](const QString &key) const
{
    Q_D(const Link);
    return d->linkPtr->data[key];
}

void Link::insert(const QString &key, const QVariant &value)
{
    Q_D(Link);
    d->linkPtr->data.insert(key, value);
}

int Link::remove(const QString &key)
{
    Q_D(Link);
    return d->linkPtr->data.remove(key);
}

bool Link::isNull()
{
    Q_D(Link);
    return d->linkPtr == 0;
}

bool Link::operator==(const Link &other) const
{
    Q_D(const Link);
    return d->linkPtr == other.d_func()->linkPtr;
}

Link &Link::operator=(const Link &other)
{
    Q_D(Link);
    new(this) Link(other);
    return *this;
}

Node Link::otherNode(const Node &thisNode)
{
    Q_D(Link);
    if (node1() == thisNode) {
        return node2();
    } else if (node2() == thisNode) {
        return node1();
    } else {
        return Node();
    }
}

Node Link::node1()
{
    Q_D(Link);
    return Node(d->linkPtr->graph, d->linkPtr->node1Idx);
}

Node Link::node2()
{
    Q_D(Link);
    return Node(d->linkPtr->graph, d->linkPtr->node2Idx);
}

Graph::Graph() :
    QObject(), d_ptr(new GraphPrivate)
{}

Graph::~Graph()
{
    delete d_ptr;
}

Node Graph::addNode(const QVariantHash &data)
{
    Q_D(Graph);
    int emptyIdx = d->nodes.indexOf(0);
    if (emptyIdx < 0) {
        d->nodes.append(0);
        emptyIdx = d->nodes.count() - 1;
    }
    d->nodes[emptyIdx] = new PrivateGraphNode(data);
    return Node(this, emptyIdx);
}

void Graph::removeNode(const Node &node)
{
    Q_D(Graph);
    Q_ASSERT(node.d_func()->graph == this);
    delete d->nodes[node.d_func()->index];
    d->nodes[node.d_func()->index] = 0;
}

QList<Node> Graph::searchNode(const QString &key, const  QVariant &value)
{
    Q_D(const Graph);
    QList<Node> out;
    for (int i = 0; i < d->nodes.count(); i++) {
        const PrivateGraphNode *const pNode = d->nodes.at(i);
        if(pNode == 0) {
            continue;
        } 
        
        if (pNode->data.value(key) == value) {
            out.append(Node(this, i));
        }
    }
    return out;
}

QList< Node > Graph::allNodesWithKey(const QString &key)
{
    Q_D(const Graph);
    QList<Node> out;
    for (int i = 0; i < d->nodes.count(); i++) {
        const PrivateGraphNode *const pNode = d->nodes.at(i);
        if(pNode == 0) {
            continue;
        }
        
        if (pNode->data.contains(key)) {
            out.append(Node(this, i));
        }
    }
    return out;
}

PrivateGraphNode *Graph::nodeByIndex(const int index)
{
    Q_D(Graph);
    return d->nodes[index];
}

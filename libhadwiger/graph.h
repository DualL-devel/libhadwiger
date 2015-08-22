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

#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QHash>
#include <QtCore/QList>

namespace Hadwiger
{

class Graph;
class Node;
class Link;

class GraphPrivate; // defined in source
class PrivateGraphNode; // defined in source
class PrivateGraphLink; // defined in source
class LinkPrivate; // defined in source
class NodePrivate; // defined in source

// accesses a PrivateGraphNode in a graph
class Node
{
public:
    friend class Graph;
    
    Node();
    Node(const Node& other);
    Node(Graph* graph, int id);
    virtual ~Node();

    // connects the nodes and registers the link to both
    Link connect(const Hadwiger::Node& other, const QVariantHash& data);
    QList<Link> links();
    QList<const Link> links() const; 

    // data access operators
    const QVariant value(const QString& key) const;
    const QVariant &operator[](const QString& key) const;
    // data write oparators
    void insert(const QString &key, const QVariant& value);
    int remove(const QString &key);
    
    bool isNull();
    bool operator==(const Node &other) const;
    Node &operator=(const Node& other);

protected:
    NodePrivate *const d_ptr;
    Q_DECLARE_PRIVATE(Node);
};

// accesses a PrivateGraphLink in a graph
class Link
{
public:
    friend class Node;
    friend class PrivateGraphLink;
    friend class PrivateGraphNode;
    
    Link();
    Link(const Link &other);
    virtual ~Link();
    
    void disconnect(); // deletes the Link from both nodes. this becomes unusable
    
    // data access operators
    const QVariant value(const QString& key) const;
    const QVariant &operator[](const QString& key) const;
    // data write oparators
    void insert(const QString &key, const QVariant& value);
    int remove(const QString &key);

    Node otherNode(const Node& thisNode);
    Node node1();
    Node node2();
    
    bool isNull();
    bool operator==(const Link &other) const;
    Link &operator=(const Link& other);

protected:
    LinkPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(Link);
    
private:
    Link(PrivateGraphLink *pPtr);
};

class Graph : public QObject
{
    Q_OBJECT;
public:

    Graph();
    virtual ~Graph();

    Node addNode(const QVariantHash& data);
    void removeNode(const Node& node);
    QList<Node> searchNode(const QString& key, const QVariant& value);
    QList<Node> allNodesWithKey(const QString &key);
    
    PrivateGraphNode *nodeByIndex(const int index);

protected:
    GraphPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(Graph);
};
};

#endif // GRAPH_H

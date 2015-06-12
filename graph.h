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

class Graph : public QObject
{
    Q_OBJECT;
public:
    class Node;
    class Link;

    class Node
    {
        Node(const QVariant& data);
    public:
        friend class Link;
        friend class Graph;

        ~Node(); // removes the node and all Links

        const QList<Link*>* allLinks() const;

        QVariant data;

    private:
        QList<Link*> links_;
    };

    class NodeID
    {
        NodeID(Graph* graph, int id);
    public:
        friend class Graph;

        NodeID(const NodeID& other);

        // connects the nodes and registers the link to both
        Link* connect(NodeID other, const QVariant& data);
        Node* node();
        bool operator==(NodeID other) const;
	
	static NodeID null();

    private:
        Graph* graph_;
        int id_;
    };

    class Link
    {
        // this does not take care of notifing the nodes
        Link(NodeID node_1, NodeID node_2, QVariant data);
    public:
        friend Link* NodeID::connect(NodeID, const QVariant&);

        ~Link(); // removes the link cleanly from the nodes
        void disconnect(); // the same as delete Link !! the pointer becomes unusable!
        QVariant data;

        NodeID otherNode(NodeID thisNode);
        NodeID node1();
        NodeID node2();

    private:
        NodeID node1_;
        NodeID node2_;
    };

    Graph();
    virtual ~Graph();

    NodeID addNode(const QVariant& data);
    int removeNode(const NodeID node);
    QList<NodeID> searchNode(QVariant searchData);
    Node* nodeByID(NodeID id);

private:
    QList<Node*> nodes_;

signals:
    void nodeRemoved(NodeID removed);
};

#endif // GRAPH_H

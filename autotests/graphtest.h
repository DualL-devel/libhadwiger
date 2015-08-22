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

#ifndef GRAPHTEST_H
#define GRAPHTEST_H

#include <QObject>

#include <graph.h>

class GraphTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();
    
    void addNodes();
    void linkNodes();
    void deleteNodeWithLink();
    void searchNode();
    void searchKeys();
    void searchNodes();
    
    //void createIndex();
    //void useIndex();
    //void deleteIndex();
    
private:
    void setupNodes(Hadwiger::Graph& graph, Hadwiger::Node& node1, Hadwiger::Node& node2);
    void setupNodesWithLink(Hadwiger::Graph &graph, Hadwiger::Node& node1, Hadwiger::Node& node2, Hadwiger::Link &link);
};

#endif // GRAPHTEST_H

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

#include "graphtest.h"

#include <QtTest>

using namespace Hadwiger;

QTEST_MAIN(GraphTest);

void GraphTest::initTestCase()
{
    // Called before the first testfunction is executed
}

void GraphTest::cleanupTestCase()
{
    // Called after the last testfunction was executed
}

void GraphTest::init()
{
    // Called before each testfunction is executed
}

void GraphTest::cleanup()
{
    // Called after every testfunction
}

void GraphTest::addNodes()
{
    Graph graph;
    
    QVariantHash data1;
    data1["name"] = QString("node1");
    Node node1 = graph.addNode(data1);
    QVERIFY(node1.value("name") == "node1");
    
    QVariantHash data2;
    data2["name"] = QString("node2");
    Node node2 = graph.addNode(data2);
    QVERIFY(node2.value("name") == "node2");
}

void GraphTest::linkNodes()
{
    Graph graph;
    
    QVariantHash data1;
    data1["name"] = QString("node1");
    Node node1 = graph.addNode(data1);
    QVERIFY(node1.value("name") == "node1");
    
    QVariantHash data2;
    data2["name"] = QString("node2");
    Node node2 = graph.addNode(data2);
    QVERIFY(node2.value("name") == "node2");
    
    QVariantHash linkData;
    linkData["name"] = QString("link1");
    Link link1 = node1.connect(node2, linkData);
    QVERIFY(link1.value("name") == "link1");
    QVERIFY(node1.links().count() == 1);
    QVERIFY(node2.links().count() == 1);
    QVERIFY(node1.links().at(0) == link1);
    QVERIFY(node2.links().at(0) == link1);
    
    link1.disconnect();
    QVERIFY(node1.links().count() == 0);
    QVERIFY(node2.links().count() == 0);
}

void GraphTest::deleteNodeWithLink()
{
    Graph graph;
    
    Node node1;
    Node node2;
    Link link;
    setupNodesWithLink(graph, node1, node2, link);
    
    graph.removeNode(node1);
    QVERIFY(node2.links().count() == 0);
}

void GraphTest::searchNode()
{
    Graph graph;
    Node node1;
    Node node2;
    setupNodes(graph, node1, node2);
    
    QList<Node> foundNodes = graph.searchNode("name", QString("node1"));
    QVERIFY(foundNodes.count() == 1);
    Node found = foundNodes[0];
    QVERIFY(found == node1);
}

void GraphTest::searchKeys()
{
    Graph graph;
    Node node1;
    Node node2;
    setupNodes(graph, node1, node2);
    
    QList<Node> foundNodes = graph.allNodesWithKey("name");
    QVERIFY(foundNodes.count() == 2);
    QVERIFY(foundNodes.contains(node1));
    QVERIFY(foundNodes.contains(node2));
}

void GraphTest::searchNodes()
{
    Graph graph;
    Node node1;
    Node node2;
    
    QVariantHash data1;
    data1["name"] = QString("node1");
    data1["data"] = QString("samehere");
    node1 = graph.addNode(data1);
    
    QVariantHash data2;
    data2["name"] = QString("node2");
    data2["data"] = QString("samehere");
    node2 = graph.addNode(data2);
    
    QList<Node> foundNodes = graph.searchNode("data", QString("samehere"));
    QVERIFY(foundNodes.count() == 2);
    QVERIFY(foundNodes.contains(node1));
    QVERIFY(foundNodes.contains(node2));
}

// ===== helpers =====

void GraphTest::setupNodes(Graph &graph, Hadwiger::Node& node1, Hadwiger::Node& node2)
{
    QVariantHash data1;
    data1["name"] = QString("node1");
    node1 = graph.addNode(data1);
    
    QVariantHash data2;
    data2["name"] = QString("node2");
    node2 = graph.addNode(data2);
}

void GraphTest::setupNodesWithLink(Graph &graph, Node &node1, Node &node2, Link &link)
{
    QVariantHash data1;
    data1["name"] = QString("node1");
    node1 = graph.addNode(data1);
    
    QVariantHash data2;
    data2["name"] = QString("node2");
    node2 = graph.addNode(data2);
    
    QVariantHash linkData;
    linkData["name"] = QString("link1");
    link = node1.connect(node2, linkData);
}

#include "graphtest.moc"

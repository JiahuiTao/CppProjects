/*
 * CS 106B Trailblazer
 * This file contains the main algorithms of pathfinding.
*/

#include "Trailblazer.h"
using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;

void clearQueue(Queue<Path*>& q){
    while (!q.isEmpty()){
        Path* p = q.dequeue();
        delete p;
    }
}

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Queue<Path*> q;
    Set<RoadEdge*> roads;
    Set<RoadNode*> visited;
    Path* p1 = new Path();
    p1->add(start);
    q.enqueue(p1);
    while (!q.isEmpty()){
        Path* p = q.dequeue();
        RoadNode* last = (*p)[p->size()-1];
        visited.add(last);
        last->setColor(Color::GREEN);
        if(last == end){
            clearQueue(q);
            return *p;
        }
        roads = last->outgoingEdges();
        for (RoadEdge* e: roads) {
            Path* p_new = new Path();
            *p_new = *p;
            RoadNode* next = e->to();
            if(visited.contains(next)){continue;}
            p_new->add(next);
            next->setColor(Color::YELLOW);
            q.enqueue(p_new);
        }
        delete p;
    }
    clearQueue(q);
    return {};
}

void clearQueue(PriorityQueue<Path*>& pq){
    while (!pq.isEmpty()){
        Path* p = pq.dequeue();
        delete p;
    }
}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    PriorityQueue<Path*> pq;
    Set<RoadEdge*> roads;
    Set<RoadNode*> visited;
    Path* p1 = new Path();
    p1->add(start);
    pq.add(p1,0);
    while (!pq.isEmpty()){
        double cost = pq.peekPriority();
        Path* p = pq.dequeue();
        RoadNode* last = (*p)[p->size()-1];
        visited.add(last);
        last->setColor(Color::GREEN);
        if(last == end){
            clearQueue(pq);
            return *p;
        }
        roads = last->outgoingEdges();
        for (RoadEdge* e: roads) {
            Path* p_new = new Path();
            *p_new = *p;
            RoadNode* next = e->to();
            if(visited.contains(next)){continue;}
            p_new->add(next);
            next->setColor(Color::YELLOW);
            pq.enqueue(p_new, cost+e->cost());
        }
        delete p;
    }
    clearQueue(pq);
    return {};
}

double underEstimateCost(const RoadGraph& graph, RoadNode* start, RoadNode* end){
    double speed = graph.maxRoadSpeed();
    double distance = graph.crowFlyDistanceBetween(start, end);
    return distance/speed;
}


Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    PriorityQueue<Path*> pq;
    Set<RoadEdge*> roads;
    Set<RoadNode*> visited;
    double h;
    Path* p1 = new Path();
    p1->add(start);
    h = underEstimateCost(graph,start,end);
    pq.add(p1,h);
    while (!pq.isEmpty()){
        double cost = pq.peekPriority();
        Path* p = pq.dequeue();
        RoadNode* last = (*p)[p->size()-1];
        h = underEstimateCost(graph,last,end);
        cost -= h;
        visited.add(last);
        last->setColor(Color::GREEN);
        if(last == end){
            clearQueue(pq);
            return *p;
        }
        roads = last->outgoingEdges();
        for (RoadEdge* e: roads) {
            Path* p_new = new Path();
            *p_new = *p;
            RoadNode* next = e->to();
            if(visited.contains(next)){continue;}
            p_new->add(next);
            next->setColor(Color::YELLOW);
            h = underEstimateCost(graph,next,end);
            pq.enqueue(p_new, cost+e->cost()+h);
        }
        delete p;
    }
    clearQueue(pq);
    return {};
}

double pathDifference(Path a, Path b){
    int cnt = 0;
    for (RoadNode* i: a){
        for (RoadNode* j: b){
            if (i==j){
                cnt++;
            }
        }
    }
    return static_cast<double>(a.size() - cnt) / static_cast<double>(b.size());
}

Path alternativeRoute(Path& best, const RoadGraph& graph, RoadNode* start, RoadNode* end, RoadNode* skip_from, RoadNode* skip_to, double& final_cost){
    PriorityQueue<Path*> pq;
    Set<RoadEdge*> roads;
    Set<RoadNode*> visited;
    double h;
    Path* p1 = new Path();
    p1->add(start);
    h = underEstimateCost(graph,start,end);
    pq.add(p1,h);
    while (!pq.isEmpty()){
        double cost = pq.peekPriority();
        Path* p = pq.dequeue();
        RoadNode* last = (*p)[p->size()-1];
        h = underEstimateCost(graph,last,end);
        cost -= h;
        visited.add(last);
        last->setColor(Color::GREEN);
        if(last == end){
            if (pathDifference(*p, best) > SUFFICIENT_DIFFERENCE){
                clearQueue(pq);
                final_cost = cost;
                return *p;
            }
            else {continue;}
        }
        roads = last->outgoingEdges();
        for (RoadEdge* e: roads) {
            if(e->from() == skip_from && e->to() == skip_to){continue;}
            Path* p_new = new Path();
            *p_new = *p;
            RoadNode* next = e->to();
            if(visited.contains(next)){continue;}
            p_new->add(next);
            next->setColor(Color::YELLOW);
            h = underEstimateCost(graph,next,end);
            pq.enqueue(p_new, cost+e->cost()+h);
        }
        delete p;
    }
    clearQueue(pq);
    return {};
}

Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Path best = aStar(graph, start, end);
    Path temp;
    Path alt;
    double alt_cost;
    double min_cost = numeric_limits<double>::max();
    for (int i = 1; i < best.size(); i++){
        temp = alternativeRoute(best, graph, start, end, best[i-1], best[i], alt_cost);
        if (temp.size() != 0 && alt_cost < min_cost){
            alt = temp;
            min_cost = alt_cost;
        }
    }
    return alt;
}


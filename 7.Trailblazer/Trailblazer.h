/*
 * CS 106B Trailblazer
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include "vector.h"
#include "RoadGraph.h"
#include "queue.h"
#include "priorityqueue.h"

/**
 * Type: Path
 *
 * A type representing a path. This type literally is a Vector<Vertex*>, but we've given
 * it the convenient name "Path" for simplicity.
 */
using Path = Vector<RoadNode*>;

/*
 * The path-searching algorithms you must implement.
 */
void clearQueue(Queue<Path*>& q);
Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end);
void clearQueue(PriorityQueue<Path*>& pq);
Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end);
double underEstimateCost(const RoadGraph& graph, RoadNode* start, RoadNode* end);
Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end);
double pathDifference(Path a, Path b);
Path alternativeRoute(Path& best, const RoadGraph& graph, RoadNode* start, RoadNode* end, RoadNode* skip_from, RoadNode* skip_to, double& final_cost);
Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end);

#endif

/*
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 */


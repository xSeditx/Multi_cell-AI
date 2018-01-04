#pragma once

#include<vector>
#include<iostream>
#include"window.h"

using namespace std;
 
#define MUTATION_RATE ((rand()%101)-50)

#define MAZE_SIZE 1000

#define MAX_AGE            60
#define MAX_HEALTH         200
#define MAX_CREATURES      7000

#define WORLD_WIDTH        SCREENWIDTH  
#define WORLD_HEIGHT       SCREENHEIGHT

#define LEFT_BOUNDS        0.0f
#define TOP_BOUNDS         0.0f

#define NUM_NEURONS        5
#define NUM_RESPONSES      3

#define NORTHING           0
#define ENEMY              1
#define MATE               2
#define WALL               3
#define FOOD               4

#define AMOUNT_FOOD 10000

enum  gender {male, female};


extern int WORLD[SCREENWIDTH][SCREENHEIGHT];


struct vec{
	float X,
		  Y,
		  SPEED,
		  ANGLE;
	float FRICTION;
};

struct Edge {
    int ID,
        IN,
       OUT;

	float TENSION,
		  ANGLE;
};

class multi_cell; // Forward Declaration of MULTI_CELL so the parent can be passed to the children cells.

class cell{
public:
	cell();
   ~cell();
	cell(multi_cell*);

	int ID,
		PARENT_ID,
		HEALTH;

	unsigned int COLOR;

    vector<int>EDGES;

	vec POSITION;
		

    void  KILL();
	void  MOVE();
    int   HIT();
    
	void  WRAP();

	long  BRAIN[NUM_NEURONS][NUM_RESPONSES] ;

//============== METHODS =============
const int   GET_ID();
      void  SIGHT_HANDLER(int SIGHT);
	  void  DRAW  (float,float,float);
  	  void  ROTATE(float &X, float &Y, float angle);
};

class multi_cell{

public:
	multi_cell();
   ~multi_cell();
	multi_cell(int);

	vector<cell>CELLS;
    vector<Edge>EDGES;

	 int ID,
		 HEALTH,
	     COLLISION,
	     NUMBER_OF_CELLS;

	 struct {
		 float FOV,
			   DISTANCE;
	 }VISION;

	 unsigned int COLOR;
	 bool         ALIVE;
	 float        ANGLE;

	 vec POSITION,
		 POTENTIAL;

	 gender GENDER;


//============== METHODS =============
	  void  ROTATE(float angle);	
	  float WRAPX(float);
	  float WRAPY(float);
	  float WRAP_ANGLE(float);
	  void  WRAP();
	  void  MOVE(float );
      void  DRAW();
	  int   HIT();
      void  KILL();
      void  SET_POSITION();
      int   SIGHT();
	  int   BREED(int OTHER);
 
const int  GET_ID();
};

/*
struct Organism {
     vector<Cell>CELLS;
     vector<Edge>EDGES;
	 float X,
	  	   Y,
		   SPEED,
		   ANGLE;
	 void Move(int);
	 void Draw();
};

struct Cell {
    int ID;
    vector<int>EDGES;

};
 struct Edge {
    int ID,
        IN,
       OUT;
};
vector<Organism>CREATURES;*/











//Graph databases are based on graph theory, and employ nodes, edges, and properties.
//
//Nodes represent entities such as people, businesses, accounts, or any other item to be tracked. They are roughly the equivalent of the
//record, relation, or row in a relational database, or the document in a document database.
//
//Edges, also termed graphs or relationships, are the lines that connect nodes to other nodes; they represent the relationship between them. Meaningful patterns emerge when examining
//the connections and interconnections of nodes, properties, and edges. Edges are the key concept in graph databases, representing an 
//abstraction that is not directly implemented in other systems.
//
//Properties are germane information that relate to nodes. For example, 
//if Wikipedia were one of the nodes, it might be tied to properties such as website, reference material, or word that starts with the 
//letter w, depending on which aspects of Wikipedia are germane to a given database.

//pub struct Graph {
//  nodes: Vec<Node>,
//  edges: Vec<Edge>,
//}
//
//pub struct Node {
//  id: u64,
//  edges: <u64>
//  attributes: HashMap<String,f32>,
//}
//
//pub struct Edge {
//  id: u64,
//  in: u64,
//  out: u64,
//  attributes: HashMap<String,f32>,
//}
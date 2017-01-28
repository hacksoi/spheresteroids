#ifndef GAME_HEADER
#define GAME_HEADER

struct read_file_result
{ 
	uint32_t ContentsSize;
	void *Contents;
};

struct game_button
{
	bool IsPressed;
	bool IsDown;
};

struct line_data
{
	line3 Line;
	v3 ACrossB;
	float ADotB;
};

struct base_vectors
{
	v3 Forward;
	v3 Right;
	v3 Up;
};

struct camera
{
	base_vectors Bases;
	base_vectors OldBases;

	v3 Pos;
	v3 OldPos;
	
	float Distance;
};

enum entity_type
{
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ASTEROID
};

struct entity
{
	entity_type Type;

	v3 RightAxis;
	quaternion Velocity;

	uint32_t NumVertices;
#define ENTITY_VERTEX_CENTER 0
#define ENTITY_VERTEX_AFTER_CENTER 1
#define ENTITY_MAX_VERTICES 12
	v3 Vertices[ENTITY_MAX_VERTICES];
	v3 OldVertices[ENTITY_MAX_VERTICES];
};

struct game_state
{
	camera Camera;

	uint32_t EntityCount;
	entity Entities[32];
};

#endif

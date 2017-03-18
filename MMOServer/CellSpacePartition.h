#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
//-----------------------------------------------------------------------------
//
//  Name:   CellSpacePartition
//
//  Desc:   Class to divide a 2D space into a grid of cells each of which
//          may contain a number of entities. Once created and initialized 
//          with entities, fast proximity querys can be made by calling the
//          calculateNeighborsForSmall method with a position and proximity radius.
//
//          If an Entity is capable of moving, and therefore capable of moving
//          between cells, the update method should be called each update-cycle
//          to sychronize the Entity and the cell space it occupies
//
//  Author: Insub Im (insooneelife@naver.com)
//
//-----------------------------------------------------------------------------

#include <vector>
#include <list>
#include <memory>
#include <sstream>
#include <cassert>

#include "AABBox2D.h"
#include <Common/Math/Vec2.h>


//-------------------------------- Cell ----------------------------------
//
//  defines a cell containing a list of pointers to entities
//------------------------------------------------------------------------
template <class Entity>
struct Cell
{
	//all the entities inhabiting this cell
	std::list<Entity> members;

	//the cell's bounding box (it's inverted because the Window's default
	//co-ordinate system has a y axis that increases as it descends)
	AABBox2D bounding_box;

	Cell(Vec2 botleft, Vec2 topright)
		:
		bounding_box(AABBox2D(botleft, topright))
	{}

	~Cell()
	{}
};

//------------------------------CellSpacePartition-------------------------------
//
//  defines a cell space containing a vector of cells
//-------------------------------------------------------------------------------

template <class Entity>
class CellSpacePartition
{
public:
	typedef std::vector<std::unique_ptr<Cell<Entity> > > CellVector;
	typedef Entity entity_type;

	CellSpacePartition(
		double	width,			// width of the environment
		double	height,			// height ...
		int		cellsX,			// number of cells horizontally
		int		cellsY,			// number of cells vertically
		int		max_entitys);	// maximum number of entities to add

	inline const CellVector& getCells() const				{ return _cells; }
	inline const std::vector<Entity>& getNeighbors() const	{ return _neighbors; }
	inline int getNeighborsCnt() const						{ return _neighborsCnt; }

	// adds entities to the class by allocating them to the appropriate cell
	inline void addEntity(const Entity& ent);

	// removes entitiy from the cell
	inline void removeEntity(const Entity& ent);

	// update an Entity's cell by calling this from your Entity's update method 
	inline void updateEntity(const Entity& ent, Vec2 old_pos);

	// empties the cells of entities
	inline void clearCells();

	// this method calculates all a target's neighbors and stores them in
	// the neighbor vector. After you have called this method use the begin, 
	// next and end methods to iterate through the vector.
	// calculates neighbors with bounding shape
	inline void	calculateNeighbors(Vec2 wpos, float radius);
	inline void	calculateNeighborsForSmall(Vec2 wpos, float radius);
	inline void calculateNeighborsForOne(Vec2 wpos);

	inline Vec2 toCellSpacePos(Vec2 wpos) const
	{
		return Vec2(wpos.x + (_space_width / 2), wpos.y + (_space_height / 2));
	}

	inline Vec2 toWorldPos(Vec2 cpos) const
	{
		return Vec2(cpos.x - (_space_width / 2), cpos.y - (_space_height / 2));
	}
	
private:

	// given a position in the game space this method determines the           
	// relevant cell's index
	inline int positionToIndex(Vec2 wpos) const;

	// the required amount of cells in the space
	CellVector _cells;

	// this is used to store any valid neighbors when an agent searches
	// its neighboring space
	std::vector<Entity>	_neighbors;
	int _neighborsCnt;

	// the width and height of the world space the entities inhabit
	double  _space_width;
	double  _space_height;

	// the number of cells the space is going to be divided up into
	int    _num_cellsX;
	int    _num_cellsY;

	double  _cell_sizeX;
	double  _cell_sizeY;
};


//----------------------------- ctor ---------------------------------------
//--------------------------------------------------------------------------
template<class Entity>
CellSpacePartition<Entity>::CellSpacePartition(
	double width,			// width of 2D space
	double height,			// height...
	int cellsX,				// number of divisions horizontally
	int cellsY,				// and vertically
	int max_entitys)		// maximum number of entities to partition 
	:	
	_space_width(width),
	_space_height(height),
	_num_cellsX(cellsX),
	_num_cellsY(cellsY),
	_neighbors(max_entitys, Entity()),
	_neighborsCnt(0)
{
	// calculate bounds of each cell
	_cell_sizeX = width / cellsX;
	_cell_sizeY = height / cellsY;

	// create the cells
	for (int y = 0; y < _num_cellsY; ++y)
	{
		for (int x = 0; x < _num_cellsX; ++x)
		{
			double left	= x * _cell_sizeX;
			double right = left + _cell_sizeX;
			double bot = y * _cell_sizeY;
			double top = bot + _cell_sizeY;

			_cells.emplace_back(new Cell<Entity>(Vec2(left, bot), Vec2(right, top)));
		}
	}
}

//----------------------- calculateNeighbors ----------------------------
//
//  This must be called to create the vector of neighbors.This method 
//  examines each cell within range of the target, If the 
//  cells contain entities then they are tested to see if they are situated
//  within the target's neighborhood region. If they are they are added to
//  neighbor list
//------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::calculateNeighbors(Vec2 wpos, float radius)
{
	Vec2 pos = ToCellSpacePos(wpos);
	_neighborsCnt = 0;
	for (auto c = std::begin(_cells); c != std::end(_cells); ++c)
	{
		AABBox2D aabb(Vec2(pos.x - radius, pos.y - radius), Vec2(pos.x + radius, pos.y + radius));

		if ((*c)->bounding_box.isOverlappedWith(aabb))
			for (auto e = std::begin((*c)->members); e != std::end((*c)->members); ++e)
				_neighbors[_neighborsCnt++] = e;
	}
		
}


//----------------------- calculateNeighborsForSmall ----------------------------
//
// If an entity is not too big, then it doesn't have to loop all the cells to
// find the intersecting cells.
// Check neighbors for only 3x3 cells including current cell.
//-------------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::calculateNeighborsForSmall(Vec2 wpos, float radius)
{
	Vec2 pos = ToCellSpacePos(wpos);
	_neighborsCnt = 0;
	int idx = positionToIndex(pos);
	int mj = idx % _num_cellsX;
	int mi = idx / _num_cellsX;

	for (int i = std::max(0, mi - 1); i <= std::min(_num_cellsY - 1, mi + 1); i++)
	{
		for (int j = std::max(0, mj - 1); j <= std::min(_num_cellsX - 1, mj + 1); j++)
		{
			int ridx = i * _num_cellsX + j;
			AABBox2D aabb(Vec2(pos.x - radius, pos.y - radius), Vec2(pos.x + radius, pos.y + radius));

			if (_cells[ridx]->bounding_box.isOverlappedWith(aabb))
			{
				// add any entities found within query radius to the neighbor list
				for (auto e = std::begin(_cells[ridx]->members); e != std::end(_cells[ridx]->members); ++e)
					_neighbors[_neighborsCnt++] = e;
			}
		}
	}
}


//----------------------- calculateNeighborsForOne ----------------------------
//
// Makes neighbors by just one zone for given position.
//-------------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::calculateNeighborsForOne(Vec2 wpos)
{
	Vec2 pos = toCellSpacePos(wpos);
	int idx = positionToIndex(wpos);
	_neighborsCnt = 0;

	for (auto e = std::begin(_cells[idx]->members); e != std::end(_cells[idx]->members); ++e)
	{
		_neighbors[_neighborsCnt++] = *e;
	}
}

//--------------------------- clearCells --------------------------------------
//
//  clears the cells of all entities
//------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::clearCells()
{
	CellVector::iterator it = _cells.begin();

	for (it; it != _cells.end(); ++it)
	{
		(*it)->members.clear();
	}
}

//--------------------- positionToIndex ----------------------------------
//
//  Given a 2D vector representing a position within the game world, this
//  method calculates an index into its appropriate cell
//------------------------------------------------------------------------
template<class Entity>
int CellSpacePartition<Entity>::positionToIndex(Vec2 wpos)const
{
	Vec2 pos = toCellSpacePos(wpos);

	assert(
		0 <= pos.x && pos.x <= _space_width &&
		0 <= pos.y && pos.y <= _space_height &&
		"position out of range!");

	int idx = 
		(int)(_num_cellsX * pos.x / _space_width) +
		((int)((_num_cellsY)* pos.y / _space_height) * _num_cellsX);

	//if the Entity's position is equal to vector2d(_space_width, _space_height)
	//then the index will overshoot. We need to check for this and adjust
	if (idx > _cells.size() - 1) idx = _cells.size() - 1;

	return idx;
}

//----------------------- addEntity --------------------------------------
//
//  Used to add the entitys to the data structure
//------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::addEntity(const Entity& ent)
{
	int idx = positionToIndex(ent->getPos());
	_cells[idx]->members.push_back(ent);
}

//----------------------- removeEntity --------------------------------------
//
//  Removes the erased entity from cellspace.
//------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::removeEntity(const Entity& ent)
{
	int idx = positionToIndex(ent->getPos());
	_cells[idx]->members.remove(ent);
}

//----------------------- updateEntity -----------------------------------
//
//  Checks to see if an Entity has moved cells. If so the data structure
//  is updated accordingly
//------------------------------------------------------------------------
template<class Entity>
void CellSpacePartition<Entity>::updateEntity(const Entity& entity, Vec2 old_pos)
{
	// if the index for the old pos and the new pos are not equal then
	// the Entity has moved to another cell.
	int old_idx = positionToIndex(old_pos);
	int new_idx = positionToIndex(entity->getPos());

	if (new_idx == old_idx) return;

	// the Entity has moved into another cell so delete from current cell
	// and add to new one
	_cells[old_idx]->members.remove(entity);
	_cells[new_idx]->members.push_back(entity);
}

#endif
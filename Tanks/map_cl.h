/*
 * map_cl.h
 *
 *  Created on: Aug 13, 2016
 *      Author: timur
 */

#ifndef MAP_CL_H_
#define MAP_CL_H_

class map_cl{
private:
	unsigned char ** map[6];
	int xx,yy;
public:
	map_cl();
	~map_cl();
	bool update();
};



#endif /* MAP_CL_H_ */

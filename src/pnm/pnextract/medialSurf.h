#ifndef REFERENCE_H
#define REFERENCE_H


#include <list>
#include <set>
#include <stddef.h>
#include <cmath>
#include <vector>


#include "typses.h"
#include "inputData.h"

class node;



class medialSurface
{
public:


 medialSurface(inputDataNE& cfg);


 void setDefaults(double avgRad);
 void paradox_pre_removeincludedballI();
 void paradoxremoveincludedballI();

 void calc_distmaps();
 void calc_distmap(voxel * vit, unsigned char vValue,  const voxelImage& vxls, std::vector<std::vector<node> >& oldAliens) const;




 void buildvoxelspace();

 void smoothRadius();

 void competeForParentNoMerge(medialBall* vi, medialBall* vjv);
 void competeForParent(medialBall* vi, medialBall* vj);
 void findBoss(medialBall*);
 void createBallsAndHierarchy();



 void allyWithBossKids();

 void moveUphill(medialBall* b_i);
 void moveUphillp1(medialBall* b_i);

 voxel* vxl(int i, int j, int k)
 {
 	if (i<0 || j<0 || k<0 || i>= nx || j>= ny || k>= nz)
 		return NULL;

 	segments& s = segs_[k][j];
 	for (int p = 0; p<s.cnt; ++p)
 		if ( (i >= s.s[p].start) && (i < s.s[p+1].start) )
 		{
			if (0 == s.s[p].value)   return (s.s[p].segV+(i-s.s[p].start));
			else                             return NULL;
		}
 	return NULL;
 }



 const segment& segg(int i, int j, int k) const
 {	if (i<0 || j<0 || k<0 || i>= nx || j>= ny || k>= nz)
		return invalidSeg;

 	const segments& s = segs_[k][j];
 	for (int p = 0; p<s.cnt; ++p)
 		if (i >= s.s[p].start && i < s.s[p+1].start)
 				return (s.s[p]);

	cout<<"Error can not find segment at "<<i<<" "<<j<<" "<<k<<" nSegs: "<<s.cnt<<endl;
 	return (s.s[s.cnt]);
 }


 const segment& nextSegg(int i, int j, int k) const
 {	if (i<0 || j<0 || k<0 || i>= nx || j>= ny || k>= nz)
		return invalidSeg;

 	const segments& s = segs_[k][j];
 	for (int p = 0; p<s.cnt; ++p)
 		if (i >= s.s[p].start && i < s.s[p+1].start)
 			return (s.s[p+1]);

	cout<<"Error can not find next segment at "<<i<<" "<<j<<" "<<k<<" nSegs: "<<s.cnt<<endl;
 	return (s.s[s.cnt]);
 }


 bool isInside(int i, int j, int k) const
 {  return (i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz);  }

 bool isJInside(int j) const
 {  return (j>=0 && j<ny);  }

 bool isInside(int i) const
 {	return (0<=i && i<nx); }

 public:

	const inputDataNE& cg_;
	int nx, ny, nz;
	double precision;

	size_t nVxls;
	size_t nBalls;


	std::vector< std::vector<segments> >& segs_;
	segment invalidSeg;
	std::vector<voxel> vxlSpace;
	std::vector<medialBall> ballSpace;
	medialBall ToBeAssigned;





    float  _minRp;
    double _clipROutx;
    double _clipROutyz;
    double _midRf;
    double _MSNoise;
    double _lenNf;

    double _vmvRadRelNf;

    int _nRSmoothing;
    double _RCorsnf;
    float _RCorsn;
//	const double crossAreaFracx4;


};





#endif

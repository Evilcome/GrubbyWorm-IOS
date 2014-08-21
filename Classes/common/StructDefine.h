//
//  StructDefine.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-21.
//
//

#ifndef DigitalWorm_StructDefine_h
#define DigitalWorm_StructDefine_h

typedef struct _row_col_
{
    int row;
    int col;
} row_col;

typedef struct _row_col_range_
{
    row_col from;
    row_col to;
} row_col_range;

typedef struct _start_point_
{
    row_col info;
    unsigned short direction;
} start_point;

typedef struct _count_detail_
{
	int now;
	int max;
} count_detail;

typedef struct _score_
{
    int combo;
    int combo_max;
    int combo_times;
    int step;
    int trigger;
    int total;
} score;

#endif
